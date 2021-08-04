#ifndef TESTAPP_H
#define TESTAPP_H

#include <QObject>
#include <QDebug>
#include <QtTest>

#include "qmlcontroller.h"

/*!
 * \brief The TestApp class:
 * Unit test for checking the application start and file loading.
 */
class TestApp : public QObject
{
    Q_OBJECT

public:

    TestApp();

private slots:

    void initTestCase();
    void cleanupTestCase();
    void test_commands();
    void test_sort();

private:

    QSharedPointer<QmlController> m_controller;
    QStringList m_listType;
    QStringList m_listDate;
};

#endif // TESTAPP_H
