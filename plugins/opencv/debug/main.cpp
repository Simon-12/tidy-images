#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QPluginLoader>

#include "visionplugin.h"

#ifdef APP_STATIC_PLUGINS
Q_IMPORT_PLUGIN(OpenCVPlugin)
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

void videoFrame(VisionPlugin* plugin) {
    QDir dir = QDir::current();
    dir.cd("../samples");
    QString video = dir.path() + "/load.mp4";
    qDebug() << video;

    VisionPlugin::Frame frame = plugin->videoFrame(video, 1000);
    qDebug() << "Rows: " << frame.rows;
    qDebug() << "Cols: " << frame.cols;
    qDebug() << "Step: " << frame.step;
    qDebug() << "Duration: " << frame.duration;
    qDebug() << "Data: " << *frame.data;
}

void matching(VisionPlugin* plugin, const QStringList& images) {
    bool check = plugin->initMatching(images[0]);
    qDebug() << "Init Matching:" << check;

    if (!check) return;

    foreach (QString image, images) {
        double result = plugin->matchImage(image);
        qDebug() << "Result: " << result;
    }
}

void rotate(VisionPlugin* plugin, const QString& image, VisionPlugin::ROTATE rotation) {
    QString file = "test.jpg";
    QFile::copy(image, file);
    if (!QFile::exists(file)) return;
    plugin->rotateImage(file, rotation);
}

int main() {
    QDir dir = QDir::current();
    dir.cdUp();
    dir.cd("plugin");
    qDebug() << "Path:" << dir.path();

    VisionPlugin* plugin = loadPlugin<VisionPlugin>(dir.path());
    if (plugin) {
        qDebug() << "Name:" << plugin->name();
        QStringList examples = exampleImages();
        videoFrame(plugin);
        // matching(plugin, examples);
        // rotate(plugin, examples[2], VisionPlugin::ROTATE_180);
    }

    return 0;
}
