#include "basehandler.h"


BaseHandler::BaseHandler(QString path, QObject *parent) : QObject(parent)
{
    m_path = path;
}


BaseHandler::~BaseHandler()
{
    QFileInfo info = QFileInfo(m_path);
    qInfo() << "Close file:" << info.fileName();
}


void BaseHandler::init()
{
    if(!QFile::exists(m_path))
    {        
        defaultFile();
        MessageBox("There is no file! \ncreate default file:\n'"+ m_path + "'");
        write();
        return;
    }

    read();
}


QString BaseHandler::path()
{
    return m_path;
}


QByteArray BaseHandler::readFile()
{    
    QFile file;
    openFile(file, QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    return data;
}


void BaseHandler::writeFile(QByteArray data)
{
    QFile file;
    openFile(file, QIODevice::WriteOnly);
    file.write(data);
    file.close();
}


void BaseHandler::openFile(QFile &file, QIODevice::OpenMode mode)
{
    file.setFileName(m_path);
    if(!file.open(mode))
        MessageBox("Could not read file! \n" + file.errorString());
}
