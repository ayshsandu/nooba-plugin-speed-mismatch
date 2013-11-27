#include "speedmismatchnode.h"

speedmismatchnode::speedmismatchnode(FeatureNode *parent):
    FeatureNode(parent)
{
}

void speedmismatchnode::setMaxSpeedThresh(int val){
    Max_Speed_Thresh = val;
}

void speedmismatchnode::setMinSpeedThresh(int val){
    Min_Speed_Thresh = val;
}

void speedmismatchnode::setSpeedAnomaly(QString val){
    Selected_Anmaly = val;
}

void speedmismatchnode::processEvents(const QList<DetectedEvent> event)
{
    SPEEDANOMALYMAX = "Max Speed Limit Anomaly";
    SPEEDANOMALYMIN = "Min Speed Limit Anomaly";
    SPEEDANOMALYRANGE = "Speed Range Limit Anomaly";

    QList<DetectedEvent> speedMismatchEvent;

    if(!event.isEmpty()){
        QList<QString> id = event.at(0).getIdentifier().split("_");
        if(id.at(0) == "speed"){
                    //Insert new speed events to the hash map.
                    //If already exists the key, this will replace the previous version
                    foreach(DetectedEvent e, event){
                        QList<QString> message = e.getMessage().split(",");
                        //speedEvents.insert(message.at(1),e);
                        if(Selected_Anmaly == SPEEDANOMALYMAX){
                            int speed = message.at(2).toInt();
                            if(isMaxSpeedThresholdpassed(speed)){
                                speedMismatchEvent.append(DetectedEvent("SPMMObj",QString("Frame %1,Blob %2, passed max speed, %3").arg(message.at(0)).arg(message.at(1)).arg(message.at(2)),1.0));

                            }
                        }
                        else if(Selected_Anmaly == SPEEDANOMALYMIN){
                            int speed = message.at(2).toInt();
                            if(isMinSpeedThresholdBelowed(speed)){
                                speedMismatchEvent.append(DetectedEvent("SPMMObj",QString("Frame %1,Blob %2, Less than min speed, %3").arg(message.at(0)).arg(message.at(1)).arg(message.at(2)),1.0));

                            }
                        }
                        else if(Selected_Anmaly == SPEEDANOMALYRANGE){
                            int speed = message.at(2).toInt();
                            if(isMaxSpeedThresholdpassed(speed) && isMinSpeedThresholdBelowed(speed)){
                                speedMismatchEvent.append(DetectedEvent("SPMMObj",QString("Frame %1,Blob %2, is out of speed range, %3").arg(message.at(0)).arg(message.at(1)).arg(message.at(2)),1.0));

                            }
                        }
                    }
                }
        if(!speedMismatchEvent.isEmpty()){
            emit generateEvent(speedMismatchEvent);
        }
    }
}

bool speedmismatchnode::isMaxSpeedThresholdpassed(int val){
    if(val> Max_Speed_Thresh){
        return true;
    }
    return false;
}

bool speedmismatchnode::isMinSpeedThresholdBelowed(int val){
    if(val< Min_Speed_Thresh){
        return true;
    }
    return false;
}

