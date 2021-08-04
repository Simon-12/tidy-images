#include "testapp.h"


TestApp::TestApp()
{
    m_listType.append("Camera");
    m_listType.append("Mobile");
    m_listType.append("Message");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");
    m_listType.append("Other");

    m_listDate.append("Do Apr 15 14:26:38 2021");
    m_listDate.append("Fr Apr 16 16:38:54 2021");
    m_listDate.append("Fr Apr 16 16:40:04 2021");
    m_listDate.append("Fr Apr 16 16:41:06 2021");
    m_listDate.append("Fr Apr 16 16:42:27 2021");
    m_listDate.append("Fr Apr 16 16:44:49 2021");
    m_listDate.append("Fr Apr 16 16:46:14 2021");
    m_listDate.append("Fr Apr 16 16:48:26 2021");
    m_listDate.append("Fr Apr 16 16:49:23 2021");
    m_listDate.append("Sa Apr 17 09:37:21 2021");
    m_listDate.append("Do Apr 29 12:14:02 2021");
    m_listDate.append("Do Apr 29 12:14:04 2021");
    m_listDate.append("Do Apr 29 12:14:04 2021");
    m_listDate.append("Do Apr 29 12:14:04 2021");
    m_listDate.append("Do Apr 29 12:14:04 2021");
    m_listDate.append("Do Apr 29 12:14:04 2021");
    m_listDate.append("Do Apr 29 12:14:04 2021");
    m_listDate.append("Do Apr 29 12:14:04 2021");
    m_listDate.append("Fr Apr 30 11:01:25 2021");
}


void TestApp::initTestCase()
{
    // Called before the first test
    qInfo() << "Init test cases";
    QScopedPointer<ConfigHandler> config(new ConfigHandler("config_test.ini"));
    config->initTest();
    QScopedPointer<FolderHandler> folder(new FolderHandler(config->settings()));
    folder->initTest();

    m_controller = QSharedPointer<QmlController>(new QmlController("config_test.ini"));
    QThread::sleep(5); // Wait some time for thread finished
}


void TestApp::cleanupTestCase()
{
    // Called after the last test
    qInfo() << "Close test cases";
}


void TestApp::test_commands()
{
    // Move command
    m_controller->setIndex(0);
    QString path = QDir::currentPath() + "/Test";
    m_controller->moveFile(path);
    QString target = QDir::currentPath() + "/Test/20171117_180824.jpg";
    QVERIFY(QFile::exists(target));
    m_controller->undo();
    QVERIFY(!QFile::exists(target));
}


void TestApp::test_sort()
{
    // Sort type
    m_controller->changeOrder(1);
    QThread::sleep(5); // Wait some time for thread finished
    FileList* list = m_controller->fileList();
    for(int i = 0; i < list->size(); i++)
    {
        FilePtr file = list->at(i);
        QCOMPARE(file->formatStr(), m_listType[i]);
    }

    // Sort modified
    m_controller->changeOrder(4);
    QThread::sleep(5); // Wait some time for thread finished
    for(int i = 0; i < list->size(); i++)
    {
        FilePtr file = list->at(i);
        QCOMPARE(file->modified()->toString(), m_listDate[i]);
    }

    // Change direction
    m_controller->changeDirection(1);
    std::reverse(m_listDate.begin(), m_listDate.end());
    QThread::sleep(5); // Wait some time for thread finished
    for(int i = 0; i < list->size(); i++)
    {
        FilePtr file = list->at(i);
        QCOMPARE(file->modified()->toString(), m_listDate[i]);
    }
}


// Generate main()
QTEST_MAIN(TestApp)
