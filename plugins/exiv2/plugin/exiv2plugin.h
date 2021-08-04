#ifndef EXIV2PLUGIN_H
#define EXIV2PLUGIN_H

#if defined(EXIV2_PLUGIN_LIBRARY)
#  define EXIV2_PLUGIN_EXPORT Q_DECL_EXPORT
#else
#  define EXIV2_PLUGIN_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>

#include <iostream>
#include <string>
#include <exiv2/exiv2.hpp>
#include "exivplugin.h"

/*!
 * \brief The Exiv2Plugin class:
 * Specific exiv plugin for image metadata.
 */
class EXIV2_PLUGIN_EXPORT Exiv2Plugin : public QObject, public ExivPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugin.exiv")
    Q_INTERFACES(ExivPlugin)

public:

    explicit Exiv2Plugin(QObject *parent = nullptr);

    // ExivPlugin interface
public:

    void exifInfo() override;
    void exifPrint(const QString &path) override;
    QDateTime readDate(const QString &path) override;
    QStringList readLabels(const QString &path) override;
    void setLabels(const QString &path, const QStringList &labels) override;
    void readMetadata(const QString &path) override;
    void writeMetadata(const QString &path) override;

private:

    Exiv2::Image::AutoPtr readImage(const QString &path);
    Exiv2::Image::AutoPtr m_metadata;
};

#endif // EXIV2PLUGIN_H
