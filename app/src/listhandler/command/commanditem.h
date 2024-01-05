#ifndef COMMANDITEM_H
#define COMMANDITEM_H

#include <QObject>

#include "commanddata.h"

/*!
 * \brief The CommandItem class:
 * Item for the command model.
 */
class CommandItem {
public:
    CommandItem() {
        m_name = "";
        m_folder = "";
        m_source = "";
        m_target = "";
        m_size = 0;
    }

    CommandItem(const QString &name, const QString &folder) {
        m_name = name;
        m_folder = folder;
        m_source = "";
        m_target = "";
        m_size = 1;
    }

    CommandItem(const CommandData &data) {
        // Folder
        QStringList list = data.target.split('/');
        m_folder = list.at(list.size() - 2);
        if (m_folder[0] == QChar('_')) m_folder = m_folder.remove(0, 1);

        m_name = *data.file->name();
        m_size = 1;
        if (data.file->typeStr() == "Image") {
            m_source = "file:///" + data.source;
            m_target = "file:///" + data.target;
        } else {
            m_source = "";
            m_target = "";
        }
    }

    CommandItem &operator<<(const CommandData &data) {
        CommandItem item(data);
        QString merge = "";
        if (m_size == 0) {
            m_folder = item.folder();
            m_source = item.source();
            m_target = item.target();
        } else
            merge = "\n";
        m_name = m_name + merge + item.name();
        m_size += 1;
        return *this;
    }

    QString name() { return m_name; }
    QString folder() { return m_folder; }
    QString source() { return m_source; }
    QString target() { return m_target; }
    int size() { return m_size; }
    void setSource(const QString &source) { m_name = source; }

private:
    QString m_name;
    QString m_folder;
    QString m_source;
    QString m_target;
    int m_size;
};

#endif  // COMMANDITEM_H
