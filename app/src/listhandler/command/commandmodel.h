#ifndef COMMANDMODEL_H
#define COMMANDMODEL_H

#include <QObject>
#include <QDebug>
#include <QAbstractListModel>

#include "commanditem.h"

/*!
 * \brief The CommandModel class:
 * Command model, shows the history of executed commands.
 */
class CommandModel : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit CommandModel(QObject *parent = nullptr);

    Q_PROPERTY(int index READ getIndex NOTIFY indexChanged)

    void append(const CommandData &data);
    void beginMacro();
    void endMacro();

    enum CommandRoles
    {
        NameRole = Qt::UserRole + 1,
        FoldertRole,
        SourceRole,
        TargetRole,
        NumberRole
    };

public slots:

    void setIndex(int index);

signals:

    void indexChanged();
    void clicked(int index);

    // QAbstractItemModel interface
public:

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:

    int size() const;
    int getIndex(){ return m_index; }
    void appendCommand(const CommandItem &item, bool macro = false);

    bool m_macro;
    int m_index;
    CommandItem m_macroItem;
    QVector<CommandItem> m_items;
};

#endif // COMMANDMODEL_H
