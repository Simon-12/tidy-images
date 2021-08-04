#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSize>

#include "options.h"

/*!
 * \brief The Settings class:
 * Settings for the application.
 */
class Settings
{

public:

    QString     path;         // Current folder path
    QString     json;         // JSON file path
    QString     database;     // Database file path
    QString     favorites;    // Favorites folder path
    QString     trash;        // Trash folder path
    QStringList imageFormats; // Image formats
    QStringList videoFormats; // Video formats
    QSize       size;         // Window size
    AppMode     mode;         // Appmode on start
    int         bufferSize;   // Buffer size for images
    int         threshold;    // Compare score threshold
};


/*!
 * \brief The Paths class:
 * Paths for qml.
 */
class Paths
{
    Q_GADGET

public:

    Q_PROPERTY(QString path      MEMBER m_path)
    Q_PROPERTY(QString folders   MEMBER m_json)
    Q_PROPERTY(QString database  MEMBER m_database)
    Q_PROPERTY(QString favorites MEMBER m_favorites)
    Q_PROPERTY(QString trash     MEMBER m_trash)

    void setPaths(Settings set)
    {
        m_path      = set.path;
        m_json      = set.json;
        m_database  = set.database;
        m_favorites = set.favorites;
        m_trash     = set.trash;
    }

private:

    QString m_path;
    QString m_json;
    QString m_database;
    QString m_favorites;
    QString m_trash;
};

Q_DECLARE_METATYPE(Paths) // for QML


#endif // SETTINGS_H
