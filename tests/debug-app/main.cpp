#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QThread>

#include "../util/utildebug.h"
#include "listhandler/listhandler.h"

int main() {
    // Create some files
    randomImages(1000);

    // Timer
    QElapsedTimer timer;
    timer.start();

    // Read files
    Settings settings;
    QDir dir = QDir::currentPath();
    dir.cd("images");
    settings.path = dir.absolutePath();
    settings.cache = "folder-cache";
    settings.imageFormats = QStringList() << "*.jpg";
    ListHandler* list = new ListHandler(settings, AppMode::Gallery);
    list->startLoadFiles(false);
    list->waitFilesLoaded();
    FileList* fileList = list->fileList();

    qDebug() << "Size:" << fileList->size();
    qDebug() << "Elapsed time:" << timer.elapsed() << "milliseconds";

    return 0;
}
