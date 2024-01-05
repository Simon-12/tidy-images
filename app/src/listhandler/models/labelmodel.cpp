#include "labelmodel.h"

LabelModel::LabelModel(FileList* list, QObject* parent) : ImageModel(list, parent) {}

void LabelModel::updateIndex(const int index) {
    if (m_fileList->size() <= 0) return;
    if (index < 0) {
        beginResetModel();
        m_model.clear();
        endResetModel();
        return;
    }

    beginResetModel();
    QStringList* labels = m_fileList->at(index)->labels();
    int size = labels->size();
    m_model.clear();
    m_model.reserve(size);

    for (int i = 0; i < size; i++) m_model.append(labels->at(i));

    endResetModel();
}

void LabelModel::append(const QString item) {
    // Append row at the end
    int row = size();
    beginInsertRows(QModelIndex(), row, row);
    m_model.append(item);
    endInsertRows();
}

bool LabelModel::contains(const QString item) { return m_model.contains(item, Qt::CaseInsensitive); }

QStringList LabelModel::getLabels() { return m_model; }
