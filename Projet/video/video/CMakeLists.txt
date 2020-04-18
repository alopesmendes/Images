cmake_minimum_required(VERSION 2.8)

# give a name to the project
project(video)

# find opencv
find_package(OpenCV REQUIRED)

# check opencv version
if(${OpenCV_VERSION} VERSION_LESS 2.0.0)
message(FATAL_ERROR “OpenCV version is not compatible : ${OpenCV_VERSION}”)
endif()

# compilation flags
set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11")

# put the binary files in this directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# create a directory called 'output' in the project binary directory
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output)


# put here all the file to compile
add_executable(video src/main.cpp src/color.cpp src/track.cpp include/color.hpp include/track.hpp)

# put here all the libraries to link
target_link_libraries(video ${OpenCV_LIBS})



