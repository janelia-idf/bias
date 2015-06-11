#include "bias_plugin.hpp"
#include <QtDebug>
#include <opencv2/core/core.hpp>
#include "camera_window.hpp"

namespace bias
{

    const QString BiasPlugin::PLUGIN_NAME = QString("basePlugin"); 
    const QString BiasPlugin::PLUGIN_DISPLAY_NAME = QString("Base Plugin"); 

    // Pulbic
    // ------------------------------------------------------------------------

    BiasPlugin::BiasPlugin(QWidget *parent) : QDialog(parent) 
    { 
        active_ = false;
        setRequireTimer(false);
    }

    void BiasPlugin::reset()
    { }

    void BiasPlugin::setFileAutoNamingString(QString autoNamingString)
    {
        fileAutoNamingString_ = autoNamingString;
    }

    void BiasPlugin::setFileVersionNumber(unsigned verNum)
    {
        fileVersionNumber_ = verNum;
    }

    void BiasPlugin::stop()
    { }

    void BiasPlugin::setActive(bool value)
    {
        active_ = value;
    }


    bool BiasPlugin::isActive()
    {
        return active_;
    }


    bool BiasPlugin::requireTimer()
    {
        return requireTimer_;
    }

    void BiasPlugin::processFrames(QList<StampedImage> frameList) 
    { 
        acquireLock();
        StampedImage latestFrame = frameList.back();
        frameList.clear();
        currentImage_ = latestFrame.image;
        timeStamp_ = latestFrame.timeStamp;
        frameCount_ = latestFrame.frameCount;
        releaseLock();
    } 


    cv::Mat BiasPlugin::getCurrentImage()
    {
        acquireLock();
        cv::Mat currentImageCopy = currentImage_.clone();
        releaseLock();
        return currentImageCopy;
    }


    QString BiasPlugin::getName()
    {
        return PLUGIN_NAME;
    }


    QString BiasPlugin::getDisplayName()
    {
        return PLUGIN_DISPLAY_NAME;
    }


    QPointer<CameraWindow> BiasPlugin::getCameraWindow()
    {
        QPointer<CameraWindow> cameraWindowPtr = (CameraWindow*)(parent());
        return cameraWindowPtr;
    }


    RtnStatus BiasPlugin::runCmdFromMap(QVariantMap cmdMap, bool showErrorDlg)
    {
        qDebug() << __PRETTY_FUNCTION__;
        RtnStatus rtnStatus;
        return rtnStatus;
    }

    QVariantMap BiasPlugin::getConfigAsMap()  
    {
        QVariantMap configMap;
        return configMap;
    }

    RtnStatus BiasPlugin::setConfigFromMap(QVariantMap configMap)
    {
        RtnStatus rtnStatus;
        rtnStatus.success = true;
        rtnStatus.message = QString("");
        return rtnStatus;
    }

    RtnStatus BiasPlugin::setConfigFromJson(QByteArray jsonArray)
    {
        RtnStatus rtnStatus;
        rtnStatus.success = true;
        rtnStatus.message = QString("");
        return rtnStatus;
    }

    bool BiasPlugin::pluginsEnabled()
    {
        return getCameraWindow() -> isPluginEnabled();
    }


    void BiasPlugin::setPluginsEnabled(bool value)
    {
        getCameraWindow() -> setPluginEnabled(value);
    }


    // Protected methods
    // ------------------------------------------------------------------------
    void BiasPlugin::setRequireTimer(bool value)
    {
        requireTimer_ = value;
    }

}
