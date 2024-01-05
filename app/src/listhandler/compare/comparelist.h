#ifndef COMPARELIST_H
#define COMPARELIST_H

#include <QDebug>
#include <QElapsedTimer>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>
#include <QtConcurrent>

#include "plugins/visionplugin.h"
#include "settings.h"
#include "tablemodel.h"

/*!
 * \brief The CompareList class:
 * Compare class for the file list, handels the compare thread.
 */
class CompareList : public QObject {
    Q_OBJECT

public:
    explicit CompareList(FileList* list, Settings set, QObject* parent = nullptr);

    void startCompare(int index);
    void stopCompare();
    TableModel* tableModel() { return m_tableModel; }
    void setPlugin(VisionPlugin* plugin);

signals:

    void compareStep();
    void compareFinished();

private:
    FileList* m_fileList;
    TableModel* m_tableModel;
    QElapsedTimer m_timer;
    QFuture<double> m_futureCompare;
    QFutureWatcher<double> m_watcherCompare;
    static VisionPlugin* m_plugin;

    static double compareImage(QString path);

private slots:

    void startedCompare();
    void compareIndex(int index);
    void finishedCompare();
};

#endif  // COMPARELIST_H
