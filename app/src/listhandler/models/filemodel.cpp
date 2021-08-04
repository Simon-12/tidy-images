#include "filemodel.h"


FileModel::FileModel(FileList* list, QObject *parent) :
    QAbstractListModel(parent),
    m_fileList(list)
{

}


void FileModel::refreshModel()
{
    beginResetModel();
    int size = m_fileList->size();
    m_items.clear();
    m_items.reserve(size);

    for(int i = 0; i < size; i++)
    {
        FilePtr file = m_fileList->at(i);
        FileItem item(file->typeStr(), "file:///" + *file->path());
        item.setFavorite(*file->favorite());
        if(*file->filetype() == BaseFile::Video)
        {
            VideoPtr video = file.staticCast<VideoFile>();
            item.setVideo(*video->duration(), video->frameId());
        }
        m_items.append(item);
    }
    endResetModel();
}


void FileModel::clearSelected()
{
    foreach(int i, m_selected)
    {
        QModelIndex idx = this->index(i);
        this->setData(idx, false, SelectedRole);
    }
    m_selected.clear();
}


void FileModel::browse(const int index)
{
    startExplorer(m_items[index].path());
}


void FileModel::append(const FileItem &item)
{
    // Appends item at the end of the list
    beginInsertRows(QModelIndex(), size(), size());
    m_items << item;
    endInsertRows();
}


void FileModel::insert(const int index)
{
    // Insert one item
    beginInsertRows(QModelIndex(), index, index);
    FilePtr file = m_fileList->at(index);
    FileItem item(file->typeStr(), "file:///" + *file->path());
    item.setFavorite(*file->favorite());
    item.setSelected(true);
    if(*file->filetype() == BaseFile::Video)
    {
        VideoPtr video = file.staticCast<VideoFile>();
        item.setVideo(*video->duration(), video->frameId());
    }
    m_items.insert(index, item);

    // Add selected
    for(int i = 0; i < m_selected.size(); i++)
    {
        if(m_selected[i] >= index)
            m_selected[i] = m_selected[i] + 1;
    }
    m_selected << index;
    endInsertRows();
}


void FileModel::remove(const int index)
{
    // Remove one item
    if (index < 0 || index >= m_items.size()) return;
    beginRemoveRows(QModelIndex(), index, index);
    m_items.removeAt(index);
    endRemoveRows();
}


void FileModel::setFavorite(const int index, bool state)
{
    QModelIndex idx = this->index(index);
    this->setData(idx, !state, FavoriteRole);
}


void FileModel::clear()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}


int FileModel::size() const
{
    return m_items.size();
}


int FileModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.size();
}


QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= size()) return QVariant();

    FileItem item = m_items[index.row()];
    switch(role)
    {
    case PathRole: return item.path();
    case TypeRole: return item.filetype();
    case DurationRole: return item.duration();
    case FrameRole: return item.frame();
    case SelectedRole: return item.selected();
    case FavoriteRole: return item.favorite();
    default: return QVariant();
    }
}


QHash<int, QByteArray> FileModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PathRole] = "path";
    roles[TypeRole] = "type";
    roles[DurationRole] = "duration";
    roles[FrameRole] = "frame";
    roles[SelectedRole] = "selected";
    roles[FavoriteRole] = "favorite";
    return roles;
}


Qt::ItemFlags FileModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}


bool FileModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;
    int idx = index.row();
    if (idx < 0 || idx >= size()) return false;

    FileItem item = m_items[idx];
    switch(role)
    {
    case SelectedRole:
        item.setSelected(value.toBool());
        if(value.toBool())
            m_selected.append(idx);
        else
            m_selected.removeOne(idx);
        break;
    case FavoriteRole: item.setFavorite(value.toBool()); break;
    default: return false;
    }

    m_items.replace(idx, item);
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}
