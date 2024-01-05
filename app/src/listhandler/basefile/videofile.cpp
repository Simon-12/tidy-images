#include "videofile.h"

FrameHash *VideoFile::frameHash = nullptr;
VisionPlugin *VideoFile::plugin = nullptr;

VideoFile::VideoFile() { m_filetype = FileType::Video; }

BaseFile::FileFormat VideoFile::readFormat(QString name, QString extension) {
    // Load frame
    loadVideoFrame();

    // Check default
    if (!extension.contains("mp4", Qt::CaseInsensitive)) return FileFormat::Other;

    // WhatsApp
    // Example: VID-20151206-WA0000.mp4
    if (name.startsWith("VID-")) return FileFormat::Message;

    // Signal
    // Example: signal-2021-09-18-183330.jpeg
    if (name.startsWith("signal-")) return FileFormat::Message;

    // Camera
    // Example: IMG_6687.mp4
    if (name.startsWith("IMG_")) return FileFormat::Camera;
    // Example: GOPR0280.mp4
    if (name.startsWith("GOPR")) return FileFormat::Camera;

    // Mobile
    // Check only digits
    // Example: 20170629_180824.mp4
    // Example: PXL_20221119_122755414.jpg
    name.remove("PXL_");
    QString test = name.remove(extension).remove(".").remove("_");
    if (m_rexp.match(test).hasMatch())
        return FileFormat::Mobile;
    else
        return FileFormat::Other;
}

QDateTime VideoFile::readDateCamera() {
    // Use created time
    return m_created;
}

void VideoFile::log() { qInfo() << "Read video:" << m_name; }

void VideoFile::setLabels(const QStringList &labels) {
    m_labels = labels;
    qInfo() << "Set labels from video:" << m_name << " - Labels:" << m_labels;
}

void VideoFile::readLabels() {}

void VideoFile::setRotation(bool direction) { Q_UNUSED(direction) }

void VideoFile::loadVideoFrame() {
    if (!plugin) return;
    VisionPlugin::Frame frame = plugin->videoFrame(m_path, 1000);
    QTime time = QTime::fromMSecsSinceStartOfDay((int)frame.duration * 1000);
    m_duration = time.toString("hh:mm:ss");
    m_frameId = addHash(frame);
}

QString VideoFile::addHash(const VisionPlugin::Frame &frame)  // static
{
    QImage image = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    image = image.rgbSwapped();
    QString id = QString::number(frameHash->size());
    frameHash->insert(id, image);
    return id;
}

QString VideoFile::addFrameHash(const QString &path)  // static
{
    if (!plugin) return "-1";
    VisionPlugin::Frame frame = plugin->videoFrame(path);
    return addHash(frame);
}
