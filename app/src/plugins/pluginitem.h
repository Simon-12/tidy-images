#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QDebug>
#include <QObject>

/*!
 * \brief The PluginItem class:
 * Item for the plugin model.
 */
class PluginItem {
public:
    PluginItem(const QString &name, const QString &icon, const QString &link, const QString &info, const QString &version) {
        m_name = name;
        m_icon = "qrc" + icon;
        m_version = version;
        m_description = info + "<br><a href='" + link + "'>" + link + "</a>";
    }

    QString name() { return m_name; }
    QString icon() { return m_icon; }
    QString description() { return m_description; }
    QString version() { return m_version; }

private:
    QString m_name;
    QString m_icon;
    QString m_description;
    QString m_version;
};

#endif  // PLUGINITEM_H
