cmake_minimum_required (VERSION 2.6)

include_directories (${ANTCONFAPP_SOURCE_DIR}/libPermutate)

# Make sure the linker can find the Hello library once it is built.
link_directories (${ANTCONFAPP_BINARY_DIR}/libPermutate)

set(test_SRCS AntennaConfiguration.cpp)
add_executable( AntConfApp ${test_SRCS})

target_link_libraries (AntConfApp Permutate)




