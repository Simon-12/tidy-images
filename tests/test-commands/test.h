#ifndef TEST_H
#define TEST_H

#include <QDebug>
#include <QObject>
#include <QtTest>

#include "qmlcontroller.h"

/*!
 * \brief The TestCommands class:
 * Unit test for checking the application start and file loading.
 */
class TestCommands : public QObject {
    Q_OBJECT

public:
    TestCommands();

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

#endif  // TEST_H
