#include "confighandler.h"

#include "../support.h"

ConfigHandler::ConfigHandler(QString path, QObject *parent) : BaseHandler(path, parent) {}

bool ConfigHandler::changePath(QString pathname, PathOptions option) {
    bool isFile = false;
    QString path;

    if (option == PathOptions::FolderFile) {
        isFile = true;
        path = QFileDialog::getOpenFileName(nullptr, "Select Folder File", pathname, "*.json");
        if (!checkFile(path)) return false;
    }
    if (option == PathOptions::DatabaseFile) {
        isFile = true;
        path = QFileDialog::getOpenFileName(nullptr, "Select Database File", pathname, "*.db");
        if (!checkFile(path)) return false;
    }
    if (!isFile) path = QFileDialog::getExistingDirectory(nullptr, "Select Path", pathname);

    if (path.isEmpty()) return false;

    switch (option) {
        case PathOptions::CurrentPath:
            if (path == m_settings.path) return false;
            m_settings.path = path;
            break;

        case PathOptions::FolderFile:
            if (path == m_settings.json) return false;
            m_settings.json = path;
            break;

        case PathOptions::DatabaseFile:
            if (path == m_settings.database) return false;
            m_settings.database = path;
            break;

        case PathOptions::FavoritesFolder:
            if (path == m_settings.favorites) return false;
            m_settings.favorites = path;
            break;

        case PathOptions::TrashFolder:
            if (path == m_settings.trash) return false;
            m_settings.trash = path;
            break;

        default:
            return false;
    }

    write();
    return true;
}

void ConfigHandler::setDatabase(bool state) {
    m_settings.databaseActive = state;
    write();
}

void ConfigHandler::initTest() {
    QString path = QDir::currentPath() + "/";
    m_settings.path = path + "samples";
    m_settings.json = path + "info_test.json";
    m_settings.imageFormats << "*.jpg";
    m_settings.mode = AppMode::Image;
    write();
}

void ConfigHandler::read() {
    QSettings ini(this->path(), QSettings::IniFormat);

    ini.beginGroup("Folders");
    m_settings.path = ini.value("path").toString();
    m_settings.json = ini.value("json").toString();
    m_settings.database = ini.value("database").toString();
    m_settings.favorites = ini.value("favorites").toString();
    m_settings.trash = ini.value("trash").toString();
    ini.endGroup();

    ini.beginGroup("Settings");
    m_settings.imageFormats = ini.value("imageFormat").toStringList();
    m_settings.videoFormats = ini.value("videoFormat").toStringList();
    m_settings.bufferSize = ini.value("bufferSize").toInt();
    m_settings.threshold = ini.value("threshold").toInt();
    m_settings.databaseActive = ini.value("databaseActive").toBool();
    m_settings.cache = ini.value("cache").toString();
    int mode = ini.value("appMode").toInt();
    if (mode > AppMode::Database) mode = 0;
    m_settings.mode = static_cast<AppMode>(mode);
    ini.endGroup();

    ini.beginGroup("QML");
    int width = ini.value("width").toInt();
    int height = ini.value("height").toInt();
    m_settings.size = QSize(width, height);
    ini.endGroup();

    checkFolder(m_settings.favorites);
    checkFolder(m_settings.trash);
    qInfo() << "Read config file";
}

void ConfigHandler::write() {
    QSettings ini(this->path(), QSettings::IniFormat);

    ini.beginGroup("Folders");
    ini.setValue("path", m_settings.path);
    ini.setValue("json", m_settings.json);
    ini.setValue("database", m_settings.database);
    ini.setValue("favorites", m_settings.favorites);
    ini.setValue("trash", m_settings.trash);
    ini.endGroup();

    ini.beginGroup("Settings");
    ini.setValue("imageFormat", m_settings.imageFormats);
    ini.setValue("videoFormat", m_settings.videoFormats);
    ini.setValue("appMode", m_settings.mode);
    ini.setValue("bufferSize", m_settings.bufferSize);
    ini.setValue("threshold", m_settings.threshold);
    ini.setValue("databaseActive", m_settings.databaseActive);
    ini.setValue("cache", m_settings.cache);
    ini.endGroup();

    ini.beginGroup("QML");
    ini.setValue("width", m_settings.size.width());
    ini.setValue("height", m_settings.size.height());
    ini.endGroup();

    qInfo() << "Write config file";
}

void ConfigHandler::defaultFile() {
    QString path = QDir::currentPath() + "/";
    m_settings.path = path + "samples";
    m_settings.json = path + "info.json";
    m_settings.database = path + "mydb.db";
    m_settings.favorites = path + "_Favorites";
    m_settings.trash = path + "_Trash";
    m_settings.cache = "folder-cache";
    m_settings.imageFormats << "*.jpg"
                            << "*.jpeg"
                            << "*.png";
    m_settings.videoFormats << "*.mp4"
                            << "*.avi";
    m_settings.size = QSize(1400, 900);
    m_settings.mode = AppMode::Gallery;
    m_settings.bufferSize = 15;
    m_settings.threshold = 15;
    m_settings.databaseActive = true;

    checkFolder(m_settings.favorites);
    checkFolder(m_settings.trash);
}

void ConfigHandler::checkFolder(QString folder) {
    QDir dir = QDir(folder);
    if (!dir.exists()) {
        if (dir.mkpath("."))
            qInfo() << "Folder: " + folder + " created";
        else
            MessageBox("Can not created folder: '" + folder + "' !");
    }
}

bool ConfigHandler::checkFile(QString file) {
    if (file.isEmpty()) return false;

    if (!QFile::exists(file)) {
        MessageBox("File does not exist: '" + file + "' !");
        return false;
    }

    return true;
}
