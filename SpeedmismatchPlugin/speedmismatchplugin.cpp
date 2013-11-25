#include "speedmismatchplugin.h"
#include <QtCore>
#include <opencv2/core/core.hpp>

SpeedmismatchPlugin::SpeedmismatchPlugin()
{

}

SpeedmismatchPlugin::~SpeedmismatchPlugin()
{

}

bool SpeedmismatchPlugin::procFrame( const cv::Mat &in, cv::Mat &out, ProcParams &params )
{

    return true;
}

bool SpeedmismatchPlugin::init()
{
    return true;
}

bool SpeedmismatchPlugin::release()
{
    return true;
}

PluginInfo SpeedmismatchPlugin::getPluginInfo() const
{
    PluginInfo pluginInfo(
        "Speed Mismatch Plugin",
        0,
        1,
        "Plugin to detect soeed anomalies",
        "Ayesha Dissanayaka");
    return pluginInfo;

 }

void SpeedmismatchPlugin::inputData(const PluginPassData& data){

    QList<DetectedEvent> receivedEvents;
    foreach(QString str,data.strList()){
        debugMsg("recv" + str);
        QList<QString> parameters = str.split(" ");
        receivedEvents.append(DetectedEvent(parameters.at(0),parameters.at(1),parameters.at(2).toFloat()));
    }
    emit generateEvent(receivedEvents);
}

// see qt4 documentation for details on the macro (Qt Assistant app)
// Mandatory  macro for plugins in qt4. Made obsolete in qt5
#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2(SpeedmismatchPlugin, SpeedmismatchPlugin);
#endif
