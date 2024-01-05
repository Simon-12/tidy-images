#include "test.h"

#include "listhandler/basefile/imagefile.h"
#include "qtestcase.h"

TestDatabase::TestDatabase() {}

void TestDatabase::initTestCase() {
    // Called before the first test
    qInfo() << "Init test cases";

    // Read in files
    QFileInfoList infoList = QDir("samples").entryInfoList(QStringList() << "*.jpg", QDir::Files);
    foreach (QFileInfo info, infoList) {
        BaseFile *file = new ImageFile();
        file->init(info, false);
        file->setLabels(QStringList() << "test");
        m_fileList.append(FilePtr(file));
    }

    // Database
    Settings set;
    set.database = "test_database.db";
    set.databaseActive = true;
    QFile file(set.database);
    if (file.exists()) file.remove();
    m_fileModel = QSharedPointer<FileModel>(new FileModel(&m_fileList));
    m_database = QSharedPointer<Database>(new Database(&m_fileList, set));
    m_database->setFileModel(m_fileModel.data());
}

void TestDatabase::cleanupTestCase() {
    // Called after the last test
    qInfo() << "Close test cases";

    m_fileList.clear();
}

void TestDatabase::test_add() {
    // Fill database
    for (int i = 0; i < m_fileList.size(); i++) {
        FilePtr file = m_fileList.at(i);
        m_database->insertFile(i, *file->path());
    }
    m_database->finished();
    QCOMPARE(m_fileModel->size(), m_fileList.size());
}

void TestDatabase::test_remove() {
    // Clear database
    for (int i = 0; i < m_fileList.size(); i++) {
        FilePtr file = m_fileList.at(i);
        m_database->removePath(*file->path());
    }
    m_database->finished();
    QCOMPARE(m_fileModel->size(), 0);
}

// Generate main()
QTEST_MAIN(TestDatabase)
