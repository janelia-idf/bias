#ifndef IMAGE_GRABBER_HPP  
#define IMAGE_GRABBER_HPP

#include "camera_facade_fwd.hpp"
#include "parameters.hpp"
#include <QObject>
#include <QRunnable>
#include <QThread>
#include <memory>
#include <opencv2/core/core.hpp>

using namespace bias;

class CameraInfo
{
    public:
        QString vendor;
        QString model;
        QString guid;
        CameraInfo();
};

class ImageData
{
    public:
        cv::Mat mat;
        unsigned long frameCount;
        ImageData();
};


class ImageGrabber : public QObject, public QRunnable
{
    Q_OBJECT

    public:

        ImageGrabber(ImageGrabberParam param, QObject *parent=0);

    public slots:

        void stopCapture();

    signals:

        void cameraSetupError(QString errorMsg);
        void newCameraInfo(CameraInfo info);
        void newImage(ImageData imageData);
        void stopped();

    private:

        bool ready_;
        bool stopped_;
        bool capturing_;
        std::shared_ptr<Camera> cameraPtr_;
        ImageGrabberParam param_;

        void run();
        bool setupCamera();

};





#endif // #ifndef BIAS_IMAGE_GRABBER_HPP