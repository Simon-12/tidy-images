#include "imagemodel.h"


ImageModel::ImageModel(FileList *list, QObject *parent) :
    QAbstractListModel(parent),
    m_fileList(list)
{

}


void ImageModel::insert(const int index)
{
    // Insert one item
    beginInsertRows(QModelIndex(), index, index);
    m_model.insert(index, "file:///" + *m_fileList->at(index)->path());
    endInsertRows();
}


void ImageModel::remove(const int index)
{
    // Remove one item
    if (index < 0 || index >= m_model.size()) return;
    beginRemoveRows(QModelIndex(), index, index);
    m_model.removeAt(index);
    endRemoveRows();
}


int ImageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_model.size();
}


QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= m_model.size()) return QVariant();
    if (role != Qt::DisplayRole) return QVariant();

    return m_model[index.row()];
}


QHash<int, QByteArray> ImageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    return roles;
}


void ImageModel::refreshModel()
{
    beginResetModel();
    int size = m_fileList->size();
    m_model.clear();
    m_model.reserve(size);

    for(int i = 0; i < size; i++)
        m_model.append("file:///" + *m_fileList->at(i)->path());

    endResetModel();
}


void ImageModel::browse(const int index)
{
    startExplorer(m_model[index]);
}


int ImageModel::size()
{
    return m_model.size();
}
