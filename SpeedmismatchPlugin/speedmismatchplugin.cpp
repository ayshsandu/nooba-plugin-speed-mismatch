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
//    QList<DetectedEvent> blobevents;

//    blobevents.append(DetectedEvent("blob","1,1,100.0,100.0",1.0));
//    blobevents.append(DetectedEvent("blob","2,2,1000.0,100.0",1.0));
//    blobevents.append(DetectedEvent("blob","3,1,160.0,100.0",1.0));
//    blobevents.append(DetectedEvent("blob","4,1,260.0,100.0",1.0));
//    blobevents.append(DetectedEvent("blob","5,2,2000.0,100.0",1.0));
//    blobevents.append(DetectedEvent("blob","6,1,100.0,180.0",1.0));

//    emit generateEvent(blobevents);
//    return true;
}

bool SpeedmismatchPlugin::init()
{

    set_speed_anomaly_list.append(config.getItemSpeedAnomalyMax());
    set_speed_anomaly_list.append(config.getItemSpeedAnomalyMin());
    set_speed_anomaly_list.append(config.getItemSpeedAnomalyRange());

    /**Assign default values for variables*/
    Max_Speed_thresh = config.getDefaultMaxSpeed();
    Min_Speed_thresh = config.getDefaultMinSpeed();
    selected_anomaly =  set_speed_anomaly_list.at(0);

    /**setup default variable values in speed mismatch calculation node */
    BlobSpeedMismatchNode.setMaxSpeedThresh(Max_Speed_thresh);
    BlobSpeedMismatchNode.setMinSpeedThresh(Min_Speed_thresh);
    BlobSpeedMismatchNode.setSpeedAnomaly(selected_anomaly);

    /**create parameters in the GUI with the lables from config class*/
    createIntParam(config.getLableMaxSpeed(),Max_Speed_thresh,config.getMaxSpeedUpperBound(),config.getMaxSpeedLowerBound());
    createIntParam(config.getLableMinSpeed(),Min_Speed_thresh,config.getMinSpeedUpperBound(),config.getMinSpeedLowerBound());
    createMultiValParam(config.getLableSeleceSpeedAnomaly(), set_speed_anomaly_list);

    mismatchCount=0;
    /**connect signals and slots*/
    connect(this, SIGNAL(generateEvent(QList<DetectedEvent>)), &blobSpeedNode, SLOT(captureEvent(QList<DetectedEvent>)));//captures blob events from currents node>>to speed node to calculate speed
    connect(&blobSpeedNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &BlobSpeedMismatchNode, SLOT(captureEvent(QList<DetectedEvent>)));// speed node output >> speed mismatch desiding node
    connect(&BlobSpeedMismatchNode, SIGNAL(generateEvent(QList<DetectedEvent>)), this, SLOT(onCaptureEvent(QList<DetectedEvent>)));//speed mismatch deciding node result>> current node to show out put

    createFrameViewer("test",true);

    debugMsg("Speed Mismatch Plugin Initialized");

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
        "Plugin to detect speed mismatching anomalies",
        "Team Nooba");
    return pluginInfo;

 }

void SpeedmismatchPlugin::onIntParamChanged(const QString& varName, int val){

    if(varName ==config.getLableMaxSpeed()){
        // assign GUI input value to max_speed_variable to compare
        Max_Speed_thresh = val;
        BlobSpeedMismatchNode.setMaxSpeedThresh(Max_Speed_thresh);
        debugMsg("Max_Speed Threshold set to "  + QString("%1").arg(val));


    }
    if(varName ==config.getLableMinSpeed()){
        // assign GUI input value to min_speed_variable to compare
        Min_Speed_thresh = val;
        BlobSpeedMismatchNode.setMinSpeedThresh(Min_Speed_thresh);
        set_speed_anomaly_list.append("Min Speed Limit Anomaly");debugMsg("Min_Speed Threshold set to "  + QString("%1").arg(val));

    }
}

void SpeedmismatchPlugin::onMultiValParamChanged(const QString &varName, const QString &val){
    if(varName ==config.getLableSeleceSpeedAnomaly()){
        // load GUI input selection to select anomaly type
        selected_anomaly = val;
        BlobSpeedMismatchNode.setSpeedAnomaly(selected_anomaly);
        debugMsg("Speed anomaly set to "  +QString("%1").arg(selected_anomaly));
    }
}

void SpeedmismatchPlugin::onCaptureEvent(QList<DetectedEvent> captured_event){

    mismatchCount++;
           if(mismatchCount<5){return;}
    foreach(DetectedEvent e, captured_event){

         debugMsg(QString("<FONT COLOR='#ff0000'>"+e.getIdentifier() + " " + e.getMessage() + " %1").arg(e.getConfidence()));
         //debugMsg(QString(e.getIdentifier() + " " + e.getMessage() + " %1").arg(e.getConfidence()));
         generateAlert("test","------",nooba::RedAlert);
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

void SpeedmismatchPlugin::inputData(const QStringList &strList, QList<QImage> imageList){

    // qDebug()<<"aaaaaabbbbbdddddd";
    QList<DetectedEvent> receivedEvents;
    QStringList stringList = strList;
    foreach(QString str,stringList){
        //debugMsg("recv" + str);
        QList<QString> parameters = str.split(" ");
        receivedEvents.append(DetectedEvent(parameters.at(0),parameters.at(1),parameters.at(2).toFloat()));
    }

     emit generateEvent(receivedEvents);

    //cv::Mat lineviewer(temp.height(),temp.width(),CV_8UC3,(uchar*)temp.bits(),temp.bytesPerLine());


    cv::Mat frame(imageList.at(0).height(),imageList.at(0).width(),CV_8UC3,(uchar*)imageList.at(0).bits(),imageList.at(0).bytesPerLine());
    //cv::Mat bgmask(imageList.at(1).height(),imageList.at(1).width(),CV_8UC1,(uchar*)imageList.at(1).bits(),imageList.at(1).bytesPerLine());
    //cv::imshow("test",bgmask);
    updateFrameViewer("test",convertToQImage(frame));

}

QImage SpeedmismatchPlugin::convertToQImage(cv::Mat &cvImg)
{
    if (cvImg.channels()== 1){
        QImage img((uchar*)cvImg.data, cvImg.cols, cvImg.rows, cvImg.step1(), QImage::Format_Indexed8);
        return img;
    }
    else{
        QImage img((uchar*)cvImg.data, cvImg.cols, cvImg.rows, cvImg.step1(), QImage::Format_RGB888);
        return img;
    }
}

//void SpeedmismatchPlugin::in

// see qt4 documentation for details on the macro (Qt Assistant app)
// Mandatory  macro for plugins in qt4. Made obsolete in qt5
#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2(SpeedmismatchPlugin, SpeedmismatchPlugin);
#endif
