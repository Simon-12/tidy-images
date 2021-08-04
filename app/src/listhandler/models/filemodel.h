#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QAbstractListModel>

#include "../basefile/imagefile.h"
#include "../basefile/videofile.h"
#include "support.h"
#include "fileitem.h"

/*!
 * \brief The FileModel class:
 * File model for image and video files.
 * Contains the file type and path to the file.
 */
class FileModel : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit FileModel(FileList* list, QObject *parent = nullptr);

    QVector<int> selected(){ return m_selected; }
    void append(const FileItem &item);
    void insert(const int index);
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

    enum FileRoles
    {
        PathRole = Qt::UserRole + 1,
        TypeRole,
        DurationRole,
        FrameRole,
        SelectedRole,
        FavoriteRole
    };

signals:

    void favorite(int index);

public slots:

    void refreshModel();
    void clearSelected();
    void browse(const int index);

private:

    FileList* m_fileList;
    QVector<FileItem> m_items;
    QVector<int> m_selected;

};

#endif // FILEMODEL_H
