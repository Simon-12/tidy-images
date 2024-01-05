#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <QDebug>
#include <QElapsedTimer>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>
#include <QUndoStack>
#include <QtConcurrent>

#include "../database/database.h"
#include "../models/imagemodel.h"
#include "commandmodel.h"
#include "plugins/exivplugin.h"
#include "plugins/visionplugin.h"
#include "settings.h"

/*!
 * \brief The CommandList class:
 * Command class for the list, contains the command handling and undo framework.
 */
class CommandList : public QObject {
    Q_OBJECT

public:
    explicit CommandList(FileList* list, Settings set, QObject* parent = nullptr);
    bool moveFile(int index, const QString& path);
    bool moveFiles(const QString& path);
    bool copyFile(int index, const QString& path);
    bool copyFiles(const QString& path);
    bool moveTrash(int index);
    bool moveFilesTrash();
    bool setFilesFavorite();
    void undo();
    void redo();

    CommandModel* model() { return m_model; }
    void setDatabase(Database* database) { m_dataDefault.database = database; }
    void setImageModel(ImageModel* imageModel) { m_dataDefault.imageModel = imageModel; }
    void setFileModel(FileModel* fileModel);
    void setPlugins(ExivPlugin* exiv, VisionPlugin* vision);

public slots:

    bool setFavorite(int index);

signals:

    void indexChanged(int index);

private:
    QString m_path;
    QString m_trash;
    QString m_favorites;
    CommandData m_dataDefault;
    FileList* m_fileList;
    FileModel* m_fileModel;
    QUndoStack* m_undoStack;
    QElapsedTimer m_timer;
    QFuture<void> m_future;
    QFutureWatcher<void> m_watcher;
    CommandModel* m_model;
    ExivPlugin* m_exivPlugin;
    VisionPlugin* m_visionPlugin;

    bool checkIndex(int index);
    CommandData createCommand(int index, const QString& path);
    void rotateThread(QString path, int rotation);
    void beginMacro();
    void endMacro();
    QList<int> selectedFiles(bool clear = false);

private slots:

    void started();
    void finished();
    void changeIndex(int index);
};

#endif  // COMMANDLIST_H
