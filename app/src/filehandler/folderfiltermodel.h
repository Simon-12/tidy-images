#ifndef FOLDERFILTERMODEL_H
#define FOLDERFILTERMODEL_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QSortFilterProxyModel>

/*!
 * \brief The FolderFilterModel class:
 *  Filters the folder model, shows only selected folders.
 */
class FolderFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:

    explicit FolderFilterModel(QObject *parent = nullptr);

signals:
    void move(QString key, int target);

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // FOLDERFILTERMODEL_H
