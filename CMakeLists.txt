cmake_minimum_required (VERSION 2.6)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project (votracker)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package (OpenCV REQUIRED)

include_directories ("${PROJECT_SOURCE_DIR}/lib")
add_library (votrackerlib SHARED
	include/sys_lib.h
        include/TrackRegion.h
	include/votracker_lib.h)
set_target_properties(votrackerlib PROPERTIES LINKER_LANGUAGE CXX)

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable (trackermain src/votrackermain.cpp)
target_link_libraries(trackermain ${OpenCV_LIBS})
target_link_libraries(trackermain votrackerlib)
