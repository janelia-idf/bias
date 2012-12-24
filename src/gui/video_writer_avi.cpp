#include "video_writer_avi.hpp"
#include "basic_types.hpp"
#include "exception.hpp"
#include <QFileInfo>
#include <QDir>
#include <iostream>

namespace bias
{ 
    const QString DUMMY_FILENAME("dummy.avi");

    const double VideoWriter_avi::DEFAULT_FPS = 30.0;
    const unsigned int VideoWriter_avi::DEFAULT_FRAME_SKIP = 4;
    const int VideoWriter_avi::DEFAULT_FOURCC = CV_FOURCC('D','I','V','X');

    VideoWriter_avi::VideoWriter_avi(QObject *parent) 
        : VideoWriter_avi(DUMMY_FILENAME,parent) 
    {}

    VideoWriter_avi::VideoWriter_avi(QString fileName, QObject *parent) 
        : VideoWriter(fileName,parent)
    {
        fourcc_ = DEFAULT_FOURCC;
        fps_ = DEFAULT_FPS;
        isFirst_ = true;
        setFrameSkip(DEFAULT_FRAME_SKIP);
    }

    VideoWriter_avi::~VideoWriter_avi() {};

    void VideoWriter_avi::addFrame(StampedImage stampedImg)
    {
        if (isFirst_)
        {
            setupOutput(stampedImg);
            isFirst_ = false;
        }
        if (frameCount_%frameSkip_==0)
        {
            videoWriter_ << stampedImg.image;
        }
        frameCount_++;
    }

    void VideoWriter_avi::setupOutput(StampedImage stampedImg)
    {
        std::string incrFileName = getUniqueFileName().toStdString();
        
        setSize(stampedImg.image.size());

        try
        {
            videoWriter_.open(incrFileName,fourcc_,fps_,size_,false);
        }
        catch (cv::Exception &e)
        {
            unsigned int errorId = ERROR_VIDEO_WRITER_INITIALIZE;
            std::string errorMsg("video writer unable to open file:\n\n"); 
            errorMsg += e.what();
            throw RuntimeError(errorId, errorMsg); 
        }

        if (!videoWriter_.isOpened())
        {
            unsigned int errorId = ERROR_VIDEO_WRITER_INITIALIZE;
            std::string errorMsg("video writer unable to open file:\n\n"); 
            errorMsg += "no exception thrown, but file not opened??";
            throw RuntimeError(errorId, errorMsg); 
        }
    }

} // namespace bias
