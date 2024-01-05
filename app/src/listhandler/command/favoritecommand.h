#ifndef FAVORITECOMMAND_H
#define FAVORITECOMMAND_H

#include <QDir>
#include <QUndoCommand>
#include <QUndoStack>
#include <QUndoView>

#include "basecommand.h"

/*!
 * \brief The CopyCommand class:
 * QUndoCommand class for favorite command.
 */
class FavoriteCommand : public BaseCommand {
public:
    FavoriteCommand(const CommandData &data, QUndoCommand *parent = nullptr);

    void redo() override;
    void undo() override;
    void setFavorite(const CommandData &data);
};

#endif  // FAVORITECOMMAND_H
