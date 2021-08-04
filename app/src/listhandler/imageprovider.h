#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QObject>
#include <QDebug>
#include <QQuickImageProvider>

#include "basefile/videofile.h"

/*!
 * \brief The ImageProvider class:
 * Shows QImages in qml.
 */
class ImageProvider : public QObject, public QQuickImageProvider
{
    Q_OBJECT

public:

    explicit ImageProvider(QObject *parent = nullptr);
    ~ImageProvider();
    void setFrameHash(FrameHash* hash);

    // QQuickImageProvider interface
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

private:

    FrameHash* m_frameHash;
    QImage testFrame(QSize *size, const QSize &requestedSize);
    QImage empty();

};

#endif // IMAGEPROVIDER_H
