#ifndef ICONMODEL_H
#define ICONMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QObject>

#include "iconitem.h"

/*!
 * \brief The IconModel class:
 * Icon model, shows information about the icon and author.
 */
class IconModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit IconModel(QObject *parent = nullptr);

    void append(const IconItem &item);
    int size() const { return m_items.size(); }

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    enum IconRoles { NameRole = Qt::UserRole + 1, IconRole, AuthorRole };

private:
    QList<IconItem> m_items;
};

#endif  // ICONMODEL_H
