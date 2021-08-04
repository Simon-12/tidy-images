#include "comparelist.h"


VisionPlugin* CompareList::m_plugin = nullptr;


CompareList::CompareList(FileList* list, Settings set, QObject *parent) : QObject(parent)
{
    m_fileList = list;
    m_tableModel = new TableModel(m_fileList, set.threshold, this);

    connect(&m_watcherCompare, &QFutureWatcher<double>::started, this, &CompareList::startedCompare);
    connect(&m_watcherCompare, &QFutureWatcher<double>::resultReadyAt, this, &CompareList::compareIndex);
    connect(&m_watcherCompare, &QFutureWatcher<double>::finished, this, &CompareList::finishedCompare);
}


void CompareList::startCompare(int index)
{
    if(!m_plugin)
    {
        qCritical() << "No vision plugin installed";
        return;
    }

    qInfo() << "Start Compare";
    QStringList list;
    for(int i = 0; i < m_fileList->size(); i++)
    {
        QString file = *m_fileList->at(i)->path();
        list << file;

        if(i == index)
        {
            if(m_plugin->initMatching(file))
                qInfo() << "Init matching";
            else
            {
                qInfo() << "Error at init matching";
                return;
            }
        }
    }

    m_futureCompare = QtConcurrent::mapped(list, compareImage);
    m_watcherCompare.setFuture(m_futureCompare);
}


void CompareList::stopCompare()
{
    m_watcherCompare.cancel();
    m_watcherCompare.waitForFinished();
}


void CompareList::setPlugin(VisionPlugin *plugin)
{
    m_plugin = plugin;
    m_tableModel->setActive(m_plugin != nullptr);
}


double CompareList::compareImage(QString path) // static
{
    return m_plugin->matchImage(path);
}


void CompareList::startedCompare()
{
    m_timer.start();
}


void CompareList::compareIndex(int index)
{
    qInfo() << "Compare step:" << index;
    emit compareStep();
}


void CompareList::finishedCompare()
{
    if(m_futureCompare.isCanceled())
    {
        qInfo() << "Stopped Compare";
        return;
    }

    QString time = QString::number(m_timer.elapsed());
    qInfo() << "Finished Compare: " + time + " ms";

    // Get results and set score
    QList<double> list = m_futureCompare.results();
    for(int i = 0; i < m_fileList->size(); i++)
    {
        ImagePtr file = m_fileList->at(i).staticCast<ImageFile>();
        file->setScore(list[i]);
    }

    emit compareFinished();
}
