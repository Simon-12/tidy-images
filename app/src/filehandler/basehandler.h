#ifndef BASEHANDLER_H
#define BASEHANDLER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QObject>

/*!
 * \brief The BaseHandler class:
 * Interface for file handling, like read and write operations.
 */
class BaseHandler : public QObject {
    Q_OBJECT

public:
    explicit BaseHandler(QString path, QObject *parent = nullptr);
    ~BaseHandler();
    void init();

protected:
    QString path();
    QByteArray readFile();
    void writeFile(QByteArray data);

    virtual void read() = 0;
    virtual void write() = 0;
    virtual void defaultFile() = 0;

private:
    QString m_path;
    void openFile(QFile &file, QIODevice::OpenMode mode);
};

#endif  // BASEHANDLER_H
