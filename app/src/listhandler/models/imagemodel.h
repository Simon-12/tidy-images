#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QObject>
#include <QDebug>
#include <QAbstractListModel>

#include "../basefile/imagefile.h"
#include "support.h"

/*!
 * \brief The ImageModel class:
 * Image model, contains the image path.
 */
class ImageModel : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit ImageModel(FileList* list, QObject *parent = nullptr);

    void insert(const int index);
    void remove(const int index);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:

    void refreshModel();
    void browse(const int index);
    int size();

protected:

    FileList* m_fileList;
    QStringList m_model;

};

#endif // IMAGEMODEL_H
