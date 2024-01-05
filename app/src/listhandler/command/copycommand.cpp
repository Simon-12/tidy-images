#include "copycommand.h"

CopyCommand::CopyCommand(const CommandData &data, QUndoCommand *parent) : BaseCommand(data, parent) {}

void CopyCommand::redo() {
    if (QFile::exists(m_data.target)) {
        qInfo() << "File already exist in folder";
        return;
    }
    QFile::copy(m_data.source, m_data.target);
}

void CopyCommand::undo() {
    if (!QFile::exists(m_data.target)) return;

    QFile(m_data.target).moveToTrash();
}
