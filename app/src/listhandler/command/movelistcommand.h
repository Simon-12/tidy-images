#ifndef MOVELISTCOMMAND_H
#define MOVELISTCOMMAND_H

#include <QObject>
#include <QUndoCommand>
#include <QUndoStack>

#include "commanddata.h"

class MoveListCommand : public QUndoCommand {
public:
    explicit MoveListCommand(const QList<CommandData> &list, QUndoCommand *parent = nullptr);

    void redo() override;
    void undo() override;

private:
    QList<CommandData> m_list;
};

#endif  // MOVELISTCOMMAND_H
