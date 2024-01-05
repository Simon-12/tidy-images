#include "test.h"

TestVision::TestVision() {}

void TestVision::initTestCase() {
    // Called before the first test
    qInfo() << "Init test cases";

    // Load plugin
    QDir dir = QDir::current();
    dir.cdUp();
    dir.cd("plugin");
    qInfo() << "Path:" << dir.path();
    m_plugin = QSharedPointer<VisionPlugin>(loadPlugin<VisionPlugin>(dir.path()));
}

void TestVision::cleanupTestCase() {
    // Called after the last test
    qInfo() << "Close test cases";
}

void TestVision::test_frame() {
    QVERIFY(m_plugin);

    // Video file
    QDir dir = QDir::current();
    dir.cd("../samples");
    QString video = dir.path() + "/load.mp4";
    qInfo() << video;
    QVERIFY(!video.isEmpty());

    // Read frame
    VisionPlugin::Frame frame = m_plugin->videoFrame(video, 0.01);
    qInfo() << "Rows: " << frame.rows;
    qInfo() << "Cols: " << frame.cols;
    qInfo() << "Step: " << frame.step;
    qInfo() << "Duration: " << frame.duration;
    qInfo() << "Data: " << *frame.data;
    QCOMPARE_NE(frame.rows, 0);
    QCOMPARE_NE(frame.cols, 0);
}

void TestVision::test_matching() {
    QVERIFY(m_plugin);

    // Read images
    QDir dir = QDir::current();
    dir.cd("../samples");
    QStringList images;
    images << dir.path() + "/IMG-20190221-WA0000.jpg";
    images << dir.path() + "/panel.jpg";

    // Init matching
    bool check = m_plugin->initMatching(images[0]);
    qInfo() << "Init Matching:" << check;
    QVERIFY(check);

    // Start matching
    foreach (QString image, images) {
        double result = m_plugin->matchImage(image);
        qInfo() << "Result: " << result;
        QCOMPARE_GT(result, 10);
    }
}

// Generate main()
QTEST_MAIN(TestVision)
