#include "commandlist.h"


CommandList::CommandList(FileList* list, Settings set, QObject *parent) : QObject(parent)
{
    m_fileList = list;
    m_path = set.path + "/"; // add seperator here
    m_trash = set.trash;
    m_favorites = set.favorites;
    m_undoStack = new QUndoStack(this);
    m_model = new CommandModel(this);
    m_dataDefault.fileList = list;
    m_dataDefault.mode = set.mode;

    connect(m_undoStack, &QUndoStack::indexChanged, this, &CommandList::changeIndex);
    connect(m_undoStack, &QUndoStack::indexChanged, m_model, &CommandModel::setIndex);
    connect(m_model, &CommandModel::clicked, m_undoStack, &QUndoStack::setIndex);
    connect(&m_watcher, &QFutureWatcher<void>::started, this, &CommandList::started);
    connect(&m_watcher, &QFutureWatcher<void>::finished, this, &CommandList::finished);
}


bool CommandList::moveFile(int index, const QString &path)
{
    if(!checkIndex(index)) return false;
    if(path.isEmpty()) return false;

    // Add to UndoStack and run redo()
    CommandData data = createCommand(index, path);
    int rotation     = *data.file->rotation();
    data.file->resetRotation(); // Get and reset rotation
    m_undoStack->push(new MoveCommand(data));

    // Rotate image
    if(rotation != 0)
    {
        m_future = QtConcurrent::run(this, &CommandList::rotateThread, data.target, rotation);
        m_watcher.setFuture(m_future);
    }

    qInfo() << "Move to: " + path;
    return true;
}


bool CommandList::moveFiles(const QString &path)
{
    QVector<int> selected = selectedFiles(true);
    if(selected.isEmpty()) return false;

    beginMacro();
    foreach(int i, selected)
        moveFile(i, path);
    endMacro();
    return true;
}


bool CommandList::copyFile(int index, const QString &path)
{
    if(!checkIndex(index)) return false;
    if(path.isEmpty()) return false;

    // Add to UndoStack and run redo()
    CommandData data = createCommand(index, path);
    m_undoStack->push(new CopyCommand(data));

    qInfo() << "Copy to: " + path;
    return true;
}


bool CommandList::copyFiles(const QString &path)
{
    QVector<int> selected = selectedFiles();
    if(selected.isEmpty()) return false;

    beginMacro();
    foreach(int i, selected)
        copyFile(i, path);
    endMacro();
    return true;
}


bool CommandList::moveTrash(int index)
{
    return moveFile(index, m_trash);
}


bool CommandList::moveFilesTrash()
{
    QVector<int> selected = selectedFiles(true);
    if(selected.isEmpty()) return false;
    beginMacro();
    foreach(int i, selected)
        moveTrash(i);
    endMacro();
    return true;
}


bool CommandList::setFavorite(int index)
{
    if(!checkIndex(index)) return false;

    // Add to UndoStack and run redo()
    CommandData data = createCommand(index, m_favorites);
    m_undoStack->push(new FavoriteCommand(data));
    return true;
}


bool CommandList::setFilesFavorite()
{
    QVector<int> selected = selectedFiles();
    if(selected.isEmpty()) return false;

    beginMacro();
    foreach(int i, selected)
        setFavorite(i);
    endMacro();
    return true;
}


void CommandList::undo()
{
    m_undoStack->undo();
}


void CommandList::redo()
{
    m_undoStack->redo();
}


void CommandList::setFileModel(FileModel *fileModel)
{
    m_dataDefault.fileModel = fileModel;
    m_fileModel = fileModel;
}


void CommandList::setPlugins(ExivPlugin *exiv, VisionPlugin *vision)
{
    m_exivPlugin = exiv;
    m_visionPlugin = vision;
}


bool CommandList::checkIndex(int index)
{
    if(index < 0 || index >= m_fileList->size())
    {
        qInfo() << "Index out of range";
        return false;
    }

    return true;
}


CommandData CommandList::createCommand(int index, const QString &path)
{
    QString file     = *m_fileList->at(index)->name();
    CommandData data = m_dataDefault;
    data.index       = index;
    data.source      = m_path + file;
    data.target      = path +"/"+ file;
    data.file        = m_fileList->at(index);

    m_model->append(data);
    return data;
}


void CommandList::rotateThread(QString path, int rotation)
{
    VisionPlugin::ROTATE rotate;
    switch (rotation)
    {
    case 90:  rotate = VisionPlugin::CLOCKWISE_90;        break;
    case 180: rotate = VisionPlugin::ROTATE_180;          break;
    case 270: rotate = VisionPlugin::COUNTERCLOCKWISE_90; break;
    default:  return;
    }

    if(!m_visionPlugin) return;
    if(m_exivPlugin) m_exivPlugin->readMetadata(path);
    m_visionPlugin->rotateImage(path, rotate);
    if(m_exivPlugin) m_exivPlugin->writeMetadata(path);
}


void CommandList::beginMacro()
{
    m_undoStack->beginMacro("Start");
    m_model->beginMacro();
}


void CommandList::endMacro()
{
    m_undoStack->endMacro();
    m_model->endMacro();
}


QVector<int> CommandList::selectedFiles(bool clear)
{
    QVector<int> selected = m_fileModel->selected();
    std::sort(selected.begin(), selected.end(), std::greater<int>());
    if(clear)
        m_fileModel->clearSelected();
    return selected;
}


void CommandList::started()
{
    m_timer.start();
}


void CommandList::finished()
{
    QString time = QString::number(m_timer.elapsed());
    qInfo() << "Single process Time: " + time + " ms";
}


void CommandList::changeIndex(int index)
{
    // Get command on stack
    const QUndoCommand* cmd = m_undoStack->command(index);
    if(!cmd)
    {
        emit indexChanged(-1);
        return;
    }

    // Get index
    const BaseCommand* data = dynamic_cast<const BaseCommand*>(cmd);
    if(!data)
    {
        emit indexChanged(-1);
        return;
    }

    emit indexChanged(data->index());
}
