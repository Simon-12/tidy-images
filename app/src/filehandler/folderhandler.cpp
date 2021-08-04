#include "folderhandler.h"


FolderHandler::FolderHandler(Settings set, QObject *parent) :
    BaseHandler(set.json, parent)
{    

}


void FolderHandler::initTest()
{
    initModel();
    QString path = QDir::currentPath() + "/Test";
    addFolder(path);
    QDir().mkdir(path);
}


void FolderHandler::updateFile()
{
    write();
}


void FolderHandler::initModel()
{
    m_model = new FolderModel(this);
    connect(m_model, &FolderModel::modelChanged, this, &FolderHandler::updateFile);

    m_filter = new FolderFilterModel(this);
    m_filter->setSourceModel(m_model);
    connect(m_filter, &FolderFilterModel::move, m_model, &FolderModel::moveKey);
}


bool FolderHandler::addFolder(QString path)
{
    int idx = path.lastIndexOf("/") + 1;
    QString folder = path.mid(idx);

    if(m_model->contains(folder))
    {
        MessageBox("Folder already exist!");
        return false;
    }

    qInfo() << "Add Folder:" << folder;
    m_model->append(FolderItem(folder, path, true));

    write();
    return true;
}


void FolderHandler::read()
{
    initModel();

    // Read file
    QByteArray data = readFile();
    QJsonDocument document = QJsonDocument::fromJson(data);

    // Create json object
    QJsonObject obj;
    obj = document["Folders"].toObject();

    // Sort keys with position and add to model
    QStringList folders = obj.keys();
    for(int i = 0; i < folders.size(); i++)
    {
        foreach(QString item, folders)
        {
            QJsonValue value = obj[item];
            if(i == value["Position"].toInt())
            {
                m_model->append(FolderItem(item,
                                           value["Path"].toString(),
                                value["Selected"].toBool()
                        )
                        );
                break; // Stop foreach loop
            }
        }
    }
    qInfo() << "Read Json file";
}


void FolderHandler::write()
{
    // Create json objects
    QJsonObject obj_all;

    // Read Model Data
    for(int i = 0; i < m_model->size(); i++)
    {
        FolderItem item = m_model->getItem(i);
        QJsonObject obj;
        obj["Position"] = i;
        obj["Selected"] = item.selected();
        obj["Path"] = item.path();
        obj_all[item.name()] = obj;
    }

    // Create json document
    QJsonObject json_root;
    json_root["Folders"] = obj_all;
    QJsonDocument document(json_root);

    // Save
    writeFile(document.toJson());
    qInfo() << "Write Json file";
}


void FolderHandler::defaultFile()
{
    initModel();
}
