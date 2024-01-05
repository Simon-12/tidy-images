#include "test.h"

TestExiv::TestExiv() {}

void TestExiv::initTestCase() {
    // Called before the first test
    qInfo() << "Init test cases";

    // Path to example images
    QDir samples = QDir::current();
    samples.cd("../samples");
    QStringList filter;
    filter << "*.jpg";

    // Load images
    QFileInfoList list = samples.entryInfoList(filter);
    foreach (QFileInfo info, list) m_images << info.filePath();

    // Load plugin
    QDir dir = QDir::current();
    dir.cdUp();
    dir.cd("plugin");
    qInfo() << "Path:" << dir.path();
    m_plugin = QSharedPointer<ExivPlugin>(loadPlugin<ExivPlugin>(dir.path()));
}

void TestExiv::cleanupTestCase() {
    // Called after the last test
    qInfo() << "Close test cases";
}

void TestExiv::test_metaData() {
    QVERIFY(m_plugin);
    QCOMPARE_NE(m_images.size(), 0);

    // Read date
    QString image = m_images.last();
    QDateTime date = m_plugin->readDate(image);
    QCOMPARE(QDate(2008, 2, 7), date.date());
}

void TestExiv::test_label() {
    QVERIFY(m_plugin);
    QCOMPARE_NE(m_images.size(), 0);

    // Set label
    QString image = m_images.first();
    QStringList labels;
    labels << "Test Label";
    m_plugin->setLabels(image, labels);

    // Read label
    QStringList list = m_plugin->readLabels(image);
    QCOMPARE(labels.first(), list.first());
}

// Generate main()
QTEST_MAIN(TestExiv)
