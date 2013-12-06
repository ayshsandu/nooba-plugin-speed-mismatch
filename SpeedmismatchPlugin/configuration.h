#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtCore>

class Configuration
{
       // static const QString ITEM_SPEED_ANOMALY_MAX;
public:
    Configuration();
    QString getItemSpeedAnomalyMax();
    QString getItemSpeedAnomalyMin();
    QString getItemSpeedAnomalyRange();

    QString getLableMaxSpeed();
    QString getLableMinSpeed();
    QString getLableSeleceSpeedAnomaly();

    int getDefaultMaxSpeed();
    int getDefaultMinSpeed();

    int getMaxSpeedUpperBound();
    int getMinSpeedUpperBound();
    int getMaxSpeedLowerBound();
    int getMinSpeedLowerBound();

private:
    static const QString ITEM_SPEED_ANOMALY_MAX;// = "Max Speed Limit Anomaly";
    static const QString ITEM_SPEED_ANOMALY_MIN;// = "Min Speed Limit Anomaly";
    static const QString ITEM_SPEED_ANOMALY_RANGE;// = "Speed Range Limit Anomaly";

    static const QString LABLE_MAX_SPEED;// = "Max Speed";
    static const QString LABLE_MIN_SPEED;// = "Min Speed";
    static const QString LABLE_SELECT_ANOMALY ;//= "Selece Speed Anomaly";

    static const int DEFAULT_MAX_SPEED;
    static const int DEFAULT_MIN_SPEED;

    static const int MAX_SPEED_UPPER_BOUND;
    static const int MAX_SPEED_LOWER_BOUND;
    static const int MIN_SPEED_UPPER_BOUND;
    static const int MIN_SPEED_LOWER_BOUND;

};

#endif // CONFIGURATION_H
