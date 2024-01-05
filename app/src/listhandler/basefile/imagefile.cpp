#include "imagefile.h"

ExivPlugin* ImageFile::plugin = nullptr;

ImageFile::ImageFile() {
    m_filetype = FileType::Image;
    m_score = 0;
}

BaseFile::FileFormat ImageFile::readFormat(QString name, QString extension) {
    // Check default
    if ((!extension.contains("jpg", Qt::CaseInsensitive)) && (!extension.contains("jpeg", Qt::CaseInsensitive)))
        return FileFormat::Other;

    // Set dimensions
    QSize img = QImageReader(m_path).size();
    m_dimensions = QString("%1x%2").arg(img.width()).arg(img.height());

    // WhatsApp
    // Example: IMG-20151206-WA0000.jpg
    if (name.startsWith("IMG-")) return FileFormat::Message;

    // Signal
    // Example: signal-2021-09-18-183330.jpeg
    if (name.startsWith("signal-")) return FileFormat::Message;

    // Camera
    // Example: IMG_6687.JPG
    if (name.startsWith("IMG_")) return FileFormat::Camera;

    // Mobile
    // Check only digits
    // Example: 20170629_180824.jpg
    // Example: PXL_20221119_122755414.jpg
    name.remove("PXL_");
    QString test = name.remove(extension).remove(".").remove("_");
    if (m_rexp.match(test).hasMatch())
        return FileFormat::Mobile;
    else
        return FileFormat::Other;
}

QDateTime ImageFile::readDateCamera() {
    if (plugin)
        return plugin->readDate(m_path);
    else
        return QDateTime(QDate(1, 1, 1), QTime(0, 0));
}

void ImageFile::log() { qInfo() << "Read image:" << m_name << "- Labels:" << m_labels; }

void ImageFile::readLabels() {
    if (plugin) m_labels = plugin->readLabels(m_path);
}

void ImageFile::setLabels(const QStringList& labels) {
    m_labels = labels;
    if (plugin) plugin->setLabels(m_path, m_labels);
    qInfo() << "Set labels from image:" << m_name << " - Labels:" << m_labels;
}

void ImageFile::setRotation(bool direction) {
    if (direction) {
        m_rotation += 90;
        if (m_rotation == 360) m_rotation = 0;
    } else {
        m_rotation -= 90;
        if (m_rotation < 0) m_rotation = 270;
    }
}

QString ImageFile::sizeStr() {
    QString str = m_size + " MB";
    if (m_dimensions.isEmpty()) return str;
    return str + "\t" + m_dimensions;
}

QString ImageFile::scoreStr() {
    if (m_score == 0) return "0";
    return QString::number(m_score, 'g', 3);
}

QDataStream& operator<<(QDataStream& stream, const ImageFile& file) {
    stream << static_cast<const BaseFile&>(file);
    stream << file.m_dimensions;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, ImageFile& file) {
    stream >> static_cast<BaseFile&>(file);
    stream >> file.m_dimensions;
    return stream;
}
