#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QDebug>
#include <QObject>
#include <QQuickImageProvider>

#include "basefile/videofile.h"

/*!
 * \brief The ImageProvider class:
 * Shows QImages in qml.
 */
class ImageProvider : public QQuickImageProvider {
    Q_OBJECT

public:
    explicit ImageProvider();
    ~ImageProvider();
    void setFrameHash(FrameHash *hash);

    // QQuickImageProvider interface
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

private:
    FrameHash *m_frameHash;
    QImage testFrame(QSize *size, const QSize &requestedSize);
    QImage empty();
};

#endif  // IMAGEPROVIDER_H
