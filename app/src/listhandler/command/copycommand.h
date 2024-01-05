#ifndef COPYCOMMAND_H
#define COPYCOMMAND_H

#include <QDir>
#include <QUndoCommand>
#include <QUndoStack>
#include <QUndoView>

#include "basecommand.h"

/*!
 * \brief The CopyCommand class:
 * QUndoCommand class for copy command.
 */
class CopyCommand : public BaseCommand {
public:
    CopyCommand(const CommandData &data, QUndoCommand *parent = nullptr);

    void redo() override;
    void undo() override;
};

#endif  // COPYCOMMAND_H
