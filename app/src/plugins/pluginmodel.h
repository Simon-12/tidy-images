#ifndef PLUGINMODEL_H
#define PLUGINMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QObject>

#include "baseplugin.h"
#include "pluginitem.h"

/*!
 * \brief The PluginModel class:
 * Plugin model, shows the plugin name, version, icon and description.
 */
class PluginModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit PluginModel(QObject *parent = nullptr);
    void append(BasePlugin *plugin);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    enum PluginRoles { NameRole = Qt::UserRole + 1, IconRole, DescriptionRole, VersionRole };

private:
    QList<PluginItem> m_items;
    int size() const;
};

#endif  // PLUGINMODEL_H
