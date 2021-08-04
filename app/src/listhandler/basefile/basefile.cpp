#include "basefile.h"


BaseFile::BaseFile()
{

}


BaseFile::~BaseFile()
{

}


void BaseFile::init(const QFileInfo &info, bool favorite)
{
    m_name = info.fileName();
    m_path = info.absoluteFilePath();
    m_modified = info.lastModified();
    m_created = info.birthTime();
    if(!m_created.isValid()) m_created = m_modified;
    m_size = QString::number((double)info.size() / 1000000, 'g', 3);
    m_favorite = favorite;
    m_rotation = 0;

    m_fileformat = readFormat(m_name, info.suffix());
    m_recorded = readDate();
    readLabels();
    log();
}


QDateTime BaseFile::readDate()
{
    // Default time
    QDateTime time(QDate(1,1,1), QTime(0,0));

    switch(m_fileformat)
    {
    case FileFormat::Other:
        // Use created time
        time = m_created;
        break;

    case FileFormat::Camera:
        time = readDateCamera();
        break;

    case FileFormat::Mobile:
        // Example: 20170629_180824
        time.setDate(QDate::fromString(m_name.mid(0, 8), "yyyyMMdd"));
        time.setTime(QTime::fromString(m_name.mid(9, 6), "hhmmss"));
        break;

    case FileFormat::Message:
        // Example: IMG-20151206-WA0000.jpg
        // Example: VID-20151206-WA0000.mp4
        time.setDate(QDate::fromString(m_name.mid(4, 8), "yyyyMMdd"));
        break;
    }

    return time;
}


QString BaseFile::fileDate(Order order)
{
    QString str;
    QDateTime date;

    switch(order)
    {
    case Order::Name:
    case Order::Type:
    case Order::Recorded: str = "Recorded: "; date = m_recorded; break;
    case Order::Created:  str = "Created: ";  date = m_created;  break;
    case Order::Modified: str = "Modified: "; date = m_modified; break;
    }
    return str += date.toString("dd.MM.yyyy-hh:mm");
}


QString BaseFile::dateStr()
{
    return m_recorded.toString("dd.MM.yyyy-hh:mm");
}


QString BaseFile::formatStr()
{
    return QVariant::fromValue(m_fileformat).toString();
}


QString BaseFile::typeStr()
{
    return QVariant::fromValue(m_filetype).toString();
}
