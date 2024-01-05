#include "iconmodel.h"

IconModel::IconModel(QObject *parent) : QAbstractListModel(parent) {}

void IconModel::append(const IconItem &item) {
    // Appends item at the end of the list
    beginInsertRows(QModelIndex(), size(), size());
    m_items << item;
    endInsertRows();
}

int IconModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return size();
}

QVariant IconModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= size()) return QVariant();

    IconItem item = m_items[index.row()];
    switch (role) {
        case NameRole:
            return item.name();
        case IconRole:
            return item.icon();
        case AuthorRole:
            return item.author();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> IconModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[AuthorRole] = "author";
    return roles;
}
