#include "commandmodel.h"

CommandModel::CommandModel(QObject *parent) : QAbstractListModel(parent) {
    m_macro = false;
    setIndex(0);                                  // Start index
    m_items << CommandItem("(empty)", "Folder");  // Add empty
}

void CommandModel::append(const CommandData &data) {
    if (m_macro)
        m_macroItem << data;  // If macro -> merge
    else
        appendCommand(CommandItem(data));
}

void CommandModel::beginMacro() {
    m_macro = true;
    m_macroItem = CommandItem();
}

void CommandModel::endMacro() {
    m_macro = false;
    appendCommand(m_macroItem, true);
}

void CommandModel::setIndex(int index) {
    m_index = index;
    emit indexChanged();
}

int CommandModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return size();
}

QVariant CommandModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= size()) return QVariant();

    CommandItem item = m_items[index.row()];
    switch (role) {
        case NameRole:
            return item.name();
        case FoldertRole:
            return item.folder();
        case SourceRole:
            return item.source();
        case TargetRole:
            return item.target();
        case NumberRole:
            return item.size();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> CommandModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[FoldertRole] = "folder";
    roles[SourceRole] = "source";
    roles[TargetRole] = "target";
    roles[NumberRole] = "number";
    return roles;
}

int CommandModel::size() const { return m_items.size(); }

void CommandModel::appendCommand(const CommandItem &item, bool macro) {
    int idx = m_index;
    if (macro) idx -= 1;  // If macro -> index already incremented
    int sz = size() - 1;

    if (idx == sz) {
        // Appends item at the end of the list
        beginInsertRows(QModelIndex(), size(), size());
        m_items << item;
        endInsertRows();
    } else {
        // Delete items above index and append item
        beginResetModel();
        m_items.remove(idx + 1, sz - idx);  // First entry is empty item
        m_items << item;
        endResetModel();
    }
}
