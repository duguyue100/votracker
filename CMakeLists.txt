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
	include/VOTDraw.h
	include/FeatureExtraction.h
	include/VOTools.h
	include/VOTKeyPoint.h
	include/votracker_lib.h)
set_target_properties(votrackerlib PROPERTIES LINKER_LANGUAGE CXX)

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable (trackermain src/votrackermain.cpp)
target_link_libraries(trackermain ${OpenCV_LIBS})
target_link_libraries(trackermain votrackerlib)

add_executable (votdrawbox src/votdrawboxtest.cpp)
target_link_libraries(votdrawbox ${OpenCV_LIBS})
target_link_libraries(votdrawbox votrackerlib)

add_executable (vothaar src/vothaartest.cpp)
target_link_libraries(vothaar ${OpenCV_LIBS})
target_link_libraries(vothaar votrackerlib)

add_executable (trackernew src/votrackernew.cpp)
target_link_libraries(trackernew ${OpenCV_LIBS})
target_link_libraries(trackernew votrackerlib)

