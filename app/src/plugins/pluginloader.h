#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>

#include "exivplugin.h"
#include "visionplugin.h"
#include "pluginmodel.h"

/*!
 * \brief The PluginLoader class:
 * Initialize plugins and fill the model.
 */
class PluginLoader : public QObject
{
    Q_OBJECT

public:

    explicit PluginLoader(QObject *parent = nullptr);

    // Getter
    ExivPlugin* exivPlugin(){ return m_exiv; }
    VisionPlugin* visionPlugin(){ return m_vision; }
    PluginModel* model(){ return m_model; }

private:

    QString m_path;
    ExivPlugin* m_exiv;
    VisionPlugin* m_vision;
    PluginModel* m_model;
};

#endif // PLUGINLOADER_H
