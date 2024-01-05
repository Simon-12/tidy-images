#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>
#include <QScopedPointer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtConcurrent>
#include <QtSql>

#include "../models/filemodel.h"
#include "headermodel.h"
#include "settings.h"
#include "sqlhandler.h"

/*!
 * \brief The Database class:
 * Database handler, contains the sql handler, database model and header model.
 */
class Database : public QObject {
    Q_OBJECT

public:
    explicit Database(FileList* list, Settings set, QObject* parent = nullptr);

    void addToDatabase();
    void removeFromDatabase();
    void insertFile(int index, QString path);
    void removePath(QString path);
    void updateModel();

    void setFileModel(FileModel* fileModel) { m_fileModel = fileModel; }
    QSqlQueryModel* model() { return m_model; }
    HeaderModel* headerModel() { return m_headerModel; }
    bool active() { return m_active; }
    void setActive(bool state);

public slots:

    void setFilter(QString filter, QString direction);
    void finished();

signals:

    void databaseStep(int index);

private:
    void init();
    void initModels();
    void addFile(int index, QString path, SqlHandler* handler);
    void startThreadAdd();
    void startThreadRemove();

    bool m_active;
    QString m_path;
    QList<QString> m_header;
    HeaderModel* m_headerModel;
    QSqlQueryModel* m_model;
    FileModel* m_fileModel;
    FileList* m_fileList;
    QString m_query;
    QString m_queryEnd;
    QFuture<void> m_future;
    QFutureWatcher<void> m_watcher;
    SqlHandler* m_handler;
};

#endif  // DATABASE_H
