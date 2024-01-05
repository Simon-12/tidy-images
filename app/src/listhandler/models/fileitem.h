#ifndef FILEITEM_H
#define FILEITEM_H

#include <QDebug>
#include <QObject>

/*!
 * \brief The FileItem class:
 * File item for the file model.
 */
class FileItem {
public:
    FileItem() {}

    FileItem(const QString &filetype, const QString &path) {
        m_filetype = filetype;
        m_path = path;
        m_duration = "";
        m_frame = "";
        m_selected = false;
        m_favorite = false;
    }

    // Getter
    QString path() { return m_path; }
    QString filetype() { return m_filetype; }
    QString duration() { return m_duration; }
    QString frame() { return m_frame; }
    bool selected() { return m_selected; }
    bool favorite() { return m_favorite; }

    // Setter
    void setVideo(const QString &duration, const QString &frame) {
        m_duration = setDuration(duration);
        m_frame = frame;
    }
    void setSelected(bool state) { m_selected = state; }
    void setFavorite(bool state) { m_favorite = state; }

private:
    QString m_path;
    QString m_filetype;
    QString m_duration;
    QString m_frame;
    bool m_selected;
    bool m_favorite;

    QString setDuration(const QString &duration) {
        if (duration.isEmpty()) return "";
        QStringList list = duration.split(":");
        QString str;

        if (list[0] != "00") {
            QString part = list[0][1];
            str = part + " h";  // hours
            if (list[1] != "00") str = list[1] + " min";
            return str;
        }
        if (list[1] != "00") {
            str = list[1];  // minutes
            if (str[0] == QChar('0')) str = str[1];
            return str + " min";
        } else {
            str = list[2];  // seconds
            return list[2] + " sec";
        }
    }
};

#endif  // FILEITEM_H
