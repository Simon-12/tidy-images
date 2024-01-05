#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QObject>
#include <QSettings>

#include "../options.h"
#include "../settings.h"
#include "basehandler.h"

/*!
 * \brief The ConfigHandler class:
 * File handler for the config ini file.
 * Reads and writes the application settings.
 */
class ConfigHandler : public BaseHandler {
    Q_OBJECT

public:
    explicit ConfigHandler(QString path, QObject *parent = nullptr);

    Settings settings() { return m_settings; }
    bool changePath(QString pathname, PathOptions option);
    void setDatabase(bool state);
    void initTest();

private:
    Settings m_settings;

    void checkFolder(QString folder);
    bool checkFile(QString file);

    // BaseHandler interface
protected:
    void read();
    void write();
    void defaultFile();
};

#endif  // CONFIGHANDLER_H
