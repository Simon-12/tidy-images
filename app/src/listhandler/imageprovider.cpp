#include "imageprovider.h"

ImageProvider::ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image) { qInfo() << "Init Image Provider"; }

ImageProvider::~ImageProvider() { qInfo() << "Clear Image Provider"; }

void ImageProvider::setFrameHash(FrameHash *hash) { m_frameHash = hash; }

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    if (!m_frameHash) return empty();
    QImage image;
    if (!m_frameHash->contains(id)) {
        // Show black frame
        image = empty();
        image.fill(QColor("black").rgba());
    } else
        image = m_frameHash->value(id);

    // Resize image to size
    Q_UNUSED(size);
    if (requestedSize.width() > 0 && requestedSize.height() > 0) image = image.scaled(requestedSize, Qt::KeepAspectRatio);

    return image;
}

QImage ImageProvider::testFrame(QSize *size, const QSize &requestedSize) {
    int width = 100;
    int height = 50;

    if (size) *size = QSize(width, height);
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);
    pixmap.fill(QColor("red").rgba());

    return pixmap.toImage();
}

QImage ImageProvider::empty() { return QImage(1, 1, QImage::Format_Mono); }
