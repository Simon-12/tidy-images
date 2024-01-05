#include "database.h"

#include "../basefile/videofile.h"

Database::Database(FileList *list, Settings set, QObject *parent) : QObject(parent) {
    m_fileList = list;
    m_path = set.database;
    m_active = set.databaseActive;
    m_header << "Name"
             << "Folder"
             << "Label"
             << "Type"
             << "Date"
             << "Favorite";

    m_query =
        "SELECT a.Name, b.Folder, GROUP_CONCAT(c.Label, '; ') AS Labels, "
        "a.Type, a.Date, a.Favorite, a.Path, a.Filetype, a.Duration "
        "FROM Files a "
        "JOIN Folders b ON b.Id = a.Folder_Id "
        "JOIN Files_Labels ac ON ac.File_Id = a.Id "
        "JOIN Labels c ON c.Id = ac.Label_Id ";
    m_queryEnd = "GROUP BY Name";
    initModels();
    init();
}

void Database::addToDatabase() {
    m_future = QtConcurrent::run(&Database::startThreadAdd, this);
    m_watcher.setFuture(m_future);
}

void Database::removeFromDatabase() {
    m_future = QtConcurrent::run(&Database::startThreadRemove, this);
    m_watcher.setFuture(m_future);
}

void Database::insertFile(int index, QString path) {
    if (!m_active) return;
    addFile(index, path, m_handler);
}

void Database::removePath(QString path) {
    if (!m_active) return;
    m_handler->removeFile(path);
}

void Database::updateModel() {
    m_fileModel->clear();
    for (int i = 0; i < m_model->rowCount(); i++) {
        QSqlRecord record = m_model->record(i);
        QString path = record.value(6).toString();
        QString type = record.value(7).toString();
        FileItem item(type, "file:///" + path);

        if (type == "Video") {
            QString id = VideoFile::addFrameHash(path);
            QString duration = record.value(8).toString();
            item.setVideo(duration, id);
        }
        m_fileModel->append(item);
    }
}

void Database::setActive(bool state) {
    m_active = state;
    if (state)
        init();
    else
        delete m_handler;
}

void Database::init() {
    if (!m_active) return;
    if (m_path.isEmpty()) return;

    // Check driver available
    m_active = QSqlDatabase::isDriverAvailable("QSQLITE");
    if (!m_active) return;

    // Init handler
    m_handler = new SqlHandler("Main", m_path, this);
    m_model->setQuery(m_query + m_queryEnd, m_handler->database());
}

void Database::initModels() {
    m_model = new QSqlQueryModel(this);
    m_headerModel = new HeaderModel(m_header, this);
    connect(m_headerModel, &HeaderModel::filterChanged, this, &Database::setFilter);
    connect(m_headerModel, &HeaderModel::finishedFilter, this, &Database::updateModel);
    connect(&m_watcher, &QFutureWatcher<void>::finished, this, &Database::finished);
}

void Database::addFile(int index, QString path, SqlHandler *handler) {
    FilePtr file = m_fileList->at(index);

    // Only add file if got a label
    if (file->labels()->isEmpty()) return;

    handler->addFile(file, path);
}

void Database::startThreadAdd() {
    QScopedPointer<SqlHandler> handler(new SqlHandler("Thread", m_path));
    for (int i = 0; i < m_fileList->size(); i++) {
        addFile(i, *m_fileList->at(i)->path(), handler.data());
        emit databaseStep(i);
    }
}

void Database::startThreadRemove() {
    QScopedPointer<SqlHandler> handler(new SqlHandler("Thread", m_path));
    for (int i = 0; i < m_fileList->size(); i++) {
        handler->removeFile(*m_fileList->at(i)->path());
        emit databaseStep(i);
    }
}

void Database::setFilter(QString filter, QString direction) {
    m_model->setQuery(m_query + filter + m_queryEnd + direction, m_handler->database());
}

void Database::finished() {
    m_model->setQuery(m_query + m_queryEnd, m_handler->database());
    updateModel();
}
