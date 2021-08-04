#include "opencvplugin.h"


OpenCVPlugin::OpenCVPlugin(QObject *parent) : QObject(parent)
{
    m_name = "OpenCV Plugin";
    m_icon = ":/opencv/icon.png";
    m_info = "Open source computer vision library";
    m_link = "https://github.com/opencv/opencv";
    m_version = QString::fromStdString(CV_VERSION);

    // Force loading of the resources
    Q_INIT_RESOURCE(resource_opencv);
}


bool OpenCVPlugin::showImage(const QString &path, double scale)
{
    cv::Mat image = cv::imread(path.toStdString().c_str(), cv::IMREAD_COLOR);

    if(image.empty())
        return false;

    if(scale < 1.0)
        cv::resize(image, image, cv::Size(), scale, scale);

    cv::imshow("Image", image);
    cv::waitKey();

    return true;
}


bool OpenCVPlugin::rotateImage(const QString &path, const VisionPlugin::ROTATE direction)
{
    cv::Mat image = cv::imread(path.toStdString().c_str(), cv::IMREAD_COLOR);
    cv::rotate(image, image, direction);
    return cv::imwrite(path.toStdString().c_str(), image);
}


VisionPlugin::Frame OpenCVPlugin::videoFrame(const QString &path, double position, double scale, bool showImage)
{
    // Open the video file
    cv::VideoCapture cap(path.toStdString(), cv::CAP_MSMF); // Microsoft Media Foundation (via videoInput)
    if (!cap.isOpened())
    {
        qCritical() << "Could not open or find the video";
        return Frame();
    }

    cap.set(cv::CAP_PROP_POS_AVI_RATIO, position); // Relative position: 0=start, 1=end.
    //cap.set(cv::CAP_PROP_POS_MSEC, position); // Current position in milliseconds
    cap >> m_image; // Keep current image in memory
    double fps = cap.get(cv::CAP_PROP_FPS);
    double frames = cap.get(cv::CAP_PROP_FRAME_COUNT);
    double duration = frames / fps;
    cap.release();

    // Shrink frame down
    cv::resize(m_image, m_image, cv::Size(), scale, scale);
    if (showImage)
    {
        cv::imshow("Display", m_image);
        cv::waitKey();
    }

    Frame frame;
    frame.rows = m_image.rows;
    frame.cols = m_image.cols;
    frame.step = (int)m_image.step;
    frame.duration = duration;
    frame.data = m_image.data;
    return frame;
}


bool OpenCVPlugin::initMatching(const QString &original, int matchingOption)
{
    // Read in image
    m_original = cv::imread(original.toStdString().c_str(), cv::IMREAD_COLOR);
    if (m_original.empty())
        return false;

    // Init detector
    cv::Ptr<cv::AKAZE> detc; // For option 1
    switch (matchingOption)
    {
    case 0:
        m_detector = cv::ORB::create(1000);
        break;
    case 1:
        detc = cv::AKAZE::create();
        detc->setThreshold(0.008f);
        m_detector = detc;
        break;
    default:
        return false;
        break;
    }

    // Init matcher
    m_matcher = cv::BFMatcher::create(cv::NORM_HAMMING);

    // Detect the keypoints using specific Detector, compute the descriptors for original
    m_detector->detectAndCompute(m_original, cv::noArray(), m_keypoints, m_descriptor);
    if (m_keypoints.empty() || m_descriptor.empty())
        return false;

    return true;
}


double OpenCVPlugin::matchImage(const QString &path, bool printResults, bool showImage)
{
    // Read in image
    cv::Mat image;
    image = cv::imread(path.toStdString().c_str(), cv::IMREAD_COLOR);
    if (image.empty())
        return -1.0;

    // Detect the keypoints using specific Detector, compute the descriptors for image
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptor;
    m_detector->detectAndCompute(image, cv::noArray(), keypoints, descriptor);
    if (keypoints.empty() || m_descriptor.empty())
        return 0.0;

    // Matching descriptor vectors with matcher
    std::vector< std::vector<cv::DMatch> > knn_matches;
    m_matcher->knnMatch(m_descriptor, descriptor, knn_matches, 2);
    if (knn_matches.empty())
        return 0.0;

    // Filter matches using the Lowe's ratio test
    std::vector<cv::DMatch> good_matches;
    const float ratio_thresh = 0.7f;
    for (size_t i = 0; i < knn_matches.size(); i++)
    {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
        {
            good_matches.push_back(knn_matches[i][0]);
        }
    }
    if (good_matches.empty())
        return 0.0;
    double ratio = (double)good_matches.size() / (double)knn_matches.size() * 100.0;

    if (printResults)
    {
        qInfo() << "Matches: " << knn_matches.size();
        qInfo() << "Good Matches: " << good_matches.size();
        qInfo() << "Ratio: " << ratio;
        qInfo() << "- - - - -";
    }

    if (showImage)
    {
        // Draw matches
        cv::Mat matches;
        cv::drawMatches(m_original, m_keypoints, image, keypoints, good_matches, matches,
                        cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(),
                        cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

        // Show detected matches
        cv::resize(matches, matches, cv::Size(), 0.25, 0.25);
        cv::imshow("Matches", matches);
        cv::waitKey();
    }

    return ratio;
}
