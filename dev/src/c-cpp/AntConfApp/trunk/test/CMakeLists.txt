cmake_minimum_required (VERSION 2.6)

include_directories (${ANTCONFAPP_SOURCE_DIR}/libPermutate)
include_directories (${ANTCONFAPP_SOURCE_DIR}/libCalibration)
include_directories (${ANTCONFAPP_SOURCE_DIR}/libPRPSSystem)
include_directories (${ANTCONFAPP_SOURCE_DIR}/libPRPSolve)

# Make sure the linker can find the Hello library once it is built.
link_directories (${ANTCONFAPP_BINARY_DIR}/libPermutate)
link_directories (${ANTCONFAPP_BINARY_DIR}/libCalibration)
link_directories (${ANTCONFAPP_BINARY_DIR}/libPRPSSystem)
link_directories (${ANTCONFAPP_BINARY_DIR}/libSolve)

set(test_SRCS AntennaConfiguration.cpp)
set(test_LIBS Permutate Calibration PRPSEvolutionSystem Solve shark)

add_executable( AntConfApp ${test_SRCS})


target_link_libraries (AntConfApp ${test_LIBS})




