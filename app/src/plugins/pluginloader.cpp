#include "pluginloader.h"


PluginLoader::PluginLoader(QObject *parent) : QObject(parent)
{
    m_model = new PluginModel(this);
    m_path = "plugins";
    qInfo() << "Load Plugins";

    // Exiv Plugin
    m_exiv = loadPlugin<ExivPlugin>(m_path);
    if(m_exiv)
        m_model->append(m_exiv);

    // Vision Plugin
    m_vision = loadPlugin<VisionPlugin>(m_path);
    if(m_vision)
        m_model->append(m_vision);
}
