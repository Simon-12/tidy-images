#ifndef TEST_H
#define TEST_H

#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QObject>
#include <QPluginLoader>
#include <QtTest>

#include "exivplugin.h"

/*!
 * \brief The TestExiv class:
 * Unit test for checking the exiv plugin.
 */
class TestExiv : public QObject {
    Q_OBJECT

public:
    TestExiv();

private slots:

    void initTestCase();
    void cleanupTestCase();
    void test_metaData();
    void test_label();

private:
    QSharedPointer<ExivPlugin> m_plugin;
    QStringList m_images;
};

#endif  // TEST_H
