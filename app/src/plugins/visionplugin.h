#ifndef VISIONPLUGIN_H
#define VISIONPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "baseplugin.h"

/*!
 * \brief The VisionPlugin class:
 * Abstract vision plugin for image processing functions.
 */
class VisionPlugin : public BasePlugin
{

public:

    explicit VisionPlugin();

    struct Frame {
        int rows;
        int cols;
        int step;
        double duration;
        unsigned char* data;
    };

    enum ROTATE {
        CLOCKWISE_90,
        ROTATE_180,
        COUNTERCLOCKWISE_90
    };

    virtual bool showImage(const QString &path, double scale = 1.0);
    virtual bool rotateImage(const QString &path, const ROTATE direction);
    virtual Frame videoFrame(const QString &path, double position = 0.01, double scale = 0.25, bool showImage = false);
    virtual bool initMatching(const QString &original, int matchingOption = 0);
    virtual double matchImage(const QString &path, bool printResults = false, bool showImage = false);
};

// Declare interface
Q_DECLARE_INTERFACE(VisionPlugin, "plugin.vision")

#endif // VISIONPLUGIN_H
