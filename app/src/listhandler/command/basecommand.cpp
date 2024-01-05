#include "basecommand.h"

BaseCommand::BaseCommand(const CommandData &data, QUndoCommand *parent) : QUndoCommand(parent) { m_data = data; }
