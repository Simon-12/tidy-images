#ifndef TEST_H
#define TEST_H

#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QObject>
#include <QPluginLoader>
#include <QtTest>

#include "visionplugin.h"

/*!
 * \brief The TestVision class:
 * Unit test for checking the vision plugin.
 */
class TestVision : public QObject {
    Q_OBJECT

public:
    TestVision();

private slots:

    void initTestCase();
    void cleanupTestCase();
    void test_frame();
    void test_matching();

private:
    QSharedPointer<VisionPlugin> m_plugin;
};

#endif  // TEST_H
