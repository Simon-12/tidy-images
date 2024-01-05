#ifndef OPENCVPLUGIN_H
#define OPENCVPLUGIN_H

#if defined(OPENCV_PLUGIN_LIBRARY)
#define OPENCV_PLUGIN_EXPORT Q_DECL_EXPORT
#else
#define OPENCV_PLUGIN_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "visionplugin.h"

/*!
 * \brief The OpenCVPlugin class:
 * Specific vision plugin for image processing functions.
 */
class OPENCV_PLUGIN_EXPORT OpenCVPlugin : public QObject, public VisionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugin.vision")
    Q_INTERFACES(VisionPlugin)

public:
    explicit OpenCVPlugin(QObject *parent = nullptr);

    // VisionPlugin interface
public:
    bool rotateImage(const QString &path, const ROTATE direction) override;
    Frame videoFrame(const QString &path, double position) override;
    bool initMatching(const QString &original, int matchingOption) override;
    double matchImage(const QString &path, bool printResults) override;

private:
    cv::Mat m_image;
    cv::Mat m_original;
    cv::Mat m_descriptor;
    cv::Ptr<cv::Feature2D> m_detector;
    cv::Ptr<cv::BFMatcher> m_matcher;
    std::vector<cv::KeyPoint> m_keypoints;
};

#endif  // OPENCVPLUGIN_H
