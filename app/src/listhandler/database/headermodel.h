#ifndef HEADERMODEL_H
#define HEADERMODEL_H

#include <QObject>
#include <QDebug>
#include <QAbstractListModel>

#include "headeritem.h"

/*!
 * \brief The HeaderModel class:
 * Header model for the database, shows the column name with filter and direction.
 */
class HeaderModel : public QAbstractListModel
{
    Q_OBJECT    

public:

    explicit HeaderModel(QVector<QString> &header, QObject *parent = nullptr);

    enum HeaderRoles
    {
        NameRole = Qt::UserRole + 1,
        FilterRole,
        DirectionRole
    };

    // QAbstractItemModel interface
public:

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:

    int size() const;
    void setFilter();
    QVector<HeaderItem> m_items;

signals:

    void filterChanged(QString filter, QString direction);
    void finishedFilter();

public slots:

    void resetFiler();
};

#endif // HEADERMODEL_H
