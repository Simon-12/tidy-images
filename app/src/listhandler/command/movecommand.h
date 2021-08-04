#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include <QUndoCommand>
#include <QUndoStack>
#include <QUndoView>
#include <QDir>

#include "basecommand.h"

/*!
 * \brief The MoveCommand class:
 * QUndoCommand class for move command.
 */
class MoveCommand : public BaseCommand
{

public:

    MoveCommand(const CommandData &data, QUndoCommand *parent = nullptr);

    void redo() override;
    void undo() override;
    bool moveFile(QString source, QString target);
};

#endif // MOVECOMMAND_H
