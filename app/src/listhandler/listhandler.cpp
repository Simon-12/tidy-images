#include "listhandler.h"


ListHandler::ListHandler(Settings set, AppMode mode, QObject *parent) : QObject(parent)
{    
    m_path = set.path + "/"; // add seperator
    m_favorites = set.favorites;
    m_mode = mode;
    set.mode = mode; // Refreseh
    ListSort::actual_order = Order::Name;
    ListSort::actual_direction = Direction::Up;
    VideoFile::setFrameHash(&m_frameHash);
    m_imageModel = new ImageModel(&m_fileList, this);
    m_labelModel = new LabelModel(&m_fileList, this);
    m_fileModel = new FileModel(&m_fileList, this);

    switch(m_mode)
    {
    case AppMode::Gallery:
    case AppMode::Database:
        m_imageFormats = set.imageFormats;
        m_videoFormats = set.videoFormats;
        break;
    case AppMode::Video: m_videoFormats = set.videoFormats; break;
    default: m_imageFormats = set.imageFormats; break;
    }

    connect(&m_watcher, &QFutureWatcher<void>::started, this, &ListHandler::started);
    connect(&m_watcher, &QFutureWatcher<void>::finished, this, &ListHandler::finished);
    if(m_mode == AppMode::Database) // Second connection for finished
        connect(&m_watcher, &QFutureWatcher<void>::finished, this, &ListHandler::databaseFinished);

    initCompare(set);
    initDatabase(set);
    initCommands(set);
    initModels();
}


ListHandler::~ListHandler()
{
    m_fileList.clear();
    qInfo() << "Delete list";
}


bool ListHandler::isFavorite(int index)
{
    if(!checkIndex(index)) return false;
    return *m_fileList[index]->favorite();
}


void ListHandler::changeOrder(Order order)
{
    if(ListSort::actual_order != order)
    {
        emit startLoading(size());
        m_future = QtConcurrent::run(ListSort::order, &m_fileList, order);
        m_watcher.setFuture(m_future);
    }
}


void ListHandler::changeDirection(Direction direction)
{
    if(ListSort::actual_direction != direction)
    {
        emit startLoading(size());
        m_future = QtConcurrent::run(ListSort::direction, &m_fileList, direction);
        m_watcher.setFuture(m_future);
    }
}


bool ListHandler::addLabel(int index, QString label)
{
    if(!checkIndex(index)) return false;
    label = label.simplified(); // remove whitespaces
    if(label.isEmpty()) return false;
    if(m_labelModel->contains(label)) return false;

    m_labelModel->append(label);
    m_fileList[index]->setLabels(m_labelModel->getLabels());
    return true;
}


bool ListHandler::removeLabel(int index, int label)
{
    if(!checkIndex(index)) return false;
    m_labelModel->remove(label);
    m_fileList[index]->setLabels(m_labelModel->getLabels());
    return true;
}


void ListHandler::setRotation(int index, bool direction)
{
    if(!checkIndex(index)) return;
    m_fileList[index]->setRotation(direction);
}


QString ListHandler::file(int index)
{
    m_labelModel->updateIndex(index);
    if(!checkIndex(index))
    {
        m_info = "";
        return "";
    }
    else
    {
        QString img = *m_fileList[index]->name();

        // Create info string
        m_info = img.leftJustified(50, ' ')
                + (m_fileList[index]->fileDate(ListSort::actual_order)
                   + "\t\t\tType: " +
                   m_fileList[index]->formatStr()
                   ).leftJustified(60, ' ')
                + "Number: " + QString::number(index + 1)
                + " / " + QString::number(size());

        return m_path + img;
    }
}


void ListHandler::startLoadFiles()
{
    if(m_mode == AppMode::Database)
    {
        emit startLoading(0);
        emit finishedLoading();
        m_database->updateModel();
        return;
    }
    loadFiles();
}


void ListHandler::addToDatabase()
{
    m_addDatabase = true;
    loadFiles();
}


void ListHandler::removeFromDatabase()
{
    m_addDatabase = false;
    loadFiles();
}


