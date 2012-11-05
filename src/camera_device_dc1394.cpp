#ifdef WITH_DC1394
#include "camera_device_dc1394.hpp"
#include "exception.hpp"
#include <sstream>

namespace bias {

    CameraDevice_dc1394::CameraDevice_dc1394() : CameraDevice()
    {
        context_dc1394_ = NULL;
        camera_dc1394_ = NULL;
        numDMABuffer_ = DEFAULT_NUM_DMA_BUFFER; 
    }

    CameraDevice_dc1394::CameraDevice_dc1394(Guid guid) : CameraDevice(guid)
    {
        context_dc1394_ = NULL;
        camera_dc1394_ = NULL;
        numDMABuffer_ = DEFAULT_NUM_DMA_BUFFER; 

        context_dc1394_ = dc1394_new();
        if ( !context_dc1394_ ) 
        {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": error creating dc1394_t" << std::endl;
            throw RuntimeError(ERROR_DC1394_CREATE_CONTEXT, ssError.str());
        }
    }

    CameraDevice_dc1394::~CameraDevice_dc1394()
    {
        if ( connected_ ) { disconnect(); }
        dc1394_free(context_dc1394_);
    }

    CameraLib CameraDevice_dc1394::getCameraLib()
    {
        return guid_.getCameraLib();
    }

    void CameraDevice_dc1394::connect() 
    {
        if ( !connected_ ) 
        {
            // Create new dc1394 camera object
            camera_dc1394_ = dc1394_camera_new( 
                    context_dc1394_, 
                    guid_.getValue_dc1394()
                    );
            if ( ! camera_dc1394_ ) 
            {
                std::stringstream ssError;
                ssError << __PRETTY_FUNCTION__;
                ssError << ": unable to create dc1394 camera";
                throw RuntimeError(ERROR_DC1394_NEW_CAMERA, ssError.str());
            }
            connected_ = true;
        }
    }

    void CameraDevice_dc1394::disconnect()
    {
        if ( connected_ ) 
        {
            dc1394_camera_free(camera_dc1394_);
            connected_ = false;
        }
    }

    void CameraDevice_dc1394::startCapture()
    {
        dc1394error_t error;

        if ( connected_ && !capturing_ ) {

            // Temporary - just pick a video mode which works.
            error = dc1394_video_set_mode(
                    camera_dc1394_, 
                    DC1394_VIDEO_MODE_FORMAT7_0
                    );
            if (error != DC1394_SUCCESS) 
            {
                std::stringstream ssError;
                ssError << __PRETTY_FUNCTION__;
                ssError << ": unable to set dc1394 video mode, error code ";
                ssError << error  << std::endl;
                throw RuntimeError(ERROR_DC1394_SET_VIDEO_MODE, ssError.str());
            }

            // Set number of DMA buffers and capture flags
            error = dc1394_capture_setup(
                    camera_dc1394_,
                    numDMABuffer_, 
                    DC1394_CAPTURE_FLAGS_DEFAULT
                    );
            if (error != DC1394_SUCCESS) 
            {
                std::stringstream ssError;
                ssError << __PRETTY_FUNCTION__;
                ssError << ": unable to setup dc1394 capture, error code ";
                ssError << error << std::endl;
                throw RuntimeError(ERROR_DC1394_CAPTURE_SETUP, ssError.str());
            }

            // Start video transmission
            error = dc1394_video_set_transmission(camera_dc1394_, DC1394_ON);
            if (error != DC1394_SUCCESS) 
            {
                std::stringstream ssError;
                ssError << __PRETTY_FUNCTION__;
                ssError << ": unable to turn on dc1394 video transmission, error code ";
                ssError << error << std::endl;
                throw RuntimeError(ERROR_DC1394_SET_VIDEO_TRANSMISSION, ssError.str());
            }
            capturing_ = true;
        }
    }

    void CameraDevice_dc1394::stopCapture()
    {
        if ( capturing_ ) {
            dc1394_video_set_transmission(camera_dc1394_, DC1394_OFF);
            dc1394_capture_stop(camera_dc1394_);
            capturing_ = false;
        }
    }

    void CameraDevice_dc1394::grabImage()
    {
        if ( capturing_ ) {
            dc1394error_t error;
            error = dc1394_capture_dequeue(
                    camera_dc1394_, 
                    DC1394_CAPTURE_POLICY_WAIT, 
                    &frame_dc1394_
                    );

            // Get frame  
            if (error != DC1394_SUCCESS) 
            { 
                std::stringstream ssError;
                ssError << __PRETTY_FUNCTION__;
                ssError << ": unable to dequeue dc1394 frame, error code ";
                ssError << error << std::endl;
                throw RuntimeError(ERROR_DC1394_CAPTURE_DEQUEUE, ssError.str());
            }

            // ----------------------------------------------------------------
            // TO DO ...need to copy image out of DMA buffer here
            // ----------------------------------------------------------------

            // Put frame back 
            error = dc1394_capture_enqueue(camera_dc1394_, frame_dc1394_);
        }
    }

    std::string CameraDevice_dc1394::toString()
    {
        std::stringstream ss;
        ss << std::endl;
        ss << " ------------------ " << std::endl;
        ss << " CAMERA INFORMATION " << std::endl;
        ss << " ------------------ " << std::endl;
        ss << std::endl;

        ss << " Guid:        " << guid_ << std::endl;
        ss << " Vendor Name: " << camera_dc1394_ -> vendor << std::endl;
        ss << " Vendor Id:   " << std::hex << camera_dc1394_ -> vendor_id  << std::dec << std::endl;
        ss << " Model Name:  " << std::hex << camera_dc1394_ -> model << std::dec << std::endl;
        ss << " Model Id:    " << camera_dc1394_ -> model_id << std::endl;
        ss << std::endl;
        return ss.str();
    }

    void CameraDevice_dc1394::printGuid()
    {
        guid_.printValue();
    }

    void CameraDevice_dc1394::printInfo()
    {
        std::cout << toString();
    }

} // namespace bias

#endif  // #ifdef WITH_DC1394
