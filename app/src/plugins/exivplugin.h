#ifndef EXIVPLUGIN_H
#define EXIVPLUGIN_H

#include <QDateTime>
#include <QObject>
#include <QtPlugin>

#include "baseplugin.h"

/*!
 * \brief The ExivPlugin class:
 * Abstract exiv plugin for image metadata.
 */
class ExivPlugin : public BasePlugin
{

public:

    explicit ExivPlugin();

    virtual void exifInfo();
    virtual void exifPrint(const QString &path);
    virtual QDateTime readDate(const QString &path);
    virtual QStringList readLabels(const QString &path);
    virtual void setLabels(const QString &path, const QStringList &labels);
    virtual void readMetadata(const QString &path);
    virtual void writeMetadata(const QString &path);
};

// Declare interface
Q_DECLARE_INTERFACE(ExivPlugin, "plugin.exiv")

#endif // EXIVPLUGIN_H
