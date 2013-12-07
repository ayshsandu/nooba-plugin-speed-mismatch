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
    static const QString ITEM_SPEED_ANOMALY_MAX;
    static const QString ITEM_SPEED_ANOMALY_MIN;
    static const QString ITEM_SPEED_ANOMALY_RANGE;

    static const QString LABLE_MAX_SPEED;
    static const QString LABLE_MIN_SPEED;
    static const QString LABLE_SELECT_ANOMALY ;

    static const int DEFAULT_MAX_SPEED;
    static const int DEFAULT_MIN_SPEED;

    static const int MAX_SPEED_UPPER_BOUND;
    static const int MAX_SPEED_LOWER_BOUND;
    static const int MIN_SPEED_UPPER_BOUND;
    static const int MIN_SPEED_LOWER_BOUND;

};

#endif // CONFIGURATION_H
