#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <set>
#include <list>
#include <memory>
#include <iostream>
#include "guid.hpp"
#include "basic_types.hpp"
#include "camera_device.hpp"

namespace bias {

    class Camera {

        // --------------------------------------------------------------------
        // Facade wrapper for cameras. Provides a unified interface for cameras 
        // which are accessed via different underlying libraries e.g. libdc1394, 
        // flycapture2, etc.
        // --------------------------------------------------------------------
       
        friend std::ostream& operator<< (std::ostream &out, Camera &camera);

        public:
            Camera();
            Camera(Guid guid);
            ~Camera();
            void printInfo();
            void printGuid();
            CameraLib getCameraLib();
            Guid getGuid();

            void connect();
            void disconnect();      

            void startCapture(); 
            void stopCapture();
            void grabImage();

        private:
            CameraDevicePtr cameraDevicePtr_;
            void createCameraDevice_fc2(Guid guid);
            void createCameraDevice_dc1394(Guid guid);

    };

    typedef std::shared_ptr<Camera> CameraPtr;

    class CameraPtrCmp : public std::binary_function<CameraPtr, CameraPtr, bool>
    {
        // Comparison object for shared_ptrs to Guid objects  
        public:
            bool operator() (const CameraPtr &camPtr0, const CameraPtr &camPtr1);
    };

    typedef std::set<CameraPtr> CameraPtrSet;
    typedef std::list<CameraPtr> CameraPtrList;
}


#endif
