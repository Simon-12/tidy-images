#ifndef SQLHANDLER_H
#define SQLHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

#include "../basefile/basefile.h"

/*!
 * \brief The SqlHandler class:
 * Sql handler for the database.
 */
class SqlHandler : public QObject {
    Q_OBJECT

public:
    explicit SqlHandler(QString name, QString path, QObject *parent = nullptr, bool debug = false);
    ~SqlHandler();

    void printTable();
    void addFile(FilePtr file, QString path);
    void removeFile(QString path);
    QSqlDatabase database();

private:
    QString m_name;
    QString m_path;
    bool m_debug;

    bool execQuery(QSqlQuery &query);
    int queryId(QSqlQuery &query);
    int checkId(QString path);
    void openDatabase();
    void createTable();
    void closeDatabase();
};

#endif  // SQLHANDLER_H
