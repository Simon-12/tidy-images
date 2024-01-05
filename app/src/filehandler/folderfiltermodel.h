#ifndef FOLDERFILTERMODEL_H
#define FOLDERFILTERMODEL_H

#include <QDebug>
#include <QObject>
#include <QSortFilterProxyModel>
#include <QVariant>

/*!
 * \brief The FolderFilterModel class:
 *  Filters the folder model, shows only selected folders.
 */
class FolderFilterModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    Q_PROPERTY(int size READ getSize NOTIFY sizeChanged)

    explicit FolderFilterModel(QObject *parent = nullptr);
    void setSize(const int size);

signals:
    void move(QString key, int target);
    void sizeChanged();

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    int m_size;
    int getSize() { return m_size; }
};

#endif  // FOLDERFILTERMODEL_H
