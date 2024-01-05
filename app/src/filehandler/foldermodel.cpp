#include "foldermodel.h"

#include "../support.h"

FolderModel::FolderModel(QObject *parent) : QAbstractListModel(parent) {}

FolderItem FolderModel::getItem(const int index) const {
    if (index < 0 || index >= size()) return FolderItem();

    return m_items[index];
}

int FolderModel::size() const { return m_items.size(); }

bool FolderModel::contains(QString folder) {
    foreach (FolderItem item, m_items) {
        if (item.name() == folder) return true;
    }

    return false;
}

void FolderModel::append(const FolderItem &folder) {
    // Appends item at the end of the list
    beginInsertRows(QModelIndex(), size(), size());
    m_items << folder;
    endInsertRows();
}

void FolderModel::remove(const int index) {
    // Remove only one item
    beginRemoveRows(QModelIndex(), index, index);
    m_items.removeAt(index);
    endRemoveRows();
    emit modelChanged();
}

void FolderModel::moveKey(const QString key, const int target) {
    int source = -1;
    for (int i = 0; i < size(); i++) {
        if (m_items[i].name() == key) {
            source = i;
            break;  // Stop loop
        }
    }
    if (source < 0) return;
    move(source, target);
}

void FolderModel::move(const int from, const int to) {
    int newRow = to;
    int oldRow = from;
    if (newRow > oldRow) newRow++;  // Hack that you can move one index up

    // Move only one item
    beginMoveRows(QModelIndex(), oldRow, oldRow, QModelIndex(), newRow);
    m_items.move(from, to);
    endMoveRows();
    emit modelChanged();
}

void FolderModel::browse(const int index) {
    FolderItem item = m_items.at(index);
    QString path = item.path();
    startExplorer(path);
}

int FolderModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return size();
}

QVariant FolderModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= size()) return QVariant();

    FolderItem item = m_items[index.row()];
    switch (role) {
        case NameRole:
            return item.name();
        case PathRole:
            return item.path();
        case SelectedRole:
            return item.selected();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> FolderModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[PathRole] = "path";
    roles[SelectedRole] = "selected";
    return roles;
}

Qt::ItemFlags FolderModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}

bool FolderModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) return false;
    if (index.row() < 0 || index.row() >= size()) return false;

    FolderItem item = m_items[index.row()];
    switch (role) {
        case SelectedRole:
            item.setSelected(value.toBool());
            break;
        default:
            return false;
    }

    m_items.replace(index.row(), item);
    emit dataChanged(index, index, QList<int>() << role);
    emit modelChanged();
    return true;
}
