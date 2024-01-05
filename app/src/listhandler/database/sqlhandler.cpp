#include "sqlhandler.h"

SqlHandler::SqlHandler(QString name, QString path, QObject *parent, bool debug) : QObject(parent) {
    m_name = name;
    m_path = path;
    m_debug = debug;

    openDatabase();
    QSqlDatabase db = database();
    if (db.isOpen() && db.tables().isEmpty()) {
        qInfo() << "Databse is empty";
        createTable();
    }
    if (m_debug) printTable();
}

SqlHandler::~SqlHandler() { closeDatabase(); }

void SqlHandler::printTable() {
    qInfo() << "Print table";
    QSqlQuery query(database());
    query.prepare(
        "SELECT a.Name, b.Folder, GROUP_CONCAT(c.Label, '; ') AS Labels, "
        "a.Type, a.Date, a.Favorite, a.Path, a.Filetype, a.Duration "
        "FROM Files a "
        "JOIN Folders b ON b.Id = a.Folder_Id "
        "JOIN Files_Labels ac ON ac.File_Id = a.Id "
        "JOIN Labels c ON c.Id = ac.Label_Id "
        "GROUP BY Name");
    if (!execQuery(query)) return;
    QSqlRecord record = query.record();

    // Print header
    QString fieldName;
    for (int i = 0; i < record.count(); i++) fieldName += record.fieldName(i) + "    ";
    qInfo() << fieldName;

    // Print values
    while (query.next()) {
        record = query.record();
        QString field;
        for (int i = 0; i < record.count(); i++) {
            QVariant var = record.value(i);
            field += var.toString() + "    ";
        }
        qInfo() << field;
    }
}

void SqlHandler::addFile(FilePtr file, QString path) {
    if (checkId(path) > 0) return;
    QSqlQuery query(database());

    // Add Folder
    int pos1 = path.lastIndexOf("/") - 1;
    int pos2 = path.lastIndexOf("/", pos1);
    QString folder = path.mid(pos2 + 1, pos1 - pos2);
    query.prepare("SELECT Id FROM Folders WHERE Folder IS :folder");
    query.bindValue(":folder", folder);
    int folder_id = queryId(query);
    if (folder_id <= 0) {
        query.prepare("INSERT INTO Folders (Folder) VALUES(:folder)");
        query.bindValue(":folder", folder);
        if (!execQuery(query)) return;
        folder_id = query.lastInsertId().toInt();
    }

    // Add file
    query.prepare(
        "INSERT INTO Files (Name, Folder_Id, Path, Type, Date, Favorite, Filetype, Duration)"
        " VALUES(:name, :folder_Id, :path, :type, :date, :favorite, :filetype, :duration)");
    query.bindValue(":name", *file->name());
    query.bindValue(":folder_Id", folder_id);
    query.bindValue(":path", path);
    query.bindValue(":type", file->formatStr());
    query.bindValue(":date", file->dateStr());
    query.bindValue(":favorite", *file->favorite());
    query.bindValue(":filetype", file->typeStr());
    query.bindValue(":duration", *file->duration());
    if (!execQuery(query)) return;
    int file_id = query.lastInsertId().toInt();

    // Add labels
    QStringList labels = *file->labels();
    if (labels.isEmpty()) {
        query.prepare("INSERT INTO Files_Labels (File_Id, Label_Id) VALUES(:file_id, :label_id)");
        query.bindValue(":file_id", file_id);
        query.bindValue(":label_id", 1);  // 1 = NULL
        if (!execQuery(query)) return;
    }
    foreach (QString label, labels) {
        query.prepare("SELECT Id FROM Labels WHERE Label IS :label");
        query.bindValue(":label", label);
        int label_id = queryId(query);
        if (label_id <= 0) {
            query.prepare("INSERT INTO Labels (Label) VALUES(:label)");
            query.bindValue(":label", label);
            if (!execQuery(query)) return;
            label_id = query.lastInsertId().toInt();
        }
        query.prepare("INSERT INTO Files_Labels (File_Id, Label_Id) VALUES(:file_id, :label_id)");
        query.bindValue(":file_id", file_id);
        query.bindValue(":label_id", label_id);
        if (!execQuery(query)) return;
    }
    qInfo() << "Added" << file_id;
}

