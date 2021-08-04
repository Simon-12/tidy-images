#ifndef ICONITEM_H
#define ICONITEM_H

#include <QObject>
#include <QDebug>

/*!
 * \brief The IconItem class:
 * Item for the icon model.
 */
class IconItem {

public:

    IconItem(const QString &name, const QString &ressource,
             const QString &link, const QString &author)
    {
        m_name = "<a href='" + link + "'>" + name + "</a>";
        m_icon = ressource + name;
        m_author = "<a href='" + author + "'>Author</a>";
    }

    QString name(){ return m_name; }
    QString icon(){ return m_icon; }
    QString author(){ return m_author; }

private:

    QString m_name;
    QString m_icon;
    QString m_author;
};

#endif // ICONITEM_H
