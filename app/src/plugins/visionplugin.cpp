#include "visionplugin.h"

VisionPlugin::VisionPlugin() {}

bool VisionPlugin::rotateImage(const QString &path, const ROTATE direction) {
    Q_UNUSED(path)
    Q_UNUSED(direction)
    return false;
}

VisionPlugin::Frame VisionPlugin::videoFrame(const QString &path, double position) {
    Q_UNUSED(path)
    Q_UNUSED(position)
    return Frame();
}

bool VisionPlugin::initMatching(const QString &original, int matchingOption) {
    Q_UNUSED(original)
    Q_UNUSED(matchingOption)
    return false;
}

double VisionPlugin::matchImage(const QString &path, bool printResults) {
    Q_UNUSED(path)
    Q_UNUSED(printResults)
    return -1;
}
