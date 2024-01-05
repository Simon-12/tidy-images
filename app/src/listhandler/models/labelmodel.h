#ifndef LABELMODEL_H
#define LABELMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QObject>

#include "imagemodel.h"

/*!
 * \brief The LabelModel class:
 * Label model, shows the label text.
 */
class LabelModel : public ImageModel {
    Q_OBJECT

public:
    explicit LabelModel(FileList* list, QObject* parent = nullptr);

    void updateIndex(const int index);
    void append(const QString item);
    bool contains(const QString item);
    QStringList getLabels();
};

#endif  // LABELMODEL_H
