#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QObject>
#include <QSet>

#include "../basefile/basefile.h"
#include "fileitem.h"

/*!
 * \brief The FileModel class:
 * File model for image and video files.
 * Contains the file type and path to the file.
 */
class FileModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit FileModel(FileList *list, QObject *parent = nullptr);

    QList<int> selected();
    void append(const FileItem &item);
    void insertFiles(const QList<int> &list);
    void remove(const int index);
    void setFavorite(const int index, bool state);
    void clear();
    int size() const;

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    enum FileRoles { PathRole = Qt::UserRole + 1, TypeRole, DurationRole, FrameRole, SelectedRole, FavoriteRole };

signals:

    void favorite(int index);

public slots:

    void refreshModel();
    void clearSelected();
    void browse(const int index);
    void setMultiple(bool state);

private:
    void selectMultiple();

    FileList *m_fileList;
    QList<FileItem> m_items;
    QSet<int> m_range;
    bool m_isMultiple;
};

#endif  // FILEMODEL_H
