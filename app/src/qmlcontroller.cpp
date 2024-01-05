#include "qmlcontroller.h"

#include "logger.h"
#include "support.h"

QmlController::QmlController(QString path, QObject *parent) : QObject(parent) {
    // Start status logger
    logger::startLogging();

    // Read config file
    m_config = new ConfigHandler(path, this);
    m_config->init();
    m_mode = m_config->settings().mode;
    m_fullscreen = false;

    // Start controller
    m_pluginloader = new PluginLoader(this);
    m_provider = new ImageProvider();
    m_loader = new LoaderClass(m_config->settings().bufferSize, this);
    startController();
}

QmlController::~QmlController() { qInfo() << "\n- Close controller"; }

void QmlController::setIndex(int index, bool force) {
    if (force) {
        if (m_index == 0)
            m_index++;
        else
            m_index--;
        emit indexChanged();
    }

    // Check to large
    if (m_index >= m_list->size()) m_index--;

    // Check empty
    if (m_list->size() == 0)
        m_index = 0;
    else if (m_index != index && index < m_list->size() && index >= 0) {
        m_index = index;
        qInfo() << "Index: " << m_index;
    }

    // Check file
    QString file = m_list->file(m_index);
    if (file.isEmpty()) {
        setFile("");
        m_mode = AppMode::Empty;
        emit modeChanged();
    } else
        setFile("file:///" + file);

    // Emit changes
    emit indexChanged();
    setFavorite();
}

void QmlController::setFile(QString file) {
    m_file = file;
    emit fileChanged();
}

void QmlController::setFavorite() {
    m_favorite = m_list->isFavorite(m_index);
    emit favoriteChanged();
}

void QmlController::setFullscreen(bool state) {
    m_fullscreen = state;
    if (state) setIndex(m_index, true);
    emit fullscreenChanged();
}

void QmlController::setDatabase(bool state) {
    if (m_databaseActive == state) return;

    m_list->setDatabase(state);
    m_databaseActive = m_list->databaseActive();
    if (m_databaseActive == state) m_config->setDatabase(state);
    emit databaseChanged();
}

void QmlController::startController() {
    qInfo() << "\n- Start controller";
    qInfo() << "Mode:" << m_mode;
    m_loader->initLoader(m_mode);  // Open dialog
    emit loaderChanged();

    // Settings
    m_settings = m_config->settings();
    m_path = m_settings.path;
    m_paths.setPaths(m_settings);
    emit pathsChanged();

    // Load folders;
    m_folder = new FolderHandler(m_settings, this);
    m_folder->init();

    // Load list;
    m_list = new ListHandler(m_settings, m_mode, this);
    m_databaseActive = m_list->databaseActive();
    m_list->setPlugins(m_pluginloader);
    connect(m_list, &ListHandler::startLoading, m_loader, &LoaderClass::startLoading);
    connect(m_list, &ListHandler::loadedFile, m_loader, &LoaderClass::loadFile);
    connect(m_list, &ListHandler::singleStep, m_loader, &LoaderClass::singleStep);
    connect(m_list, &ListHandler::finishedLoading, this, &QmlController::finishedLoading);
    connect(m_list, &ListHandler::indexChanged, this, &QmlController::changeIndex);
    m_provider->setFrameHash(m_list->frameHash());
    // In Main.qml: controller.startLoadFiles(false)
}

QString QmlController::pathDialog() { return QFileDialog::getExistingDirectory(nullptr, "Select Path", m_path); }

void QmlController::updateController() {
    qInfo() << "\n- Update controller";
    delete m_folder;
    delete m_list;

    startController();
    startLoadFiles(true);
}

void QmlController::startLoadFiles(bool ignoreCache) { m_list->startLoadFiles(ignoreCache); }

void QmlController::waitFilesLoaded() { m_list->waitFilesLoaded(); }

void QmlController::moveFile(QString path) {
    if (m_mode == AppMode::Gallery && !m_fullscreen) {
        m_list->commands()->moveFiles(path);
        return;
    }

    if (m_mode == AppMode::Video) setFile("");  // Video must be cleared from memory

    m_list->commands()->moveFile(m_index, path);
}

void QmlController::addFolder() {
    QString path = pathDialog();
    if (!path.isEmpty()) m_folder->addFolder(path);
}

void QmlController::copyFile() {
    QString folder = pathDialog();
    if (folder.isEmpty()) return;

    if (m_mode == AppMode::Gallery && !m_fullscreen) {
        m_list->commands()->copyFiles(folder);
        return;
    }
    m_list->commands()->copyFile(m_index, folder);
}

void QmlController::deleteFile(int index) {
    if (m_mode == AppMode::Gallery && !m_fullscreen) {
        m_list->commands()->moveFilesTrash();
        return;
    }

    if (m_mode == AppMode::Video) setFile("");  // Video must cleared from memory

    if (index >= 0) m_index = index;  // Use given index
    m_list->commands()->moveTrash(m_index);
}

void QmlController::fileFavorit() {
    if (m_mode == AppMode::Gallery && !m_fullscreen) {
        m_list->commands()->setFilesFavorite();
        return;
    }

    m_list->commands()->setFavorite(m_index);
    setFavorite();
}

void QmlController::openExplorer(Menu menu) {
    QString argument;
    switch (menu) {
        case Menu::Path:
            argument = m_path;
            break;
        case Menu::Favorites:
            argument = m_settings.favorites;
            break;
        case Menu::Trash:
            argument = m_settings.trash;
            break;
        case Menu::File:
            argument = m_file;
            break;
    }
    startExplorer(argument);
}

void QmlController::changeOrder(int order) {
    Order odr = static_cast<Order>(order);  // int to enum
    m_list->changeOrder(odr);
}

void QmlController::changeDirection(int direction) {
    Direction dir = static_cast<Direction>(direction);  // int to enum
    m_list->changeDirection(dir);
}

void QmlController::addLabel(QString label) { m_list->addLabel(m_index, label); }

void QmlController::removeLabel(int index) { m_list->removeLabel(m_index, index); }

void QmlController::changePath(QString path, PathOptions option) {
    if (!m_config->changePath(path, option)) return;

    if (m_mode == AppMode::Empty)
        changeMode(AppMode::Gallery);
    else
        updateController();
}

void QmlController::changeCurrentPath() { changePath(m_path, PathOptions::CurrentPath); }

void QmlController::changeMode(AppMode mode) {
    if (mode == m_mode) {
        emit modeChanged();  // reset
        return;
    }

    m_mode = mode;
    emit modeChanged();
    updateController();
}

void QmlController::undo() { m_list->commands()->undo(); }

void QmlController::redo() {
    if (m_mode == AppMode::Video) setFile("");  // Video must cleared from memory

    m_list->commands()->redo();
}

void QmlController::setRotation(bool direction) { m_list->setRotation(m_index, direction); }

void QmlController::startCompare(int index) { m_list->compare()->startCompare(index); }

void QmlController::stopCompare() { m_list->compare()->stopCompare(); }

void QmlController::addToDatabase() { m_list->addToDatabase(); }

void QmlController::removeFromDatabase() { m_list->removeFromDatabase(); }

void QmlController::changeIndex(int index) {
    if (index < 0) {
        if (m_mode == AppMode::Gallery && !m_fullscreen) return;
        setIndex(m_index, true);
    } else
        setIndex(index, m_index == index);
}

void QmlController::finishedLoading() {
    if (m_mode != AppMode::Database) setIndex(0);
    emit modelsChanged();
}
