#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QPluginLoader>

#include "exivplugin.h"

#ifdef APP_STATIC_PLUGINS
Q_IMPORT_PLUGIN(Exiv2Plugin)
#endif

QStringList exampleImages() {
    // Path to example images
    QDir dir = QDir::current();
    dir.cd("../samples");

    QStringList filter;
    filter << "*.jpg";
    QFileInfoList list = dir.entryInfoList(filter);

    QStringList images;
    foreach (QFileInfo info, list) images << info.filePath();

    return images;
}

void setLabels(ExivPlugin* plugin, const QString& image, QStringList labels) {
    QString file = "test.jpg";
    QFile::copy(image, file);
    if (!QFile::exists(file)) return;

    qDebug() << plugin->readLabels(file);
    plugin->setLabels(file, labels);
    qDebug() << plugin->readLabels(file);
}

void metaData(ExivPlugin* plugin, const QString& source, const QString& target) {
    QString from = "original.jpg";
    QFile::copy(source, from);
    if (!QFile::exists(from)) return;

    QString to = "target.jpg";
    QFile::copy(target, to);
    if (!QFile::exists(to)) return;

    plugin->readMetadata(from);
    plugin->writeMetadata(to);
}

int main() {
    QDir dir = QDir::current();
    dir.cdUp();
    dir.cd("plugin");
    qDebug() << "Path:" << dir.path();

    ExivPlugin* plugin = loadPlugin<ExivPlugin>(dir.path());
    if (plugin) {
        qDebug() << "Name:" << plugin->name();
        plugin->exifInfo();

        QStringList examples = exampleImages();
        QString image = examples[4];
        // plugin->exifPrint(image);
        qDebug() << plugin->readDate(image);
        // qDebug() << plugin->readLabels(image);
        // setLabels(plugin, image, QStringList() << "Pengu");
        // metaData(plugin, image, examples[5]);
    }

    return 0;
}
