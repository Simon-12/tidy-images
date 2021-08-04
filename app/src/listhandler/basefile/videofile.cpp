#include "videofile.h"


FrameHash* VideoFile::frameHash = nullptr;
VisionPlugin* VideoFile::plugin = nullptr;


VideoFile::VideoFile()
{
    m_filetype = FileType::Video;
}


BaseFile::FileFormat VideoFile::readFormat(QString name, QString extension)
{
    // Load frame
    loadVideoFrame();

    // Check default
    if(!extension.contains("mp4", Qt::CaseInsensitive))
        return FileFormat::Other;

    // Check first 4 chars
    // Example: VID-20151206-WA0000.mp4
    if(name.mid(0,4) == "VID-")
        return FileFormat::Message;

    // Check first 4 chars
    // Example: IMG_6687.mp4
    if(name.mid(0,4) == "IMG_")
        return FileFormat::Camera;
    // Example: GOPR0280.mp4
    if(name.mid(0,4) == "GOPR")
        return FileFormat::Camera;

    // Check only digits
    // Example: 20170629_180824.mp4
    QString test = name.
            remove(extension).
            remove(".").
            remove("_");
    QRegExp re("\\d*");  // digit (\d) + zero or more times (*)
    if (re.exactMatch(test))
        return FileFormat::Mobile;
    else
        return FileFormat::Other;
}


QDateTime VideoFile::readDateCamera()
{
    // Use created time
    return m_created;
}


void VideoFile::log()
{
    qInfo() << "Read video:" << m_name;
}


void VideoFile::setLabels(const QStringList &labels)
{
    m_labels = labels;
    qInfo() << "Set labels from video:" << m_name << " - Labels:" << m_labels;
}


void VideoFile::readLabels()
{

}


void VideoFile::setRotation(bool direction)
{
    Q_UNUSED(direction)
}


void VideoFile::loadVideoFrame()
{
    if(!plugin) return;
    VisionPlugin::Frame frame =  plugin->videoFrame(m_path, 0.01, 1);
    QTime time = QTime::fromMSecsSinceStartOfDay((int)frame.duration * 1000);
    m_duration = time.toString("hh:mm:ss");
    m_frameId = addHash(frame);
}


QString VideoFile::addHash(const VisionPlugin::Frame &frame) // static
{
    QImage image = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    image = image.rgbSwapped();
    QString id = QString::number(frameHash->size());
    frameHash->insert(id, image);
    return id;
}


QString VideoFile::addFrameHash(const QString &path) // static
{
    if(!plugin) return "-1";
    VisionPlugin::Frame frame = plugin->videoFrame(path);
    return addHash(frame);
}
