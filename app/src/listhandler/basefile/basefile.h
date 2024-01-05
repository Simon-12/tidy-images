#ifndef BASEFILE_H
#define BASEFILE_H

#include <QDataStream>
#include <QDateTime>
#include <QFileInfo>
#include <QObject>
#include <QRegularExpression>
#include <QSharedPointer>
#include <QtDebug>

#include "options.h"

/*!
 * \brief The BaseFile class:
 * Base file interface with base variables and virtual functions.
 */
class BaseFile {
    Q_GADGET

public:
    explicit BaseFile();
    ~BaseFile();

    void init(const QFileInfo& info, bool favorite);
    QString fileDate(Order order);
    QString dateStr();
    QString formatStr();
    QString typeStr();

    enum FileFormat { Camera, Mobile, Message, Other };
    enum FileType { Image, Video };
    Q_ENUM(FileFormat)
    Q_ENUM(FileType)

    // Getter (references)
    QString* name() { return &m_name; }
    QString* path() { return &m_path; }
    FileFormat* fileformat() { return &m_fileformat; }
    QDateTime* created() { return &m_created; }
    QDateTime* modified() { return &m_modified; }
    QDateTime* recorded() { return &m_recorded; }
    QStringList* labels() { return &m_labels; }
    bool* favorite() { return &m_favorite; }
    int* rotation() { return &m_rotation; }
    QString* duration() { return &m_duration; }
    FileType* filetype() { return &m_filetype; }

    // Setter
    void setFavorite(bool state) { m_favorite = state; }
    virtual void setLabels(const QStringList& labels) = 0;
    virtual void setRotation(bool direction) = 0;
    void resetRotation() { m_rotation = 0; }

    friend QDataStream& operator<<(QDataStream& stream, const BaseFile& file);
    friend QDataStream& operator>>(QDataStream& stream, BaseFile& file);

protected:
    QString m_name;
    QString m_path;
    QStringList m_labels;
    QDateTime m_created;
    QString m_size;
    QString m_duration;
    int m_rotation;
    FileType m_filetype;
    QRegularExpression m_rexp;

    virtual FileFormat readFormat(QString name, QString extension) = 0;
    virtual QDateTime readDateCamera() = 0;
    virtual void readLabels() = 0;
    virtual void log() = 0;

private:
    FileFormat m_fileformat;
    QDateTime m_modified;
    QDateTime m_recorded;
    bool m_favorite;

    QDateTime readDate();
};

typedef QSharedPointer<BaseFile> FilePtr;
typedef QList<FilePtr> FileList;

#endif  // BASEFILE_H
