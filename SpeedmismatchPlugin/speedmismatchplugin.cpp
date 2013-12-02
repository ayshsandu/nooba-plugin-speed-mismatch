#include "speedmismatchplugin.h"
#include <QtCore>
#include <opencv2/core/core.hpp>

SpeedmismatchPlugin::SpeedmismatchPlugin()
{
    //qDebug()<<"-----------Speed Mismatch Plugin Initialized";
    //debugMsg("Speed Mismatch Plugin Initialized");

}

SpeedmismatchPlugin::~SpeedmismatchPlugin()
{
    //debugMsg("Speed Mismatch Plugin Destructed");

}

bool SpeedmismatchPlugin::procFrame( const cv::Mat &in, cv::Mat &out, ProcParams &params )
{
    QList<DetectedEvent> blobevents;

    blobevents.append(DetectedEvent("blob","1,1,100.0,100.0",1.0));
    blobevents.append(DetectedEvent("blob","2,2,1000.0,100.0",1.0));
    blobevents.append(DetectedEvent("blob","3,1,160.0,100.0",1.0));
    blobevents.append(DetectedEvent("blob","4,1,260.0,100.0",1.0));
    blobevents.append(DetectedEvent("blob","5,2,2000.0,100.0",1.0));
    blobevents.append(DetectedEvent("blob","6,1,100.0,180.0",1.0));

    emit generateEvent(blobevents);
    return true;
}

bool SpeedmismatchPlugin::init()
{
    Max_Speed_thresh = 60;
    Min_Speed_thresh = 30;

    BlobSpeedMismatchNode.setMaxSpeedThresh(Max_Speed_thresh);
    BlobSpeedMismatchNode.setMinSpeedThresh(Min_Speed_thresh);

    createIntParam("Max_Speed",Max_Speed_thresh,100,0);
    createIntParam("Min_Speed",Min_Speed_thresh,100,0);

    set_speed_anomaly_list.append("Max Speed Limit Anomaly");
    set_speed_anomaly_list.append("Min Speed Limit Anomaly");
    set_speed_anomaly_list.append("Speed Range Limit Anomaly");

    selected_anomaly =  set_speed_anomaly_list.at(0);

    createMultiValParam("Select Speed anomaly", set_speed_anomaly_list);

    connect(this, SIGNAL(generateEvent(QList<DetectedEvent>)), &blobSpeedNode, SLOT(captureEvent(QList<DetectedEvent>)));
    connect(&blobSpeedNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &BlobSpeedMismatchNode, SLOT(captureEvent(QList<DetectedEvent>)));
    connect(&BlobSpeedMismatchNode, SIGNAL(generateEvent(QList<DetectedEvent>)), this, SLOT(onCaptureEvent(QList<DetectedEvent>)));

    debugMsg("Speed Mismatch Plugin Initialized");

//    QList<DetectedEvent> blobevents;

//    blobevents.append(DetectedEvent("blob","4,1,10.0,10.0",1.0));
//    blobevents.append(DetectedEvent("blob","5,1,2000.0,200.0",1.0));
//    blobevents.append(DetectedEvent("blob","6,1,1600.0,180.0",1.0));

//    emit generateEvent(blobevents);

    // debugMsg("initializing");
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
        "Plugin to detect speed anomalies",
        "Ayesha Dissanayaka");
    return pluginInfo;

 }

void SpeedmismatchPlugin::onIntParamChanged(const QString& varName, int val){

    if(varName =="Max_Speed"){
        // assign value to max_speed_variable to compare
        Max_Speed_thresh = val;
        BlobSpeedMismatchNode.setMaxSpeedThresh(Max_Speed_thresh);
        debugMsg("Max_Speed Threshold set to "  + QString("%1").arg(val));


    }
    if(varName =="Min_Speed"){
        // assign value to min_speed_variable to compare
        Min_Speed_thresh = val;
        BlobSpeedMismatchNode.setMinSpeedThresh(Min_Speed_thresh);
        set_speed_anomaly_list.append("Min Speed Limit Anomaly");debugMsg("Min_Speed Threshold set to "  + QString("%1").arg(val));

    }
}

void SpeedmismatchPlugin::onMultiValParamChanged(const QString &varName, const QString &val){
    if(varName =="Select Speed anomaly"){
        // assign value to max_speed_variable to compare
        selected_anomaly = set_speed_anomaly_list.at(val.toInt());
        BlobSpeedMismatchNode.setSpeedAnomaly(selected_anomaly);
        debugMsg("Speed anomaly set to "  +QString("%1").arg(selected_anomaly));
    }
}

void SpeedmismatchPlugin::onCaptureEvent(QList<DetectedEvent> captured_event){

    foreach(DetectedEvent e, captured_event){
        debugMsg(QString(e.getIdentifier() + " " + e.getMessage() + " %1").arg(e.getConfidence()));
    }
    return;

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
