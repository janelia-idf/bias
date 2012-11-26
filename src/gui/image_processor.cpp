#include "image_processor.hpp"
#include <iostream>

ImageProcessor::ImageProcessor()
{
    ready_ = false;
    stopped_ = true;
}

ImageProcessor::ImageProcessor(bias::ImagePoolPtr imagePoolPtr)
{
    imagePoolPtr_ = imagePoolPtr;
    ready_ = true;
    stopped_ = true;
}

bool ImageProcessor::tryDisplayImageLock()
{
    return displayImageMutex_.tryLock();
}

void ImageProcessor::acquireDisplayImageLock() 
{
    displayImageMutex_.lock();
}

void ImageProcessor::releaseDisplayImageLock()
{
    displayImageMutex_.unlock();
}

cv::Mat ImageProcessor::getDisplayImage()
{
    return displayImage_;
}

void ImageProcessor::stop()
{
    stopped_ = true;
}


void ImageProcessor::run()
{
    cv::Mat newImage;
    cv::Mat tmpImage;

    bool haveNewImage = false;

    stopped_ = false;

    while (!stopped_) 
    {
        // Get new image from image pool
        imagePoolPtr_ -> acquireNewImageLock();
        if (imagePoolPtr_ -> numberOfNewImages() > 0)
        {
            newImage = imagePoolPtr_ -> dequeueNewImage();
            haveNewImage = true;
        }
        imagePoolPtr_ -> releaseNewImageLock();

        // Place old image onto image pool
        if (haveNewImage) 
        {
            std::cout << "image processor -> new image" << std::endl << std::flush;
            if (tryDisplayImageLock())
            {
                // Swap new image and display image
                //std::cout << "swapping" << std::endl << std::flush;
                tmpImage = displayImage_;
                displayImage_ = newImage;
                newImage = tmpImage;
                releaseDisplayImageLock();
            }

            imagePoolPtr_ -> acquireOldImageLock();
            imagePoolPtr_ -> enqueueOldImage(newImage);
            imagePoolPtr_ -> releaseOldImageLock();
            haveNewImage = false;
        }
    }
}


