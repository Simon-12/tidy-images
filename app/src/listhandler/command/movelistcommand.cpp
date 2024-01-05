
#include "movelistcommand.h"

#include "movecommand.h"

MoveListCommand::MoveListCommand(const QList<CommandData> &list, QUndoCommand *parent) : QUndoCommand{parent} { m_list = list; }

void MoveListCommand::redo() {
    foreach (CommandData data, m_list) {
        if (!MoveCommand::moveFile(data.source, data.target)) continue;

        int idx = data.index;
        data.database->insertFile(idx, data.target);
        data.fileList->remove(idx);
        data.fileModel->remove(idx);
    }
}

void MoveListCommand::undo() {
    QList<int> list;
    std::reverse(m_list.begin(), m_list.end());  // List from low to high
    foreach (CommandData data, m_list) {
        if (!MoveCommand::moveFile(data.target, data.source)) continue;

        int idx = data.index;
        list.append(idx);
        data.fileList->insert(idx, data.file);
        data.database->removePath(data.target);
    }
    // Removed from the model at once
    m_list.at(0).fileModel->insertFiles(list);
}
