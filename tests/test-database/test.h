#ifndef TEST_H
#define TEST_H

#include <QDebug>
#include <QDir>
#include <QObject>
#include <QtTest>

#include "listhandler/database/database.h"

/*!
 * \brief The TestDatabase class:
 * Unit test for checking the database handling.
 */
class TestDatabase : public QObject {
    Q_OBJECT

public:
    TestDatabase();

private slots:

    void initTestCase();
    void cleanupTestCase();
    void test_add();
    void test_remove();

private:
    QSharedPointer<Database> m_database;
    QSharedPointer<FileModel> m_fileModel;
    FileList m_fileList;
};

#endif  // TEST_H
