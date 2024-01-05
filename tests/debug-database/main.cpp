#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>

#include "../util/utildebug.h"
#include "listhandler/database/sqlhandler.h"

void debugDatabase(const FileList& fileList) {
    // Database
    SqlHandler* handler = new SqlHandler("Main", "test_database.db", nullptr, false);

    // Fill database
    for (int i = 0; i < fileList.size(); i++) {
        FilePtr file = fileList.at(i);
        handler->addFile(file, *file->path());
    }

    // Clear database
    QList<int> items;
    items << 10 << 20 << 30 << 40 << 50;
    foreach (int i, items) {
        FilePtr file = fileList.at(i);
        handler->removeFile(*file->path());
    }

    delete handler;
}

int main() {
    // Create some files
    randomImages(100);

    // Timer
    QElapsedTimer timer;

    // Read files
    FileList fileList;
    readFiles(fileList);

    // Debug database
    timer.start();
    debugDatabase(fileList);
    qDebug() << "Elapsed time:" << timer.elapsed() << "milliseconds";

    fileList.clear();
    return 0;
}
