#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <QObject>
#include <QUndoCommand>
#include <QUndoStack>

#include "commanddata.h"

/*!
 * \brief The BaseCommand class:
 * Base interface for commands.
 */
class BaseCommand : public QUndoCommand {
public:
    BaseCommand(const CommandData &data, QUndoCommand *parent = nullptr);
    int index() const { return m_data.index; }
    QString name() const { return *m_data.file->name(); }

protected:
    CommandData m_data;
};

#endif  // BASECOMMAND_H
