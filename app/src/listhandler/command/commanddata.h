#ifndef COMMANDDATA_H
#define COMMANDDATA_H

#include <QObject>

#include "../basefile/basefile.h"
#include "../database/database.h"
#include "../models/imagemodel.h"
#include "support.h"

/*!
 * \brief The CommandData class:
 * Command data for the command classes.
 */
class CommandData
{

public:

    int index;
    FilePtr file;
    QString source;
    QString target;
    AppMode mode;
    FileList* fileList;
    ImageModel* imageModel;
    FileModel* fileModel;
    Database* database;
};

#endif // COMMANDDATA_H
