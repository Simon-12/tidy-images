#include "tablemodel.h"

#include "../basefile/imagefile.h"

TableModel::TableModel(FileList *list, int threshold, QObject *parent) : QAbstractTableModel(parent), m_fileList(list) {
    setThreshold(threshold);
    m_columns = 3;
    m_rows = 5;

    // Set header
    m_header << ""
             << "Score"
             << "Date"
             << "Type"
             << "Size";

    // Colors
    m_colorDefault = "whitesmoke";
    m_colorEqual = "orange";
    m_colorMarked = "lightgreen";
    QList<QString *> vec(m_rows, 0);
    m_tableColor.reserve(m_columns);
    m_tableColor.fill(vec, m_columns);
}

int TableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    if (m_tableText.isEmpty()) return -1;
    return m_rows;
}

int TableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    if (m_tableText.isEmpty()) return -1;
    return m_columns;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (m_tableText.isEmpty()) return QVariant();
    if (!index.isValid()) return QVariant();
    if (index.column() < 0 || index.column() >= m_columns) return QVariant();
    if (index.row() < 0 || index.row() >= m_rows) return QVariant();

    switch (role) {
        case TextRole:
            return m_tableText[index.column()][index.row()];
        case ColorRole:
            return *m_tableColor[index.column()][index.row()];
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> TableModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TextRole] = "text";
    roles[ColorRole] = "color";
    return roles;
}

void TableModel::refreshModel() {
    if (m_fileList->size() <= 0) return;

    m_left = 0;
    m_right = 0;

    // Reset table
    m_tableText.clear();
    m_tableText.reserve(m_columns);
    QList<QString> vec(m_rows, "");
    m_tableText.fill(vec, m_columns);

    beginResetModel();
    m_tableText.replace(0, m_header);
    m_tableText.replace(1, setFileColumn(m_left));   // First column
    m_tableText.replace(2, setFileColumn(m_right));  // Second column
    setColor();
    endResetModel();
}

void TableModel::setFile(int left, int right) {
    if (m_fileList->size() <= 0) return;
    if (m_tableText.isEmpty()) return;
    if (left < 0 || right < 0) return;

    if (left != m_left) {
        beginResetModel();
        m_left = left;
        m_tableText.replace(1, setFileColumn(m_left));  // First column
    }
    if (right != m_right) {
        beginResetModel();
        m_right = right;
        m_tableText.replace(2, setFileColumn(m_right));  // Second column
    }

    setColor();
    endResetModel();
}

QList<QString> TableModel::setFileColumn(int index) {
    QList<QString> list(m_header);  // Allocate default size
    ImagePtr file = m_fileList->at(index).dynamicCast<ImageFile>();
    if (!file) return list;

    list.replace(0, *file->name());
    list.replace(1, file->scoreStr());
    list.replace(2, file->dateStr());
    list.replace(3, file->formatStr());
    list.replace(4, file->sizeStr());
    return list;
}

void TableModel::setColor() {
    // Set default colors
    QList<QString *> vec(m_rows, &m_colorDefault);
    m_tableColor.fill(vec, m_columns);
    if (m_left == m_right) return;

    // Start at second row
    for (int i = 1; i < m_rows; i++) {
        QString left = m_tableText[1][i];
        QString right = m_tableText[2][i];
        if (left.isEmpty() || right.isEmpty()) continue;  // Next i++

        switch (i) {
            case 1: {
                if (left == "0") break;
                m_tableColor[1][i] = &m_colorMarked;
                double val = right.toDouble();
                double thr = m_threshold;
                m_tableColor[2][i] = processColor<double>(val, thr);
                break;
            }
            case 2: {
                QDateTime time1 = QDateTime::fromString(left, "dd.MM.yyyy-hh:mm");
                QDateTime time2 = QDateTime::fromString(right, "dd.MM.yyyy-hh:mm");
                m_tableColor[1][i] = processColor<QDateTime>(time1, time2);
                m_tableColor[2][i] = processColor<QDateTime>(time2, time1);
                break;
            }
            case 3:
                m_tableColor[1][i] = processColor<QString>(right, left);
                m_tableColor[2][i] = processColor<QString>(left, right);
                break;
            case 4: {
                double val1 = left.split(" MB").at(0).toDouble();
                double val2 = right.split(" MB").at(0).toDouble();
                m_tableColor[1][i] = processColor<double>(val1, val2);
                m_tableColor[2][i] = processColor<double>(val2, val1);
                break;
            }
            default:
                break;
        }
    }
}

template <class T>
QString *TableModel::processColor(T &left, T &right) {
    if (left == right) return &m_colorEqual;
    if (left > right)
        return &m_colorMarked;
    else
        return &m_colorDefault;
}

void TableModel::setThreshold(int threshold) {
    if (threshold < 0 || threshold > 100) return;
    m_threshold = threshold;
    emit thresholdChanged();
}

void TableModel::setActive(bool state) {
    m_active = state;
    emit activeChanged();
}
