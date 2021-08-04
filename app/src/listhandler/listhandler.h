#ifndef LISTHANDLER_H
#define LISTHANDLER_H

#include <QObject>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QElapsedTimer>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

#include "basefile/imagefile.h"
#include "basefile/videofile.h"
#include "command/commandlist.h"
#include "compare/comparelist.h"
#include "database/database.h"
#include "models/imagemodel.h"
#include "models/labelmodel.h"
#include "models/listmodels.h"
#include "plugins/pluginloader.h"
#include "settings.h"
#include "options.h"
#include "support.h"
#include "listsort.h"

/*!
 * \brief The ListHandler class:
 * Main list handler, reads in files and fill the models.
 * Contains the command, compare and database handler.
 */
class ListHandler : public QObject
{
    Q_OBJECT

public:

    explicit ListHandler(Settings set, AppMode mode, QObject *parent = nullptr);
    ~ListHandler();

    bool isFavorite(int index);
    void changeOrder(Order order);
    void changeDirection(Direction direction);
    bool addLabel(int index, QString label);
    bool removeLabel(int index, int label);
    void setRotation(int index, bool direction);
    QString file(int index);
    void startLoadFiles();
    void addToDatabase();
    void removeFromDatabase();

    FileList* fileList(){ return &m_fileList; }
    QString* info(){ return &m_info; }
    FrameHash* frameHash(){ return &m_frameHash; }
    int size(){ return m_fileList.size(); }
    CommandList* commands(){ return m_commandList; }
    CompareList* compare(){return m_compareList;}
    ListModels listModels(){ return m_listModels; }
    void setPlugins(PluginLoader* plugins);

private:

    FileList m_fileList;
    CommandList* m_commandList;
    CompareList* m_compareList;
    Database* m_database;
    ImageModel* m_imageModel;
    LabelModel* m_labelModel;
    FileModel* m_fileModel;
    ListModels m_listModels;
    FrameHash m_frameHash;
    PluginLoader* m_plugins;

    QString m_path;
    QString m_favorites;
    QString m_info;
    AppMode m_mode;
    QStringList m_imageFormats;
    QStringList m_videoFormats;
    QElapsedTimer m_timer;
    QFuture<void> m_future;
    QFutureWatcher<void> m_watcher;
    bool m_addDatabase;

    void loadFiles();
    void startThreadFiles(const QFileInfoList &infoList, const QStringList &favorites);
    void updateModels();
    void initCompare(Settings set);
    void initDatabase(Settings set);
    void initCommands(Settings set);
    void initModels();
    bool checkIndex(int index);

signals:

    void indexChanged(int index);
    void singleStep();
    void startLoading(int size);
    void loadedFile(int index);
    void finishedLoading();

private slots:

    void started();
    void finished();
    void compareFinished();
    void databaseFinished();
};

#endif // LISTHANDLER_H
