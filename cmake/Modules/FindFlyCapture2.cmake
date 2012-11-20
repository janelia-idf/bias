# - Try to find FlyCapture2 
# 
# Once done this will define
#
#  FlyCapture2_FOUND         - System has LibXml2
#  FlyCapture2_INCLUDE_DIRS  - The LibXml2 include directories
#  FlyCapture22_LIBRARIES    - The libraries needed to use LibXml2
#
# ------------------------------------------------------------------------------

set(typical_fc2_dir "C:/Program Files/Point Grey Research/FlyCapture2")
set(typical_fc2_lib_dir "${typical_fc2_dir}/lib64/C")
set(typical_fc2_inc_dir "${typical_fc2_dir}/include/C")

if(WIN32)
    # -------------------------------------------------------------------------
    # TO DO
    # 
    # I think this pretty fragile ... what if user puts flycapure in
    # different location
    # -------------------------------------------------------------------------
    message(STATUS "finding include dir")
    find_path(
        FlyCapture2_INCLUDE_DIR 
        "FlyCapture2_C.h"
        HINTS ${typical_fc2_inc_dir}
        )
    message(STATUS "FlyCapture2_INCLUDE_DIR: " ${FlyCapture2_INCLUDE_DIR})
else()
    # -------------------------------------------------------------------------
    # TO DO
    # 
    # linux, macos, etc not implemented yet
    # -------------------------------------------------------------------------
    message(FATAL_ERROR "FlyCapture2 currently only supported on WIN32")
endif()

if(WIN32)
    # -------------------------------------------------------------------------
    # TO DO
    # 
    # I think this pretty fragile ... what if user puts flycapure in
    # different location
    # -------------------------------------------------------------------------
    message(STATUS "finding library")
    find_library(
        FlyCapture2_LIBRARY 
        NAMES "FlyCapture2_C.lib"
        HINTS ${typical_fc2_lib_dir} 
        )
else() 
    # -------------------------------------------------------------------------
    # TO DO
    # 
    # linux, macos, etc not implemented yet
    # -------------------------------------------------------------------------
    message(FATAL_ERROR "FlyCapture2 currently only supported on WIN32")
endif()


set(FlyCapture2_LIBRARIES ${FlyCapture2_LIBRARY} )
set(FlyCapture2_INCLUDE_DIRS ${FlyCapture2_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
    FlyCapture2  DEFAULT_MSG
    FlyCapture2_LIBRARY 
    FlyCapture2_INCLUDE_DIR
    )

mark_as_advanced(FlyCapture2_INCLUDE_DIR FlyCapture2_LIBRARY )

