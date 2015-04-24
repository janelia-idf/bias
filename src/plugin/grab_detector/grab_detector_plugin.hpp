#ifndef GRAB_DETECTOR_PLUGIN_HPP
#define GRAB_DETECTOR_PLUGIN_HPP
#include "ui_grab_detector_plugin.h"
#include "bias_plugin.hpp"
#include "pulse_device.hpp"
#include <QPointer>
#include <QVector>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>

class QTimer;

namespace cv
{
    class Mat;
}

namespace bias
{

    class ImageLabel;


    class GrabDetectorPlugin : public BiasPlugin, public Ui::GrabDetectorPluginDialog
    {
        Q_OBJECT

        public:

            static const QString PLUGIN_NAME;
            static const QString PLUGIN_DISPLAY_NAME;
            static int DEFAULT_XPOS;
            static int DEFAULT_YPOS;
            static int DEFAULT_WIDTH;
            static int DEFAULT_HEIGHT;
            static int DEFAULT_TRIGGER_ARMED;
            static int DEFAULT_TRIGGER_THRESHOLD;
            static int DEFAULT_TRIGGER_FILTER_SIZE;
            static int DEFAULT_LIVEPLOT_UPDATE_DT;
            static double DEFAULT_LIVEPLOT_TIME_WINDOW; 
            static double DEFAULT_LIVEPLOT_SIGNAL_WINDOW;
            static QColor DEFAULT_DETECTION_BOX_COLOR;

            GrabDetectorPlugin(ImageLabel *imageLabelPtr, QWidget *parentPtr=0);

            virtual void processFrames(QList<StampedImage> frameList);
            virtual cv::Mat getCurrentImage();

            virtual QString getName();
            virtual QString getDisplayName();
            
            virtual RtnStatus runCmdFromMap(QVariantMap cmdMap, bool showErrorDlg=true);

            void setTriggerEnabled(bool value);
            void resetTrigger();

        signals:

            void triggerFired();

        protected:

            bool found_;
            bool triggerArmed_;
            bool triggerEnabled_;
            double signalMax_;
            double signalMin_;
            unsigned long frameCount_;
            QColor detectionBoxColor_;

            int livePlotUpdateDt_;
            double livePlotTimeWindow_; 
            double livePlotSignalWindow_;
            QVector<double> livePlotTimeVec_;
            QVector<double> livePlotSignalVec_;
            QPointer<QTimer> livePlotUpdateTimerPtr_;
            QPointer<ImageLabel> imageLabelPtr_;

            QList<QSerialPortInfo> serialInfoList_;
            PulseDevice pulseDevice_;

            void connectWidgets();
            void initialize();

            cv::Rect getDetectionBoxCv();
            QRect getDetectionBox();
            void setDetectionBox(QRect box);
            bool isDetectionBoxLocked();

            int getThreshold();
            int getMedianFilter();

            void updateTrigStateInfo();
            void refreshPortList();

            void updateColorExampleLabel();


        private slots:

            void comPortComboBoxIndexChanged(QString text);
            void connectPushButtonClicked();
            void refreshPortListPushButtonClicked();
            void outputTestPushButtonClicked();
            void durationDblSpinBoxValueChanged(double value);
            void colorSelectPushButtonClicked();
            void trigResetPushButtonClicked();
            void trigEnabledCheckBoxStateChanged(int state);
            void detectionBoxChanged(QRect boxRect);
            void updateLivePlotOnTimer();
            void onTriggerFired();

    };
}
#endif
