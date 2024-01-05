#ifndef LOGGER_H
#define LOGGER_H

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QTextStream>

/*!
 * \brief The logger class:
 * Logger class for console output, gets saved to log file.
 */
class logger : public QObject {
    Q_OBJECT

public:
    explicit logger(QObject *parent = nullptr);

    static bool logging;
    static QString filename;
    static void startLogging();
    static void handler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:

public slots:
};

#endif  // LOGGER_H
