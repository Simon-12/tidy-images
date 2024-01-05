#include "test.h"

TestCommands::TestCommands() {
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

    m_listDate.append("Thu Apr 29 12:14:02 2021");
    m_listDate.append("Thu Apr 29 12:14:04 2021");
    m_listDate.append("Thu Apr 29 12:14:04 2021");
    m_listDate.append("Thu Apr 29 12:14:04 2021");
    m_listDate.append("Thu Apr 29 12:14:04 2021");
    m_listDate.append("Thu Apr 29 12:14:04 2021");
    m_listDate.append("Thu Apr 29 12:14:04 2021");
    m_listDate.append("Thu Apr 29 12:14:04 2021");
    m_listDate.append("Sun Dec 19 13:16:19 2021");
    m_listDate.append("Sun Dec 19 13:16:19 2021");
    m_listDate.append("Sun Dec 19 13:16:19 2021");
    m_listDate.append("Sun Dec 19 13:16:19 2021");
    m_listDate.append("Sun Dec 19 13:16:19 2021");
    m_listDate.append("Sun Dec 19 13:16:19 2021");
    m_listDate.append("Sun Dec 19 13:16:20 2021");
    m_listDate.append("Sun Dec 19 13:16:20 2021");
    m_listDate.append("Sun Dec 19 13:16:20 2021");
    m_listDate.append("Sun Dec 19 13:16:20 2021");
    m_listDate.append("Sun Dec 19 13:16:20 2021");
}

void TestCommands::initTestCase() {
    // Called before the first test
    qInfo() << "Init test cases";
    QScopedPointer<ConfigHandler> config(new ConfigHandler("config_test.ini"));
    config->initTest();
    QScopedPointer<FolderHandler> folder(new FolderHandler(config->settings()));
    folder->initTest();

    m_controller = QSharedPointer<QmlController>(new QmlController("config_test.ini"));
    m_controller->startLoadFiles(true);
    m_controller->waitFilesLoaded();
}

void TestCommands::cleanupTestCase() {
    // Called after the last test
    qInfo() << "Close test cases";
}

void TestCommands::test_commands() {
    // Move command
    m_controller->setIndex(0);
    QString path = QDir::currentPath() + "/Test";
    m_controller->moveFile(path);
    QString target = QDir::currentPath() + "/Test/20171117_180824.jpg";
    QVERIFY(QFile::exists(target));
    m_controller->undo();
    QVERIFY(!QFile::exists(target));
}

void TestCommands::test_sort() {
    // Sort type
    m_controller->changeOrder(1);
    m_controller->waitFilesLoaded();
    FileList* list = m_controller->fileList();
    for (int i = 0; i < list->size(); i++) {
        FilePtr file = list->at(i);
        QCOMPARE(file->formatStr(), m_listType[i]);
    }

    // Sort modified
    m_controller->changeOrder(4);
    m_controller->waitFilesLoaded();
    for (int i = 0; i < list->size(); i++) {
        FilePtr file = list->at(i);
        QCOMPARE(file->modified()->toString(), m_listDate[i]);
    }

    // Change direction
    m_controller->changeDirection(1);
    std::reverse(m_listDate.begin(), m_listDate.end());
    m_controller->waitFilesLoaded();
    for (int i = 0; i < list->size(); i++) {
        FilePtr file = list->at(i);
        QCOMPARE(file->modified()->toString(), m_listDate[i]);
    }
}

// Generate main()
QTEST_MAIN(TestCommands)
