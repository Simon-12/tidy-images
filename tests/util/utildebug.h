#ifndef UTILDDEBUG_H
#define UTILDDEBUG_H

#include <QDebug>
#include <QDir>
#include <QImage>
#include <QObject>
#include <QRandomGenerator>

#include "listhandler/basefile/imagefile.h"

void randomImages(int quantity) {
    QString path = "images";
    int imgSize = 10;

    // Create folder
    QDir folder(path);
    if (!folder.exists()) folder.mkpath(".");

    for (int i = 0; i < quantity; i++) {
        // Filename
        QString name = path + QString("/%1.jpg").arg(i, 4, 10, QChar('0'));
        QFile file(name);
        if (file.exists()) continue;  // skip
        qDebug() << name;

        // Create image and fill it with random pixel values
        QImage image(imgSize, imgSize, QImage::Format_RGB32);
        for (int x = 0; x < imgSize; x++) {
            for (int y = 0; y < imgSize; y++) {
                int r = QRandomGenerator::global()->bounded(256);
                int g = QRandomGenerator::global()->bounded(256);
                int b = QRandomGenerator::global()->bounded(256);
                image.setPixel(x, y, qRgb(r, g, b));
            }
        }

        // Save as a JPG file
        file.open(QIODevice::WriteOnly);
        image.save(&file, "JPG");
    }
}

void readFiles(FileList& fileList) {

    QFileInfoList infoList = QDir("images").entryInfoList(QStringList() << "*.jpg", QDir::Files);

    foreach (QFileInfo info, infoList) {
        BaseFile* file = new ImageFile();
        file->init(info, false);
        fileList.append(FilePtr(file));
    }
}

#endif  // UTILDDEBUG_H
