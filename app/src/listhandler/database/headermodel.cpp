#include "headermodel.h"


HeaderModel::HeaderModel(QVector<QString> &header, QObject *parent) : QAbstractListModel(parent)
{
    beginInsertRows(QModelIndex(), 0, header.size());
    foreach(QString item, header)
        m_items.append(HeaderItem(item));
    endInsertRows();
}


int HeaderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return size();
}


QVariant HeaderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= size()) return QVariant();

    HeaderItem item = m_items[index.row()];
    switch(role)
    {
    case NameRole: return item.name();
    case FilterRole: return item.filter();
    case DirectionRole: return item.direction();
    default: return QVariant();
    }
}


QHash<int, QByteArray> HeaderModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[FilterRole] = "filter";
    roles[DirectionRole] = "direction";
    return roles;
}


Qt::ItemFlags HeaderModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}


bool HeaderModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    HeaderItem item = m_items[index.row()];
    switch(role)
    {
    case FilterRole: item.setFilter(value.toString()); break;
    case DirectionRole:
    {
        int num = value.toInt();
        if(num > 2) num = 0;
        item.setDirection(static_cast<HeaderDirection>(num));
        break;
    }
    default: return false;
    }

    m_items.replace(index.row(), item);
    setFilter();

    // Emit changes
    switch(role)
    {
    case DirectionRole:
        emit dataChanged(index, index, QVector<int>() << role);
        emit finishedFilter();
        break;
    default: break;
    }

    return true;
}


int HeaderModel::size() const
{
    return m_items.size();
}


void HeaderModel::setFilter()
{

    QString filter;
    QString direction;
    foreach(HeaderItem item, m_items)
    {
        // Create filter
        if(!item.filter().isEmpty())
        {
            if(filter.isEmpty())
                filter += " WHERE ";
            else
                filter += " AND ";
            filter += item.name() + " LIKE '%" + item.filter() + "%'";
        }

        // Create direction
        if(item.direction() != HeaderDirection::Disabled)
        {
            if(direction.isEmpty())
                direction += " ORDER BY ";
            else
                direction += ", ";
            direction += item.name();
            switch (item.direction())
            {
            case HeaderDirection::Low:  direction += " DESC ";  break;
            case HeaderDirection::High: direction += " ASC "; break;
            default: break;
            }
        }
    }

    emit filterChanged(filter, direction);
}


void HeaderModel::resetFiler()
{
    beginResetModel();
    for(int i = 0; i < size(); i++)
    {
        HeaderItem item = m_items[i];
        m_items.replace(i, HeaderItem(item.name()));
    }
    endResetModel();
    emit filterChanged("", "");
    emit finishedFilter();
}
