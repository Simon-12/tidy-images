#ifndef LISTMODELS_H
#define LISTMODELS_H

#include <QObject>
#include <QSqlQueryModel>

#include "../compare/tablemodel.h"
#include "../database/headermodel.h"
#include "../command/commandmodel.h"
#include "labelmodel.h"
#include "filemodel.h"

/*!
 * \brief The ListModels class:
 * Contains all models for the list handler.
 */
class ListModels
{
    Q_GADGET

public:

    Q_PROPERTY(ImageModel*     images   MEMBER m_images)
    Q_PROPERTY(LabelModel*     labels   MEMBER m_labels)
    Q_PROPERTY(TableModel*     table    MEMBER m_table)
    Q_PROPERTY(QSqlQueryModel* database MEMBER m_database)
    Q_PROPERTY(HeaderModel*    header   MEMBER m_header)
    Q_PROPERTY(FileModel*      files    MEMBER m_files)
    Q_PROPERTY(CommandModel*   command  MEMBER m_command)
    Q_PROPERTY(bool     databaseActive  MEMBER m_databaseActive)

    void setImages(ImageModel *images){ m_images = images; }
    void setLabels(LabelModel *labels){ m_labels = labels; }
    void setTable(TableModel *table){ m_table = table; }
    void setDatabase(QSqlQueryModel *database){ m_database = database; }
    void setHeader(HeaderModel *header){ m_header = header; }
    void setFiles(FileModel *files){ m_files = files; }
    void setCommand(CommandModel *command){ m_command = command; }
    void setDatabaseActive(bool state){ m_databaseActive = state; }

private:

    ImageModel* m_images;
    LabelModel* m_labels;
    TableModel*  m_table;
    QSqlQueryModel* m_database;
    HeaderModel* m_header;
    FileModel* m_files;
    CommandModel* m_command;
    bool m_databaseActive;
};

Q_DECLARE_METATYPE(ListModels) // for QML

#endif // LISTMODELS_H
