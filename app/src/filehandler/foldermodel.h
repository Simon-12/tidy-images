#ifndef FOLDERMODEL_H
#define FOLDERMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QObject>

#include "folderitem.h"

/*!
 * \brief The FolderModel class:
 * Shows the folder name, path and selected state.
 */
class FolderModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit FolderModel(QObject *parent = nullptr);

    FolderItem getItem(const int index) const;
    int size() const;
    bool contains(QString folder);
    void append(const FolderItem &folder);

    enum FolderRoles { NameRole = Qt::UserRole + 1, PathRole, SelectedRole };

public slots:

    void remove(const int index);
    void moveKey(const QString key, const int target);
    void move(const int from, const int to);
    void browse(const int index);

signals:

    void modelChanged();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QList<FolderItem> m_items;
};

#endif  // FOLDERMODEL_H
