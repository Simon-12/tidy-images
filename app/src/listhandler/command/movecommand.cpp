#include "movecommand.h"


MoveCommand::MoveCommand(const CommandData &data, QUndoCommand *parent) : BaseCommand(data, parent)
{

}


void MoveCommand::redo()
{
    if(!moveFile(m_data.source, m_data.target))
        return;

    m_data.database->insertFile(m_data.index, m_data.target);
    m_data.fileList->remove(m_data.index);
    if(m_data.mode == AppMode::Gallery)
        m_data.fileModel->remove(m_data.index);
    else
    {
        if(*m_data.file->filetype() == BaseFile::Image)
            m_data.imageModel->remove(m_data.index);
    }
}


void MoveCommand::undo()
{
    if(!moveFile(m_data.target, m_data.source))
        return;

    m_data.fileList->insert(m_data.index, m_data.file);
    m_data.database->removePath(m_data.target);
    if(m_data.mode == AppMode::Gallery)
        m_data.fileModel->insert(m_data.index);
    else
    {
        if(*m_data.file->filetype() == BaseFile::Image)
            m_data.imageModel->insert(m_data.index);
    }
}


bool MoveCommand::moveFile(QString source, QString target)
{
    if(QFile::exists(target))
    {
        QFile(source).moveToTrash();
        qInfo() << "File already exist in folder -> delete";
        return true;
    }

    if(!QFile::rename(source, target))
    {
        MessageBox("Error: can not move file to folder");
        return false;
    }

    return true;
}
