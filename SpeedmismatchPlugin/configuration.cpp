#include "configuration.h"



Configuration::Configuration()
{
}

QString Configuration::getItemSpeedAnomalyMax(){return ITEM_SPEED_ANOMALY_MAX;}
QString Configuration::getItemSpeedAnomalyMin(){return ITEM_SPEED_ANOMALY_MIN;}
QString Configuration::getItemSpeedAnomalyRange(){return ITEM_SPEED_ANOMALY_RANGE;}

QString Configuration::getLableMaxSpeed(){return LABLE_MAX_SPEED;}
QString Configuration::getLableMinSpeed(){return LABLE_MIN_SPEED;}
QString Configuration::getLableSeleceSpeedAnomaly(){return LABLE_SELECT_ANOMALY;}

int Configuration::getDefaultMaxSpeed(){return DEFAULT_MAX_SPEED;}
int Configuration::getDefaultMinSpeed(){return DEFAULT_MIN_SPEED;}

int Configuration::getMaxSpeedUpperBound(){return MAX_SPEED_UPPER_BOUND;}
int Configuration::getMinSpeedUpperBound(){return MIN_SPEED_UPPER_BOUND;}
int Configuration::getMaxSpeedLowerBound(){return MAX_SPEED_LOWER_BOUND;}
int Configuration::getMinSpeedLowerBound(){return MIN_SPEED_LOWER_BOUND;}

const QString Configuration::ITEM_SPEED_ANOMALY_MAX = "Max Speed Limit Anomaly";
const QString Configuration::ITEM_SPEED_ANOMALY_MIN = "Min Speed Limit Anomaly";
const QString Configuration::ITEM_SPEED_ANOMALY_RANGE = "Speed Range Limit Anomaly";

const QString Configuration::LABLE_MAX_SPEED = "Max Speed";
const QString Configuration::LABLE_MIN_SPEED = "Min Speed";
const QString Configuration::LABLE_SELECT_ANOMALY = "Select Speed Anomaly";

const int Configuration::DEFAULT_MAX_SPEED=60;
const int Configuration::DEFAULT_MIN_SPEED=30;

const int Configuration::MAX_SPEED_UPPER_BOUND=1000;
const int Configuration::MAX_SPEED_LOWER_BOUND=0;
const int Configuration::MIN_SPEED_UPPER_BOUND=1000;
const int Configuration::MIN_SPEED_LOWER_BOUND=0;
