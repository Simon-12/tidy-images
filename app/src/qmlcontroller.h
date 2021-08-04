#ifndef QMLCONTROLLER_H
#define QMLCONTROLLER_H

#include <QObject>
#include <QTime>
#include <QDebug>
#include <QFileDialog>

#include "filehandler/confighandler.h"
#include "filehandler/folderhandler.h"
#include "listhandler/listhandler.h"
#include "listhandler/imageprovider.h"
#include "plugins/pluginloader.h"
#include "logger.h"
#include "loaderclass.h"

/*!
 * \brief The QmlController class:
 * Main class for business logic.
 * Starts all necessary classes and sends updates to qml.
 */
class QmlController : public QObject
{
    Q_OBJECT

public:

    explicit QmlController(QString path, QObject *parent = nullptr);
    ~QmlController();    

    // Propertys
    Q_PROPERTY(int             index READ getIndex      WRITE  setIndex      NOTIFY indexChanged)
    Q_PROPERTY(bool       fullscreen READ getFullscreen WRITE  setFullscreen NOTIFY fullscreenChanged)
    Q_PROPERTY(bool         favorite READ getFavorite   NOTIFY favoriteChanged)
    Q_PROPERTY(QString        status READ getStatus     NOTIFY indexChanged)
    Q_PROPERTY(QString          file READ getFile       NOTIFY fileChanged)
    Q_PROPERTY(LoaderClass*   loader READ getLoader     NOTIFY loaderChanged)
    Q_PROPERTY(Paths           paths READ getPaths      NOTIFY pathsChanged)
    Q_PROPERTY(QSize          window READ getWindow     CONSTANT)
    Q_PROPERTY(Options::AppMode mode READ getMode       NOTIFY modeChanged)

    // Models
    Q_PROPERTY(FolderModel*        folders READ getFolders  NOTIFY modelsChanged)
    Q_PROPERTY(FolderFilterModel* selected READ getSelected NOTIFY modelsChanged)
    Q_PROPERTY(PluginModel*        plugins READ getPlugins  NOTIFY modelsChanged)
    Q_PROPERTY(ListModels       listModels READ getModels   NOTIFY modelsChanged)

    // Public getter and setter
    void setIndex(int index, bool force = false);
    FileList* fileList(){ return m_list->fileList(); }
    ImageProvider* imageProvider(){ return m_provider; }

private:

    int m_index;
    bool m_favorite;
    bool m_fullscreen;
    AppMode m_mode;
    QString m_path;
    QString m_file;
    Settings m_settings;
    Paths m_paths;
    ConfigHandler* m_config;
    FolderHandler* m_folder;
    ListHandler* m_list;
    LoaderClass* m_loader;
    ImageProvider* m_provider;
    PluginLoader* m_pluginloader;

    // Getter for propertys
    int getIndex(){ return m_index; }
    bool getFavorite(){ return m_favorite; }
    bool getFullscreen(){ return m_fullscreen; }
    LoaderClass* getLoader(){ return m_loader; }
    AppMode getMode(){ return m_mode; }
    QString getFile(){ return m_file; }
    QString getStatus(){ return *m_list->info(); }
    Paths getPaths(){ return m_paths; }
    QSize getWindow(){ return m_settings.size; }

    // Getter models
    FolderModel* getFolders(){ return m_folder->folderModel(); }
    FolderFilterModel* getSelected(){ return m_folder->selectedModel(); }
    PluginModel* getPlugins(){ return m_pluginloader->model(); }
    ListModels getModels(){ return  m_list->listModels(); }

    // Setter for propertys
    void setFile(QString file);
    void setFavorite();
    void setFullscreen(bool state);

    // Functions
    void startController();
    QString pathDialog();

signals:

    // Signals for propertys
    void indexChanged();
    void loaderChanged();
    void modeChanged();
    void fileChanged();
    void favoriteChanged();
    void pathsChanged();
    void modelsChanged();
    void fullscreenChanged();

public slots:

    void updateController();
    void moveFile(QString path);
    void addFolder();
    void copyFile();
    void deleteFile(int index = -1);
    void fileFavorit();
    void openExplorer(Menu menu);
    void changeOrder(int order);
    void changeDirection(int direction);
    void addLabel(QString label);
    void removeLabel(int index);
    void changePath(QString path, PathOptions option);
    void changeCurrentPath();
    void changeMode(AppMode mode);
    void undo();
    void redo();
    void setRotation(bool direction);
    void startCompare(int index);
    void stopCompare();
    void addToDatabase();
    void removeFromDatabase();

private slots:

    void changeIndex(int index);
    void finishedLoading();
};

#endif // QMLCONTROLLER_H
