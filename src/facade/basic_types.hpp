#ifndef BIAS_BASIC_TYPES_HPP
#define BIAS_BASIC_TYPES_HPP

#include <set>
#include <list>

namespace bias {

    enum CameraLib 
    {
        CAMERA_LIB_FC2=0,
        CAMERA_LIB_DC1394,
        CAMERA_LIB_UNDEFINED,
        NUMBER_OF_CAMERA_LIB,
    };

    typedef std::list<CameraLib> CameraLibList;
    typedef std::set<CameraLib> CameraLibSet;

    enum ErrorCode 
    {

        ERROR_OK = 0,

        // Camera library errors
        ERROR_CAMERA_LIB_UNKNOWN,
        ERROR_CAMERA_LIB_UNDEFINED,

        // 
        ERROR_INVALID_FRAMERATE,
        ERROR_NO_FRAMERATE_FOR_VIDEOMODE,

        // FlyCapture2 specific errors
        ERROR_NO_FC2,
        ERROR_FC2_CREATE_CONTEXT,
        ERROR_FC2_DESTROY_CONTEXT,
        ERROR_FC2_CONNECT,
        ERROR_FC2_DISCONNECT,
        ERROR_FC2_START_CAPTURE,
        ERROR_FC2_STOP_CAPTURE,
        ERROR_FC2_RETRIEVE_BUFFER,
        ERROR_FC2_GRAB_IMAGE,
        ERROR_FC2_CREATE_IMAGE,
        ERROR_FC2_DESTROY_IMAGE,
        ERROR_FC2_GET_GUID,
        ERROR_FC2_ENUMERATE_CAMERAS,
        ERROR_FC2_GET_CAMERA_FROM_INDEX,
        ERROR_FC2_GET_VIDEOMODE_FRAMERATE_INFO,
        ERROR_FC2_CONVERT_IMAGE,
        ERROR_FC2_GET_FORMAT7_INFO,
        ERROR_FC2_GET_FORMAT7_CONFIGURATION,
        ERROR_FC2_GET_VIDEOMODE_AND_FRAMERATE,
        ERROR_FC2_UNSUPPORTED_VIDEO_MODE,
        ERROR_FC2_VALIDATE_FORMAT7_SETTINGS,
        ERROR_FC2_INVALID_FORMAT7_SETTINGS,
        ERROR_FC2_SET_FORMAT7_CONFIGURATION,
        ERROR_FC2_GET_DEFAULT_OUTPUT_FORMAT,
        ERROR_FC2_GET_CAMERA_INFO,
        ERROR_FC2_GET_PROPERTY_INFO,
        ERROR_FC2_GET_PROPERTY,
        ERROR_FC2_SET_PROPERTY,
        ERROR_FC2_SET_VIDEOMODE_AND_FRAMERATE,
        ERROR_FC2_SET_VIDEOMODE_FORMAT7,
        ERROR_FC2_GET_TRIGGER_MODE,
        ERROR_FC2_GET_TRIGGER_MODE_INFO,
        ERROR_FC2_SET_TRIGGER_MODE,
        ERROR_FC2_GET_EMBEDDED_IMAGE_INFO,
        ERROR_FC2_SET_EMBEDDED_IMAGE_INFO,
        ERROR_FC2_NO_SUPPORTED_PIXEL_FORMAT,
        ERROR_FC2_NO_COMPATIBLE_OPENCV_FORMAT,
        ERROR_FC2_GET_CONFIG,
        ERROR_FC2_SET_CONFIG,
        ERROR_FC2_GET_STROBE_CONTROL,   
        ERROR_FC2_SET_STROBE_CONTROL,
        ERROR_FC2_GET_STROBE_INFO,

        ERROR_FC2_CONVERT_PROPERTY_TYPE,
        ERROR_FC2_CONVERT_FRAMERATE,
        ERROR_FC2_CONVERT_VIDEOMODE,
        ERROR_FC2_CONVERT_IMAGEMODE,
        ERROR_FC2_CONVERT_PIXEL_FORMAT,

        // Libdc1394 specific errors
        ERROR_NO_DC1394,
        ERROR_DC1394_CREATE_CONTEXT,
        ERROR_DC1394_NULL_POINTER,
        ERROR_DC1394_ENUMERATE_CAMERAS,
        ERROR_DC1394_NEW_CAMERA,
        ERROR_DC1394_IS_COLOR,
        ERROR_DC1394_CAPTURE_SETUP,
        ERROR_DC1394_CAPTURE_DEQUEUE,
        ERROR_DC1394_START_CAPTURE,
        ERROR_DC1394_GRAB_IMAGE,
        ERROR_DC1394_CONVERT_PIXEL_FORMAT,

