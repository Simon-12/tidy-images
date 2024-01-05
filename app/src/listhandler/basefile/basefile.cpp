#include "basefile.h"

BaseFile::BaseFile() {
    // digit (\d) + zero or more times (+)
    m_rexp = QRegularExpression("\\d+");
}

BaseFile::~BaseFile() {}

void BaseFile::init(const QFileInfo& info, bool favorite) {
    m_name = info.fileName();
    m_path = info.absoluteFilePath();
    m_modified = info.lastModified();
    m_created = info.birthTime();
    if (!m_created.isValid()) m_created = m_modified;
    m_size = QString::number((double)info.size() / 1000000, 'g', 3);
    m_favorite = favorite;
    m_rotation = 0;

    m_fileformat = readFormat(m_name, info.suffix());
    m_recorded = readDate();
    if (!m_recorded.isValid()) m_recorded = m_created;
    readLabels();
    log();
}

QDateTime BaseFile::readDate() {
    // Default time
    QDateTime time(QDate(1, 1, 1), QTime(0, 0));
    // Copy name
    QString name(m_name);

    switch (m_fileformat) {
        case FileFormat::Other:
            // Use created time
            time = m_created;
            break;

        case FileFormat::Camera:
            time = readDateCamera();
            break;

        case FileFormat::Mobile:
            // Example: 20170629_180824
            // Example: PXL_20221119_122755414.jpg
            name.remove("PXL_");
            time.setDate(QDate::fromString(name.mid(0, 8), "yyyyMMdd"));
            time.setTime(QTime::fromString(name.mid(9, 6), "hhmmss"));
            break;

        case FileFormat::Message:
            // Example: IMG-20151206-WA0000.jpg
            // Example: VID-20151206-WA0000.mp4
            // Example: signal-2021-09-18-183330.jpeg
            if (name.startsWith("signal-")) {
                name.remove("signal-");
                time.setDate(QDate::fromString(name.mid(0, 10), "yyyy-MM-dd"));
                time.setTime(QTime::fromString(name.mid(11, 6), "hhmmss"));
                break;
            }
            name.remove("IMG-");
            name.remove("VID-");
            time.setDate(QDate::fromString(name.mid(0, 8), "yyyyMMdd"));
            break;
    }
    return time;
}

QString BaseFile::fileDate(Order order) {
    QString str;
    QDateTime date;

    switch (order) {
        case Order::Name:
        case Order::Type:
        case Order::Recorded:
            str = "Recorded: ";
            date = m_recorded;
            break;
        case Order::Created:
            str = "Created: ";
            date = m_created;
            break;
        case Order::Modified:
            str = "Modified: ";
            date = m_modified;
            break;
    }
    return str += date.toString("dd.MM.yyyy-hh:mm");
}

QString BaseFile::dateStr() { return m_recorded.toString("dd.MM.yyyy-hh:mm"); }

QString BaseFile::formatStr() { return QVariant::fromValue(m_fileformat).toString(); }

QString BaseFile::typeStr() { return QVariant::fromValue(m_filetype).toString(); }

QDataStream& operator<<(QDataStream& stream, const BaseFile& file) {
    stream << file.m_name;
    stream << file.m_path;
    stream << file.m_labels;
    stream << file.m_created;
    stream << file.m_size;
    stream << file.m_duration;
    stream << file.m_filetype;
    stream << file.m_fileformat;
    stream << file.m_modified;
    stream << file.m_recorded;
    stream << file.m_favorite;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, BaseFile& file) {
    stream >> file.m_name;
    stream >> file.m_path;
    stream >> file.m_labels;
    stream >> file.m_created;
    stream >> file.m_size;
    stream >> file.m_duration;
    stream >> file.m_filetype;
    stream >> file.m_fileformat;
    stream >> file.m_modified;
    stream >> file.m_recorded;
    stream >> file.m_favorite;
    return stream;
}
