#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include <QObject>
#include <QTime>
#include <QImage>
#include <QHash>

#include "basefile.h"
#include "plugins/visionplugin.h"

typedef QHash<QString, QImage> FrameHash;

/*!
 * \brief The VideoFile class:
 * Video file
 */
class VideoFile : public BaseFile
{
    Q_GADGET

public:

    explicit VideoFile();

    void readLabels() override;
    void setRotation(bool direction) override;
    QString frameId(){ return m_frameId; }

    static void setFrameHash(FrameHash* hash){ frameHash = hash; }
    static void setPlugin(VisionPlugin* plg){ plugin = plg; }
    static QString addFrameHash(const QString &path);

protected:

    FileFormat readFormat(QString name, QString extension) override;
    QDateTime readDateCamera() override;
    void setLabels(const QStringList &labels) override;
    void log() override;

private:

    QString m_frameId;
    static FrameHash* frameHash;
    static VisionPlugin* plugin;

    void loadVideoFrame();
    static QString addHash(const VisionPlugin::Frame &frame);
};

typedef QSharedPointer<VideoFile> VideoPtr;

#endif // VIDEOFILE_H
