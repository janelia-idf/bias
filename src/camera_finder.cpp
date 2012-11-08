#include "camera_finder.hpp"
#include "exception.hpp"
#include <iostream>
#include <sstream>

namespace bias {

    CameraFinder::CameraFinder() 
    {
        createQueryContext_fc2();
        createQueryContext_dc1394();
    };

    CameraFinder::~CameraFinder() 
    {
        destroyQueryContext_fc2();
        destroyQueryContext_dc1394();
    };

    void CameraFinder::update() 
    {
        guidPtrSet_.clear();
        update_fc2();
        update_dc1394();
    }

    void CameraFinder::printGuid() 
    {
        std::cout << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << " CameraFinder Guid List" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << std::endl;
        std::cout << getGuidListAsString();
    }

    std::string CameraFinder::getGuidListAsString()
    {
        int count;
        std::stringstream ss;
        GuidPtrSet::iterator it;

        for (it=guidPtrSet_.begin(), count=0; it!=guidPtrSet_.end(); it++, count++) 
        {
            ss << "[" << count << "] " << **it << std::endl;
        }
        ss << std::endl;
        return ss.str();
    }

    unsigned int CameraFinder::numberOfCameras() 
    {
        return guidPtrSet_.size();
    }

    Guid CameraFinder::getGuidByIndex(unsigned int index)
    {
        if (index >= guidPtrSet_.size()) {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": unable to get FlyCapture2 guid by index";
            throw RuntimeError(ERROR_FC2_GET_GUID, ssError.str());
        }
        GuidPtrSet::iterator it = guidPtrSet_.begin();
        std::advance(it,index);
        return **it;
    }

    GuidPtrSet CameraFinder::getGuidPtrSet()
    {
        return guidPtrSet_;
    }

    GuidPtrList CameraFinder::getGuidPtrList()
    {
        GuidPtrList guidPtrList;
        std::copy(
                guidPtrSet_.begin(), 
                guidPtrSet_.end(), 
                std::back_inserter(guidPtrList)
                ); 
        return guidPtrList;
    }

#ifdef WITH_FC2

    // FlyCapture2 specific features
    // ------------------------------------------------------------------------
    void CameraFinder::createQueryContext_fc2()
    {
        fc2Error error = fc2CreateContext(&queryContext_fc2_);
        if (error != FC2_ERROR_OK) 
        {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": unable to create FlyCapture2 context";
            throw RuntimeError(ERROR_FC2_CREATE_CONTEXT, ssError.str());
        }
    }

    void CameraFinder::destroyQueryContext_fc2()
    {
        fc2Error error = fc2DestroyContext(queryContext_fc2_);
        if (error != FC2_ERROR_OK) 
        {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": unable to destroy FlyCapture2 context";
            throw RuntimeError(ERROR_FC2_DESTROY_CONTEXT, ssError.str());
        }
    }

    void CameraFinder::update_fc2()
    {
        fc2Error error;
        fc2PGRGuid guid_fc2;
        unsigned int numCameras = 0;

        // Get number of attached cameras.
        error = fc2GetNumOfCameras(queryContext_fc2_, &numCameras);
        if (error != FC2_ERROR_OK) 
        {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": unable to enumerate FlyCapture2 cameras";
            throw RuntimeError(ERROR_FC2_ENUMERATE_CAMERAS, ssError.str());
        }

        // Get attached camera guids - add to guid set 
        for (int i=0; i<numCameras; i++) 
        {
            error = fc2GetCameraFromIndex(queryContext_fc2_, i, &guid_fc2);
            if (error != FC2_ERROR_OK) 
            {
                std::stringstream ssError;
                ssError << __PRETTY_FUNCTION__;
                ssError << ": unable to get FlyCapture2 camera guid from index";
                throw RuntimeError(ERROR_FC2_GET_CAMERA_FROM_INDEX, ssError.str());
            }
            else 
            {
                //GuidPtr guidPtr(new Guid(guid_fc2));
                GuidPtr guidPtr = std::make_shared<Guid>(guid_fc2);
                guidPtrSet_.insert(guidPtr);
            }
        }
    }

#else

    // Dummy methods for when FlyCapture2 is not included
    // ------------------------------------------------------------------------

    void CameraFinder::createQueryContext_fc2() {};
    void CameraFinder::destroyQueryContext_fc2() {};
    void CameraFinder::update_fc2() {};

#endif

#ifdef WITH_DC1394

    // Libdc1394 specific features
    // ------------------------------------------------------------------------
    void CameraFinder::createQueryContext_dc1394()
    {
        queryContext_dc1394_ = NULL;
        queryContext_dc1394_ = dc1394_new();
        if ( !queryContext_dc1394_ ) 
        {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": error creating dc1394_t" << std::endl;
            throw RuntimeError(ERROR_DC1394_CREATE_CONTEXT, ssError.str());
        }
    }

    void CameraFinder::destroyQueryContext_dc1394() 
    {
        dc1394_free(queryContext_dc1394_);
        queryContext_dc1394_ = NULL;
    }

    void CameraFinder::update_dc1394()
    {
        dc1394error_t error;
        dc1394camera_list_t *cameraList;

        if ( !queryContext_dc1394_ ) 
        {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": error updating dc1394 context is NULL" << std::endl;
            throw RuntimeError(ERROR_DC1394_NULL_POINTER, ssError.str());
        }
        
        // Get number of attached cameras
        error = dc1394_camera_enumerate(queryContext_dc1394_, &cameraList);
        if (error != DC1394_SUCCESS)  
        {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": unable to enumerate dc1394 camears, error code ";
            ssError << error  << std::endl;
            throw RuntimeError(ERROR_DC1394_ENUMERATE_CAMERAS, ssError.str());
        }

        // Add attached camera guids to the guid set.
        for (int i=0; i<(cameraList->num); i++) 
        {
            GuidPtr guidPtr = std::make_shared<Guid>(cameraList->ids[i].guid);
            guidPtrSet_.insert(guidPtr);
        }
        dc1394_camera_free_list(cameraList);
    }

#else
    // Dummy methods for when libdc1394 is not included
    // ------------------------------------------------------------------------

    void CameraFinder::createQueryContext_dc1394() {};
    void CameraFinder::destroyQueryContext_dc1394() {};
    void CameraFinder::update_dc1394() {};

#endif

} // namespace bias