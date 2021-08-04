#include "folderfiltermodel.h"


FolderFilterModel::FolderFilterModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}


bool FolderFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    QVariant data = sourceModel()->data(index, Qt::UserRole + 3); // SelectedRole

    bool item = data.value<bool>();
    return item;
}
