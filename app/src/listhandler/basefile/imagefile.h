#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <QObject>
#include <QImage>

#include "plugins/exivplugin.h"
#include "basefile.h"


/*!
 * \brief The ImageFile class:
 * Image file
 */
class ImageFile : public BaseFile
{
    Q_GADGET

public:

    explicit ImageFile();

    QString sizeStr();
    QString scoreStr();
    double* score(){ return &m_score; }
    void setScore(double score){ m_score = score; }

    void setLabels(const QStringList &labels) override;
    void setRotation(bool direction) override;
    static void setPlugin(ExivPlugin* plg){ plugin = plg; }


protected:

    FileFormat readFormat(QString name, QString extension) override;
    QDateTime readDateCamera() override;
    void readLabels() override;
    void log() override;

private:

    QString m_dimensions;
    double m_score;
    static ExivPlugin* plugin;
};

typedef QSharedPointer<ImageFile> ImagePtr;

#endif // IMAGEFILE_H
