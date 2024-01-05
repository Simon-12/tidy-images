#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QDateTime>
#include <QObject>
#include <QVariant>

#include "../basefile/basefile.h"

/*!
 * \brief The TableModel class:
 * Table model with infos about the compared files.
 */
class TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    Q_PROPERTY(int threshold READ getThreshold WRITE setThreshold NOTIFY thresholdChanged)
    Q_PROPERTY(bool active READ getActive NOTIFY activeChanged)

    explicit TableModel(FileList *list, int threshold, QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    enum TableRoles { TextRole = Qt::UserRole + 1, ColorRole };

public slots:

    void refreshModel();
    void setFile(int left, int right);
    void setActive(bool state);

private:
    int m_columns;
    int m_rows;
    int m_left;
    int m_right;
    int m_threshold;
    bool m_active;
    QString m_colorDefault;
    QString m_colorEqual;
    QString m_colorMarked;
    QList<QString> m_header;
    FileList *m_fileList;

    // Columns first -> rows -> cell (text, color)
    QList<QList<QString> > m_tableText;     // Stores info from files
    QList<QList<QString *> > m_tableColor;  // Stores color for model (pointers)

    QList<QString> setFileColumn(int index);
    void setColor();
    template <class T>
    QString *processColor(T &left, T &right);
    int getThreshold() { return m_threshold; }
    bool getActive() { return m_active; }
    void setThreshold(int threshold);

signals:

    void thresholdChanged();
    void activeChanged();
};

#endif  // TABLEMODEL_H