void SqlHandler::removeFile(QString path) {
    int id = checkId(path);
    if (id <= 0) return;

    // Remove file
    QSqlQuery query(database());
    query.prepare("DELETE FROM Files where id IS :id");
    query.bindValue(":id", id);
    if (!execQuery(query)) return;

    // Remove labels
    query.prepare("DELETE FROM Files_Labels where file_id IS :id");
    query.bindValue(":id", id);
    if (!execQuery(query)) return;

    qInfo() << "Removed" << id;
}

QSqlDatabase SqlHandler::database() {
    // re-create object for thread safety
    return QSqlDatabase::database(m_name);
}

bool SqlHandler::execQuery(QSqlQuery &query) {
    QSqlDatabase db = database();
    if (!db.isOpen()) {
        qInfo() << "The connection is not open!";
        return false;
    }

    if (m_debug) qInfo() << "Exec: " << query.executedQuery();

    if (!query.exec()) {
        qInfo() << "Error:" << db.lastError().text();
        qInfo() << "Error:" << query.lastError().text();
        return false;
    }
    return true;
}

int SqlHandler::queryId(QSqlQuery &query) {
    if (execQuery(query)) {
        if (!query.next()) return 0;
        QSqlRecord record = query.record();
        return record.value(0).toInt();
    }
    return 0;
}

int SqlHandler::checkId(QString path) {
    QSqlQuery query(database());
    query.prepare("SELECT Id FROM Files WHERE Path IS :path");
    query.bindValue(":path", path);
    return queryId(query);
}

void SqlHandler::openDatabase() {
    qInfo() << "Opening database";
    // m_name = QString("%1").arg(qintptr(QThread::currentThreadId()), 0, 16); // Use thread id
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", m_name);
    db.setDatabaseName(m_path);
    // ":memory:"
    // create a temporary database existing in memory until the connection is closed

    // m_db.setHostName("localhost");
    // m_db.setUserName("username");
    // m_db.setPassword("password");

    if (!db.open()) {
        qInfo() << "Could not open connection!";
        qInfo() << "Error:" << db.lastError().text();
        return;
    }
    qInfo() << "Opened database connection";
}

void SqlHandler::createTable() {
    // Files table
    QSqlQuery query(database());
    query.prepare(
        "CREATE TABLE Files ("
        "Id	INTEGER NOT NULL UNIQUE,"
        "Name TEXT NOT NULL,"
        "Folder_Id INTEGER NOT NULL,"
        "Path TEXT NOT NULL,"
        "Type TEXT NOT NULL,"
        "Date TEXT NOT NULL,"
        "Favorite INTEGER,"
        "Filetype TEXT NOT NULL,"
        "Duration TEXT,"
        "PRIMARY KEY(Id),"
        "FOREIGN KEY(Folder_Id) REFERENCES Folders(Id)"
        ");");
    if (!execQuery(query)) return;

    // Folder table
    query.prepare(
        "CREATE TABLE Folders ("
        "Id	INTEGER NOT NULL UNIQUE,"
        "Folder TEXT NOT NULL,"
        "PRIMARY KEY(Id)"
        ");");
    if (!execQuery(query)) return;

    // Labels table
    query.prepare(
        "CREATE TABLE Labels ("
        "Id	INTEGER NOT NULL UNIQUE,"
        "Label TEXT,"
        "PRIMARY KEY(Id)"
        ");");
    if (!execQuery(query)) return;
    query.prepare("INSERT INTO Labels (Label) VALUES(null)");
    if (!execQuery(query)) return;

    // File_Id to Labels_Id table
    query.prepare(
        "CREATE TABLE Files_Labels ("
        "File_Id INTEGER NOT NULL,"
        "Label_Id INTEGER NOT NULL,"
        "FOREIGN KEY(Label_Id) REFERENCES Labels(Id),"
        "FOREIGN KEY(File_Id) REFERENCES Files(Id)"
        ");");
    if (!execQuery(query)) return;

    qInfo() << "Create default table";
}

void SqlHandler::closeDatabase() {
    QSqlDatabase::removeDatabase(m_name);
    qInfo() << "Disconnected database";
}
