#include "visionplugin.h"


VisionPlugin::VisionPlugin()
{

}


bool VisionPlugin::showImage(const QString &path, double scale)
{
    Q_UNUSED(path)
    Q_UNUSED(scale)
    return false;
}


bool VisionPlugin::rotateImage(const QString &path, const ROTATE direction)
{
    Q_UNUSED(path)
    Q_UNUSED(direction)
    return false;
}


VisionPlugin::Frame VisionPlugin::videoFrame(const QString &path, double position, double scale, bool showImage)
{
    Q_UNUSED(path)
    Q_UNUSED(position)
    Q_UNUSED(scale)
    Q_UNUSED(showImage)
    return Frame();
}


bool VisionPlugin::initMatching(const QString &original, int matchingOption)
{
    Q_UNUSED(original)
    Q_UNUSED(matchingOption)
    return false;
}


double VisionPlugin::matchImage(const QString &path, bool printResults, bool showImage)
{
    Q_UNUSED(path)
    Q_UNUSED(printResults)
    Q_UNUSED(showImage)
    return -1;
}
