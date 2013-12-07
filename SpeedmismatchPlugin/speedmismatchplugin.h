#ifndef SPEEDMISMATCHPLUGIN_H
#define SPEEDMISMATCHPLUGIN_H

#include "speedmismatchplugin_global.h"
#include "noobapluginapi.h"
#include "NoobaVSSAD/detectedevent.h"
#include "NoobaVSSAD/speednode.h"
#include  "speedmismatchnode.h"
#include "configuration.h"

#include <QObject>

class SPEEDMISMATCHPLUGIN_EXPORT SpeedmismatchPlugin: public NoobaPluginAPI
{
    Q_OBJECT
    Q_INTERFACES(NoobaPluginAPI)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "nooba.plugins.qt5.speedmismatch-plugin" FILE "speedmismatchPlugin.json")
#endif

public:
    SpeedmismatchPlugin();
    ~SpeedmismatchPlugin();

    bool procFrame(const cv::Mat &in, cv::Mat &out, ProcParams &params);
    bool init();
    bool release();
    PluginInfo getPluginInfo() const;



public slots:
    void onIntParamChanged(const QString& varName, int val);
    void onMultiValParamChanged(const QString& varName, const QString& val);
    void onCaptureEvent(QList<DetectedEvent> captured_event);

    void inputData(const PluginPassData& data);
    void inputData(const QStringList &strList, QList<QImage> imageList);
    QImage convertToQImage(cv::Mat &cvImg);

signals:
    void generateEvent(QList<DetectedEvent> generated_event);
    /**
     * These functions will be called when the parameters are changed by the
     * user.
     */
   // void onIntParamChanged(const QString& varName, int val);
//    void onDoubleParamChanged(const QString& varName, double val);
//    void onStringParamChanged(const QString& varName, const QString& val);
//    void onMultiValParamChanged(const QString& varName, const QString& val);

private:
    QStringList set_speed_anomaly_list;
    QStringList set_anomaly_crowd_type;
    int Max_Speed_thresh;
    int Min_Speed_thresh;
    QString selected_anomaly;
    QString selected_crowd_type;
    speedmismatchnode BlobSpeedMismatchNode;
    SpeedNode blobSpeedNode;
    Configuration config;
    int mismatchCount;


};

#endif // SPEEDMISMATCHPLUGIN_H
