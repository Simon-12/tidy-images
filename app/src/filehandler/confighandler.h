#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QFileDialog>
#include <QDebug>

#include "basehandler.h"
#include "../settings.h"
#include "../options.h"

/*!
 * \brief The ConfigHandler class:
 * File handler for the config ini file.
 * Reads and writes the application settings.
 */
class ConfigHandler : public BaseHandler
{
    Q_OBJECT

public:

    explicit ConfigHandler(QString path, QObject *parent = nullptr);

    Settings settings(){ return m_settings; }
    bool changePath(QString pathname, PathOptions option);
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

#endif // CONFIGHANDLER_H
