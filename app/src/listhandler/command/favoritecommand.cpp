#include "favoritecommand.h"

FavoriteCommand::FavoriteCommand(const CommandData &data, QUndoCommand *parent) : BaseCommand(data, parent) {}

void FavoriteCommand::redo() { setFavorite(m_data); }

void FavoriteCommand::undo() { setFavorite(m_data); }

void FavoriteCommand::setFavorite(const CommandData &data) {
    bool state = *data.file->favorite();
    data.file->setFavorite(!state);
    if (!state)
        QFile::copy(data.source, data.target);
    else
        QFile(data.target).moveToTrash();

    if (m_data.mode == AppMode::Gallery) m_data.fileModel->setFavorite(m_data.index, state);
}
