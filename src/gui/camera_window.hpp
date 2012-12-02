#ifndef BIAS_GUI_CAMERA_WINDOW_HPP
#define BIAS_GUI_CAMERA_WINDOW_HPP

#include <memory>
#include <QDir>
#include <QSize>
#include <QMap>
#include <QPointer>
#include <QMainWindow>
#include "ui_camera_window.h"
#include "camera_facade_fwd.hpp"


// External lib forward declarations
class QTimer;
class QThreadPool;
class QSignalMapper;

namespace cv   { class Mat; }

namespace bias 
{
    // BIAS forward declarations
    class ImageGrabber;
    class ImageDispatcher;
    struct StampedImage;
    template <class T> class Lockable;
    template <class T> class LockableQueue;



    class CameraWindow : public QMainWindow, private Ui::CameraWindow
    {
        Q_OBJECT

        const double DEFAULT_IMAGE_DISPLAY_FREQ = 15.0; // Hz 
        const QSize PREVIEW_DUMMY_IMAGE_SIZE = QSize(320,256);
        const QSize DEFAULT_HISTOGRAM_IMAGE_SIZE = QSize(256,204);
        enum ImageRotationType
        { 
            IMAGE_ROTATION_0=0,
            IMAGE_ROTATION_90=90,
            IMAGE_ROTATION_180=180,
            IMAGE_ROTATION_270=270
        };

        public:

            CameraWindow(Guid cameraGuid, QWidget *parent=0);

        protected:

            void resizeEvent(QResizeEvent *event);
            void closeEvent(QCloseEvent *event);
            void showEvent(QShowEvent *event);

        private slots:
           
            // Button callbacks
            void connectButtonClicked();
            void startButtonClicked();
            void startImageCaptureError(unsigned int errorId, QString errorMsg);
            void stopImageCaptureError(unsigned int errorId, QString errorMsg);

            // Display Timer update
            void updateImageDisplay();

            // Tab changed event
            void tabWidgetChanged(int index);

            // Menu actions
            void actionFileLoadConfigTriggered();
            void actionFileSaveconfigTriggered();
            void actionFileCloseWindowTriggered();
            void actionFileHideWindowTriggered();
            void actionCameraInfoTriggered();
            void actionCameraFormat7SettingsTriggered();
            void actionLoggingEnabledTriggered();
            void actionLoggingVideoFileTriggered();
            void actionLoggingSettingsTriggered();
            void actionLoggingFormatTriggered();
            void actionTimerEnabledTriggered();
            void actionTimerSettingsTriggered();
            void actionDisplayUpdateFreqTriggered();
            void actionDisplayFlipVertTriggered();
            void actionDisplayFlipHorzTriggered();
            void actionDisplayRotTriggered();
            void actionHelpUserManualTriggered();
            void actionHelpAboutTriggered();
            void actionPluginsSettingsTriggered();

            // Signal mappers for videomode, framerate and properties
            void actionVideoModeTriggered(int vidModeInt);
            void actionFrameRateTriggered(int frmRateInt);
            void actionPropertyTriggered(int propTypeInt);

        private:

            bool connected_;
            bool capturing_;
            bool logging_;
            bool timer_;
            bool flipVert_;
            bool flipHorz_;
            QDir defaultSaveDir_;
            double imageDisplayFreq_;
            ImageRotationType imageRotation_;
            unsigned long frameCount_;

            QPixmap previewPixmapOriginal_;
            QPixmap pluginPixmapOriginal_;
            QPixmap histogramPixmapOriginal_;

            QPointer<QActionGroup> videoModeActionGroupPtr_; 
            QPointer<QActionGroup> frameRateActionGroupPtr_; 
            QPointer<QActionGroup> cameraTriggerActionGroupPtr_;
            QPointer<QActionGroup> loggingFormatActionGroupPtr_;
            QPointer<QActionGroup> rotationActionGroupPtr_;

            QPointer<QSignalMapper> videoModeSignalMapperPtr_;
            QPointer<QSignalMapper> frameRateSignalMapperPtr_;
            QPointer<QSignalMapper> propertiesSignalMapperPtr_;

            QMap<QAction*, ImageRotationType> actionToRotationMap_;

            std::shared_ptr<Lockable<Camera>> cameraPtr_;
            std::shared_ptr<LockableQueue<StampedImage>> newImageQueuePtr_;

            QPointer<QThreadPool> threadPoolPtr_;
            QPointer<QTimer> imageDisplayTimerPtr_;

            QPointer<ImageGrabber> imageGrabberPtr_;
            QPointer<ImageDispatcher> imageDispatcherPtr_;

            void connectWidgets();
            void initialize(Guid guid);

            void connectCamera();
            void disconnectCamera();

            void startImageCapture();
            void stopImageCapture();

            void setDefaultSaveDir();
            void setupImageDisplayTimer();
            
            // Menu setup methods
            void setupCameraMenu();
            void setupLoggingMenu();
            void setupDisplayMenu();
            void setupDisplayOrientMenu();
            void setupDisplayRotMenu();

            // Menu update methods
            void updateCameraMenu();
            void populateVideoModeMenu();
            void populateFrameRateMenu();
            void populatePropertiesMenu();
            void updateCameraVideoModeMenu();
            void updateCameraFrameRateMenu();
            void updateCameraPropertiesMenu();
            void updateCameraTriggerMenu();
            void updateLoggingMenu();
            void updateTimerMenu();
           
            void updatePreviewImageLabel();
            void updateCameraInfoMessage();

            void setupImageLabels();
            void updateImageLabel(
                    QLabel *imageLabelPtr, 
                    QPixmap &pixmapOriginal, 
                    bool flipAndRotate=true,
                    bool addFrameCount=true
                    );
            void resizeImageLabel(
                    QLabel *imageLabelPtr, 
                    QPixmap &pixmapOriginal, 
                    bool flipAndRotate=true,
                    bool addFrameCount=true
                    );
            void resizeAllImageLabels();

            void updateHistogramPixmap(cv::Mat hist);

            void deleteMenuActions(QMenu *menuPtr, QActionGroup *actionGroupPtr=NULL);
            void setCameraInfoMessage(QString vendorName, QString modelName);
            void setMenuChildrenEnabled(QWidget *parentWidgetPtr, bool value);
            void setCaptureTimeLabel(double timeStamp);

            // Development
            cv::Mat calcHistogram(cv::Mat mat);


    }; // class CameraWindow


    // Utilitiy functions
    QString boolToOnOffQString(bool value);
    QString timeStampToQString(double timeStamp);

}

#endif // #ifndef BIAS_GUI_CAMERA_WINDOW_HPP
