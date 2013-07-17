cmake_minimum_required (VERSION 2.6)
Project(AntConfApp)

# The version number.
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_SUB_MINOR 1)

set(VERSION_TARGET_DIR test)
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
   "${VERSION_TARGET_DIR}/AntennaConfiguration.h.in"
   "${VERSION_TARGET_DIR}/AntennaConfiguration.h"
   )

SET(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -DNDEBUG")

# the libraries
add_subdirectory(libPermutate)
add_subdirectory(libCalibration)
add_subdirectory(libPRPSSystem)
add_subdirectory(libSolve)
add_subdirectory(libNormalizer)
add_subdirectory(/usr/local/include)

add_subdirectory(test)






