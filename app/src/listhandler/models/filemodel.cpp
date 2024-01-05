#include "filemodel.h"

#include "../basefile/videofile.h"
#include "support.h"

FileModel::FileModel(FileList *list, QObject *parent) : QAbstractListModel(parent), m_fileList(list) { m_isMultiple = false; }

QList<int> FileModel::selected() {
    QList<int> list;
    for (int i = 0; i < size(); i++) {
        FileItem item = m_items[i];
        if (item.selected()) list.append(i);
    }
    return list;
}

void FileModel::refreshModel() {
    beginResetModel();
    int size = m_fileList->size();
    m_items.clear();
    m_items.reserve(size);

    for (int i = 0; i < size; i++) {
        FilePtr file = m_fileList->at(i);
        FileItem item(file->typeStr(), "file:///" + *file->path());
        item.setFavorite(*file->favorite());
        if (*file->filetype() == BaseFile::Video) {
            VideoPtr video = file.staticCast<VideoFile>();
            item.setVideo(*video->duration(), video->frameId());
        }
        m_items.append(item);
    }
    endResetModel();
}

void FileModel::clearSelected() {
    foreach (int i, selected()) {
        QModelIndex idx = this->index(i);
        this->setData(idx, false, SelectedRole);
    }
}

void FileModel::browse(const int index) { startExplorer(m_items[index].path()); }

void FileModel::setMultiple(bool state) {
    m_isMultiple = state;
    m_range.clear();
}

void FileModel::selectMultiple() {
    if (m_range.size() < 2) return;

    int min = *std::min_element(m_range.begin(), m_range.end());
    int max = *std::max_element(m_range.begin(), m_range.end());

    for (int i = min; i < max; i++) {
        FileItem item = m_items[i];
        if (item.selected()) continue;  // skip

        // Set selected
        item.setSelected(true);
        m_items.replace(i, item);
        QModelIndex idx = this->index(i);
        emit dataChanged(idx, idx, QList<int>() << SelectedRole);
    }
}

void FileModel::append(const FileItem &item) {
    // Appends item at the end of the list
    beginInsertRows(QModelIndex(), size(), size());
    m_items.append(item);
    endInsertRows();
}

void FileModel::insertFiles(const QList<int> &list) {
    beginResetModel();
    foreach (int idx, list) {
        FilePtr file = m_fileList->at(idx);
        FileItem item(file->typeStr(), "file:///" + *file->path());
        item.setFavorite(*file->favorite());
        item.setSelected(true);
        if (*file->filetype() == BaseFile::Video) {
            VideoPtr video = file.staticCast<VideoFile>();
            item.setVideo(*video->duration(), video->frameId());
        }
        m_items.insert(idx, item);
    }
    endResetModel();
}

void FileModel::remove(const int index) {
    // Remove one item
    if (index < 0 || index >= m_items.size()) return;
    beginRemoveRows(QModelIndex(), index, index);
    m_items.removeAt(index);
    endRemoveRows();
}

void FileModel::setFavorite(const int index, bool state) {
    QModelIndex idx = this->index(index);
    this->setData(idx, !state, FavoriteRole);
}

void FileModel::clear() {
    beginResetModel();
    m_items.clear();
    endResetModel();
}

int FileModel::size() const { return m_items.size(); }

int FileModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_items.size();
}

QVariant FileModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= size()) return QVariant();

    FileItem item = m_items[index.row()];
    switch (role) {
        case PathRole:
            return item.path();
        case TypeRole:
            return item.filetype();
        case DurationRole:
            return item.duration();
        case FrameRole:
            return item.frame();
        case SelectedRole:
            return item.selected();
        case FavoriteRole:
            return item.favorite();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> FileModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PathRole] = "path";
    roles[TypeRole] = "type";
    roles[DurationRole] = "duration";
    roles[FrameRole] = "frame";
    roles[SelectedRole] = "selected";
    roles[FavoriteRole] = "favorite";
    return roles;
}

Qt::ItemFlags FileModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}

bool FileModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) return false;
    int idx = index.row();
    if (idx < 0 || idx >= size()) return false;

    FileItem item = m_items[idx];
    bool state = value.toBool();

    switch (role) {
        case SelectedRole:
            if (m_isMultiple) {
                state = true;
                m_range.insert(idx);
                selectMultiple();
            }
            item.setSelected(state);
            break;
        case FavoriteRole:
            item.setFavorite(state);
            break;
        default:
            return false;
    }

    m_items.replace(idx, item);
    emit dataChanged(index, index, QList<int>() << role);
    return true;
}
