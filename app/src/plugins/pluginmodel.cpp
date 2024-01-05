#include "pluginmodel.h"

PluginModel::PluginModel(QObject *parent) : QAbstractListModel(parent) {}

void PluginModel::append(BasePlugin *plugin) {
    qInfo() << plugin->name();
    PluginItem item(plugin->name(), plugin->icon(), plugin->link(), plugin->info(), plugin->version());

    // Appends item at the end of the list
    beginInsertRows(QModelIndex(), size(), size());
    m_items << item;
    endInsertRows();
}

int PluginModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_items.size();
}

QVariant PluginModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= size()) return QVariant();

    PluginItem item = m_items[index.row()];
    switch (role) {
        case NameRole:
            return item.name();
        case IconRole:
            return item.icon();
        case DescriptionRole:
            return item.description();
        case VersionRole:
            return item.version();
        default:
            return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> PluginModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[DescriptionRole] = "description";
    roles[VersionRole] = "version";
    return roles;
}

int PluginModel::size() const { return m_items.size(); }
