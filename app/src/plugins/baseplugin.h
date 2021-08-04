#ifndef BASEPLUGIN_H
#define BASEPLUGIN_H

#include <QObject>
#include <QPluginLoader>
#include <QFileInfoList>
#include <QDebug>
#include <QDir>

/*!
 * \brief The BasePlugin class:
 * Base interaface for all plugins.
 */
class BasePlugin
{

public:

    explicit BasePlugin()
    {
    }

    QString name() const { return m_name; }
    QString icon() const { return m_icon; }
    QString info() const { return m_info; }
    QString link() const { return m_link; }
    QString version() const { return m_version; }

protected:

    QString m_name;
    QString m_icon;
    QString m_info;
    QString m_link;
    QString m_version;
};


template <class T> T* loadPlugin(const QString &path)
{
    QStringList filter;
    filter << "*.dll" << "*.so" << "*.dylib";
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(filter);
    T* plugin = nullptr;

    foreach(QFileInfo info, list)
    {
        QString file = info.filePath();
        QPluginLoader loader(file);
        if(!loader.load())
        {
            qInfo() << "Error:" <<  loader.fileName() << " Error:" << loader.errorString();
            continue;
        }

        plugin = qobject_cast<T*>(loader.instance());
        if(!plugin)
        {
            //qInfo() << "Could not cast:" << loader.fileName();
            continue;
        }
        else
            return plugin;
    }

    // Check for static plugin
    if(!plugin)
    {

        QObjectList instances = QPluginLoader::staticInstances();
        foreach(QObject *item, instances)
        {
            plugin = qobject_cast<T*>(item);
            if(plugin) return plugin;
        }
    }

    return plugin;
}


#endif // BASEPLUGIN_H
