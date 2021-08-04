#ifndef FOLDERHANDLER_H
#define FOLDERHANDLER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "foldermodel.h"
#include "folderfiltermodel.h"
#include "basehandler.h"
#include "../settings.h"

/*!
 * \brief The FolderHandler class:
 * File handler for the json file.
 * Reads and writes the used folders.
 * Handles the model for ui.
 */
class FolderHandler : public BaseHandler
{
    Q_OBJECT

public:

    explicit FolderHandler(Settings set, QObject *parent = nullptr);
    void initTest();

    bool addFolder(QString path);
    FolderModel* folderModel() { return m_model; }
    FolderFilterModel* selectedModel() { return m_filter; }

public slots:

    void updateFile();

private:

    FolderModel *m_model;
    FolderFilterModel *m_filter;

    void initModel();

    // BaseHandler interface
protected:

    void read();
    void write();
    void defaultFile();
};

#endif // FOLDERHANDLER_H
