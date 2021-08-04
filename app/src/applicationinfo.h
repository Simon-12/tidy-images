#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

#include <QObject>
#include <QDirIterator>
#include <QFontDatabase>
#include <QDebug>
#include <QFile>

#include "iconmodel.h"

/*!
 * \brief The ApplicationInfo class:
 * Informations about the application.
 * Handles the icon model and loads the fonts.
 */
class ApplicationInfo : public QObject
{
    Q_OBJECT

public:

    Q_PROPERTY(QString about    READ getAbout   CONSTANT)
    Q_PROPERTY(QString story    READ getStory   CONSTANT)
    Q_PROPERTY(QString paypal   READ getPaypal  CONSTANT)
    Q_PROPERTY(QString btc      READ getBtc     CONSTANT)
    Q_PROPERTY(QString website  READ getWebsite CONSTANT)
    Q_PROPERTY(QString license  READ getLicense CONSTANT)
    Q_PROPERTY(QString qtinfo   READ getQtInfo  CONSTANT)
    Q_PROPERTY(IconModel* model READ getModel   CONSTANT)

    explicit ApplicationInfo(QObject *parent = nullptr);
    static void loadFonts();

private:

    QString getAbout(){ return m_about; }
    QString getStory(){ return m_story; }
    QString getPaypal(){ return m_paypal; }
    QString getBtc(){ return m_btc; }
    QString getWebsite(){ return m_website; }
    QString getLicense(){ return m_license; }
    QString getQtInfo(){ return m_QtInfo; }
    IconModel* getModel(){ return m_model; }
    void initFlatIcons();
    void initMaterialIcons();

    QString m_about;
    QString m_story;
    QString m_paypal;
    QString m_btc;
    QString m_website;
    QString m_report;
    QString m_version;
    QString m_license;
    QString m_QtInfo;
    IconModel* m_model;
};

#endif // APPLICATIONINFO_H