        ERROR_DC1394_SET_VIDEO_TRANSMISSION,
        ERROR_DC1394_SET_VIDEO_MODE,
        ERROR_DC1394_SET_FEATURE, 

        ERROR_DC1394_CONVERT_PROPERTY_TYPE,
        ERROR_DC1394_CONVERT_VIDEOMODE,
        ERROR_DC1394_CONVERT_FRAMERATE,
        ERROR_DC1394_GET_VIDEOMODE,
        ERROR_DC1394_GET_FRAMERATE,
        ERROR_DC1394_GET_SUPPORTED_VIDEOMODES,
        ERROR_DC1394_GET_SUPPORTED_FRAMERATES,
        ERROR_DC1394_GET_COLOR_CODING_FROM_VIDEOMODE,
        ERROR_DC1394_GET_FEATURE_INFO,
        ERROR_DC1394_GET_IMAGE_POSITION,
        ERROR_DC1394_GET_IMAGE_SIZE,
        ERROR_DC1394_GET_FORMAT7_SETTINGS,
        ERROR_DC1394_GET_COLOR_CODING,

        // Video Writer Errors
        ERROR_VIDEO_WRITER_ADD_FRAME,
        ERROR_VIDEO_WRITER_INITIALIZE,
        ERROR_VIDEO_WRITER_FINISH,

        // Image Logger Errors
        ERROR_IMAGE_LOGGER_MAX_QUEUE_SIZE,
        ERROR_FRAMES_TODO_MAX_QUEUE_SIZE,
        ERROR_FRAMES_FINISHED_MAX_SET_SIZE,

        // Capture Errors
        ERROR_CAPTURE_MAX_ERROR_COUNT,
        
        NUMBER_OF_ERROR,
    }; 

    typedef std::list<ErrorCode> ErrorCodeList;
    typedef std::set<ErrorCode> ErrorCodeSet;

    enum PropertyType 
    { 
        PROPERTY_TYPE_BRIGHTNESS=0, 
        PROPERTY_TYPE_AUTO_EXPOSURE,
        PROPERTY_TYPE_SHARPNESS,
        PROPERTY_TYPE_WHITE_BALANCE,
        PROPERTY_TYPE_HUE,
        PROPERTY_TYPE_SATURATION,
        PROPERTY_TYPE_GAMMA,
        PROPERTY_TYPE_IRIS,
        PROPERTY_TYPE_FOCUS,
        PROPERTY_TYPE_ZOOM,
        PROPERTY_TYPE_PAN,
        PROPERTY_TYPE_TILT,
        PROPERTY_TYPE_SHUTTER,
        PROPERTY_TYPE_GAIN,
        PROPERTY_TYPE_TRIGGER_MODE,
        PROPERTY_TYPE_TRIGGER_DELAY,
        PROPERTY_TYPE_FRAME_RATE,
        PROPERTY_TYPE_TEMPERATURE,

        NUMBER_OF_PROPERTY_TYPE,
        PROPERTY_TYPE_UNSPECIFIED,
    };

    typedef std::list<PropertyType> PropertyTypeList;
    typedef std::set<PropertyType> PropertyTypeSet;

    enum FrameRate
    {
        FRAMERATE_1_875=0, 
        FRAMERATE_3_75, 
        FRAMERATE_7_5, 
        FRAMERATE_15, 
        FRAMERATE_30, 
        FRAMERATE_60, 
        FRAMERATE_120, 
        FRAMERATE_240, 
        FRAMERATE_FORMAT7, 

        NUMBER_OF_FRAMERATE,
        FRAMERATE_UNSPECIFIED,
    };

    typedef std::list<FrameRate> FrameRateList;
    typedef std::set<FrameRate> FrameRateSet;

    enum VideoMode 
    {
        VIDEOMODE_160x120YUV444=0, 
        VIDEOMODE_320x240YUV422, 
        VIDEOMODE_640x480YUV411, 
        VIDEOMODE_640x480YUV422, 
        VIDEOMODE_640x480RGB, 
        VIDEOMODE_640x480Y8, 
        VIDEOMODE_640x480Y16, 
        VIDEOMODE_800x600YUV422, 
        VIDEOMODE_800x600RGB, 
        VIDEOMODE_800x600Y8, 
        VIDEOMODE_800x600Y16, 
        VIDEOMODE_1024x768YUV422, 
        VIDEOMODE_1024x768RGB, 
        VIDEOMODE_1024x768Y8, 
        VIDEOMODE_1024x768Y16, 
        VIDEOMODE_1280x960YUV422, 
        VIDEOMODE_1280x960RGB, 
        VIDEOMODE_1280x960Y8, 
        VIDEOMODE_1280x960Y16, 
        VIDEOMODE_1600x1200YUV422, 
        VIDEOMODE_1600x1200RGB, 
        VIDEOMODE_1600x1200Y8, 
        VIDEOMODE_1600x1200Y16, 
        VIDEOMODE_FORMAT7, 
        NUMBER_OF_VIDEOMODE,
        VIDEOMODE_UNSPECIFIED,
    };