void ListHandler::setPlugins(PluginLoader *plugins)
{
    m_plugins = plugins;
    m_compareList->setPlugin(m_plugins->visionPlugin());
    m_commandList->setPlugins(m_plugins->exivPlugin(),
                              m_plugins->visionPlugin());
    ImageFile::setPlugin(m_plugins->exivPlugin());
    VideoFile::setPlugin(m_plugins->visionPlugin());
}


void ListHandler::loadFiles()
{
    QStringList favorites = QDir(m_favorites).entryList(m_imageFormats + m_videoFormats, QDir::Files);
    QFileInfoList infoList = QDir(m_path).entryInfoList(m_imageFormats + m_videoFormats, QDir::Files);
    m_fileList.clear();
    m_fileList.reserve(infoList.size());

    qInfo() << "Start loading";
    emit startLoading(infoList.size());
    m_future = QtConcurrent::run(this, &ListHandler::startThreadFiles, infoList, favorites);
    m_watcher.setFuture(m_future);
}


void ListHandler::startThreadFiles(const QFileInfoList &infoList, const QStringList &favorites)
{
    int index = 0;
    foreach(QFileInfo info, infoList)
    {
        BaseFile *file;
        if(m_videoFormats.contains("*." + info.suffix(), Qt::CaseInsensitive))
            file = new VideoFile();
        else
            file = new ImageFile();

        file->init(info, favorites.contains(info.fileName(), Qt::CaseInsensitive));
        m_fileList.append(FilePtr(file));
        emit loadedFile(index);
        index++;
    }
}


void ListHandler::updateModels()
{
    if(m_mode == AppMode::Image || m_mode == AppMode::Compare)
        m_imageModel->refreshModel();

    if(m_mode == AppMode::Compare)
        m_compareList->tableModel()->refreshModel();

    if(m_mode == AppMode::Gallery)
        m_fileModel->refreshModel();
}


void ListHandler::initCompare(Settings set)
{
    m_compareList = new CompareList(&m_fileList, set, this);
    connect(m_compareList, &CompareList::compareStep, this, &ListHandler::singleStep);
    connect(m_compareList, &CompareList::compareFinished, this, &ListHandler::compareFinished);
}


void ListHandler::initDatabase(Settings set)
{
    m_database = new Database(&m_fileList, set, this);
    m_database->setFileModel(m_fileModel);
    connect(m_database, &Database::databaseStep, this, &ListHandler::loadedFile);
}


void ListHandler::initCommands(Settings set)
{
    m_commandList = new CommandList(&m_fileList, set, this);
    m_commandList->setDatabase(m_database);
    m_commandList->setImageModel(m_imageModel);
    m_commandList->setFileModel(m_fileModel);
    connect(m_commandList, &CommandList::indexChanged, this, &ListHandler::indexChanged);
    connect(m_fileModel, &FileModel::favorite, m_commandList, &CommandList::setFavorite);
}


void ListHandler::initModels()
{
    m_listModels.setImages(m_imageModel);
    m_listModels.setLabels(m_labelModel);
    m_listModels.setTable(m_compareList->tableModel());
    m_listModels.setDatabaseActive(m_database->active());
    m_listModels.setDatabase(m_database->model());
    m_listModels.setHeader(m_database->headerModel());
    m_listModels.setFiles(m_fileModel);
    m_listModels.setCommand(m_commandList->model());
}


bool ListHandler::checkIndex(int index)
{
    if(index < 0 || index >= size())
    {
        qInfo() << "Index out of range";
        return false;
    }
    return true;
}


void ListHandler::started()
{
    m_timer.start();
}


void ListHandler::finished()
{
    updateModels();
    qInfo() << "Finished loading";
    emit finishedLoading();
    QString time = QString::number(m_timer.elapsed());
    qInfo() << "Process Time: " + time + " ms";
}


void ListHandler::compareFinished()
{
    // Sort and update model
    emit startLoading(size());
    ListSort::actual_direction = Direction::Down; // Max first
    ListSort::score(&m_fileList);
    updateModels();
}


void ListHandler::databaseFinished()
{
    emit startLoading(size());
    if(m_addDatabase)
        m_database->addToDatabase();
    else
        m_database->removeFromDatabase();
}
