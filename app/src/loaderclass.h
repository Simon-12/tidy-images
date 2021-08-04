#ifndef LOADERCLASS_H
#define LOADERCLASS_H

#include <QObject>
#include <QDebug>
#include <QVector>

#include "options.h"

/*!
 * \brief The LoaderClass class:
 * Handels the progress and updates the qml progress bars.
 */
class LoaderClass : public QObject
{
    Q_OBJECT

public:

    Q_PROPERTY(int step READ getStep WRITE setStep NOTIFY stepChanged)
    Q_PROPERTY(int progress READ getProgress NOTIFY progressChanged)
    Q_PROPERTY(bool open READ getOpen NOTIFY openChanged)
    Q_PROPERTY(int size READ getSize NOTIFY sizeChanged)
    Q_PROPERTY(int bufferSize READ getBuffer NOTIFY bufferChanged)
    Q_PROPERTY(QString text READ getText NOTIFY textChanged)

    explicit LoaderClass(int buffer, QObject *parent = nullptr);
    void initLoader(AppMode mode);

public slots:

    void startLoading(int size);
    void loadFile(int index);
    void loadImage(int index);
    void singleStep();

private:

    QVector<int> m_files;
    QVector<int> m_images;
    AppMode m_mode;
    int m_bufferSize;

    void setDialog(bool open);

    // Propertys
    bool m_open;
    int m_size;
    int m_progress;
    int m_step;
    QString m_text;
    bool getOpen(){ return m_open; }
    int getSize(){ return m_size; }
    int getBuffer(){ return m_bufferSize; }
    int getProgress(){ return m_progress; }
    void setProgress(int progress);
    int getStep(){ return m_step; }
    void setStep(int step);
    QString getText() { return m_text; }

signals:

    void openChanged();
    void sizeChanged();
    void progressChanged();
    void stepChanged();
    void textChanged();
    void bufferChanged();
};


#endif // LOADERCLASS_H