    typedef std::list<VideoMode> VideoModeList;
    typedef std::set<VideoMode> VideoModeSet;

    enum ImageMode 
    {
        IMAGEMODE_0=0,
        IMAGEMODE_1,
        IMAGEMODE_2,
        IMAGEMODE_3,
        IMAGEMODE_4,
        IMAGEMODE_5,
        IMAGEMODE_6,
        IMAGEMODE_7,
        IMAGEMODE_8,
        IMAGEMODE_9,
        IMAGEMODE_10,
        IMAGEMODE_11,
        IMAGEMODE_12,
        IMAGEMODE_13,
        IMAGEMODE_14,
        IMAGEMODE_15,
        IMAGEMODE_16,
        IMAGEMODE_17,
        IMAGEMODE_18,
        IMAGEMODE_19,
        IMAGEMODE_20,
        IMAGEMODE_21,
        IMAGEMODE_22,
        IMAGEMODE_23,
        IMAGEMODE_24,
        IMAGEMODE_25,
        IMAGEMODE_26,
        IMAGEMODE_27,
        IMAGEMODE_28,
        IMAGEMODE_29,
        IMAGEMODE_30,
        IMAGEMODE_31,
        NUMBER_OF_IMAGEMODE, 
        IMAGEMODE_UNSPECIFIED,
    };  

    typedef std::list<ImageMode> ImageModeList;
    typedef std::set<ImageMode> ImageModeSet;

    enum PixelFormat
    {
        PIXEL_FORMAT_MONO8,
        PIXEL_FORMAT_411YUV8,
        PIXEL_FORMAT_422YUV8,
        PIXEL_FORMAT_444YUV8,
        PIXEL_FORMAT_RGB8,
        PIXEL_FORMAT_MONO16,
        PIXEL_FORMAT_RGB16,
        PIXEL_FORMAT_S_MONO16,
        PIXEL_FORMAT_S_RGB16,
        PIXEL_FORMAT_RAW8,
        PIXEL_FORMAT_RAW16,
        PIXEL_FORMAT_MONO12,
        PIXEL_FORMAT_RAW12,
        PIXEL_FORMAT_BGR8,
        PIXEL_FORMAT_BGRU,
        PIXEL_FORMAT_RGBU,
        PIXEL_FORMAT_BGR16,
	    PIXEL_FORMAT_BGRU16,
        PIXEL_FORMAT_422YUV8_JPEG,
        NUMBER_OF_PIXEL_FORMAT,
        PIXEL_FORMAT_UNSPECIFIED,
    };

    typedef std::list<PixelFormat> PixelFormatList;
    typedef std::set<PixelFormat> PixleFormatSet;

    enum TriggerType
    {
        TRIGGER_INTERNAL,
        TRIGGER_EXTERNAL,
        NUMBER_OF_TRIGGER_TYPE,
        TRIGGER_TYPE_UNSPECIFIED,
    };

    typedef std::list<TriggerType> TriggerTypeList;
    typedef std::set<TriggerType> TriggerTypeSet;

    enum VideoFileFormat
    {
        VIDEOFILE_FORMAT_BMP,
        VIDEOFILE_FORMAT_AVI,
        VIDEOFILE_FORMAT_FMF,
        VIDEOFILE_FORMAT_UFMF,
        NUMBER_OF_VIDEOFILE_FORMAT,
        VIDEOFILE_FORMAT_UNSPECIFIED,
    };

    enum ImageRotationType
    { 
        IMAGE_ROTATION_0=0,
        IMAGE_ROTATION_90=90,
        IMAGE_ROTATION_180=180,
        IMAGE_ROTATION_270=270,
        NUMBER_OF_IMAGE_ROTATION,
        IMAGE_ROTATION_UNSPECIFIED,
    };

    struct ImageInfo 
    {
        unsigned int rows;
        unsigned int cols;
        unsigned int stride;
        unsigned int dataSize;
        PixelFormat pixelFormat;
    };

    struct TimeStamp
    {
        unsigned long long seconds;
        unsigned int microSeconds;
    };

} // namespace bias

#endif // #ifndef BIAS_BASIC_TYPES_HPP
