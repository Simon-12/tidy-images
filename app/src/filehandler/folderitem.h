#ifndef FOLDERITEM_H
#define FOLDERITEM_H

#include <QObject>

/*!
 * \brief The FolderItem class:
 * Item for the folder model.
 */
class FolderItem {

public:

    FolderItem() :
        m_name(""),
        m_path(""),
        m_selected(false)
    {
    }

    FolderItem(QString name, QString path, bool selected) :
        m_name(name),
        m_path(path),
        m_selected(selected)
    {
    }

    // Getter
    QString name(){ return m_name; }
    QString path(){ return m_path; }
    bool selected(){ return m_selected; }

    // Setter
    void setSelected(bool state){ m_selected = state; }

private:

    QString m_name;
    QString m_path;
    bool m_selected;
};

#endif // FOLDERITEM_H
