#include "logger.h"

QString logger::filename = QDir::currentPath() + QDir::separator() + "log.txt";
bool logger::logging = false;
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

logger::logger(QObject *parent) : QObject(parent) {}

void logger::startLogging() {
    logger::logging = true;

    // Clear Log
    QFile file(logger::filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) file.close();

    qInstallMessageHandler(logger::handler);
}

void logger::handler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    if (logger::logging) {
        QString txt;
        switch (type) {
            case QtInfoMsg:
                txt = QString("Info");
                break;
            case QtDebugMsg:
                txt = QString("Debug");
                break;
            case QtWarningMsg:
                txt = QString("Warning");
                break;
            case QtCriticalMsg:
                txt = QString("Critical");
                break;
            case QtFatalMsg:
                txt = QString("Fatal");
                break;
        }

        QFile file(logger::filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream ts(&file);
            ts << QDateTime::currentDateTime().toString("hh:mm:ss") << " - " << txt << ": " << msg << " -> " << context.file
               << " line: " << context.line << Qt::endl;
            ts.flush();
            file.close();
        }
    }

    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}
