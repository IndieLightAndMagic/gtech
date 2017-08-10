cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(camsample)
add_executable(camsample camsample.cpp)

#DEBUG
set(CMAKE_VERBOSE_MAKEFILE ON)

#DIRECTORIES
get_filename_component(ROOT_DIR "../.." ABSOLUTE)
set(INCLUDE_DIR "${ROOT_DIR}/inc")
set(LIB_DIR "${ROOT_DIR}/lib")
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ROOT_DIR: ${ROOT_DIR}")
message(STATUS "INCLUDE_DIR: ${INCLUDE_DIR}")
message(STATUS "LIB_DIR: ${LIB_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "-----------------------------")


#C++11
set(CPP11 "-std=c++11")
#HEADER FILES
include_directories(${INCLUDE_DIR})
#COMPILE FLAGS
set(CMAKE_CXX_FLAGS "${CPP11}")

#LIBRARY LINKS
set(STANDARD_STATIC_LIBRARIES "iconv" "m")
set(G_STATIC_LIBRARIES "SDL2" "shdr" "Primitive" "Util")
set(STATIC_LIBRARIES ${STANDARD_STATIC_LIBRARIES} ${G_STATIC_LIBRARIES})


if (APPLE)
	message(STATUS "Setting Apple Frameworks")
	set(STATIC_FRAMEWORKS "OpenGL" "AudioToolbox" "CoreAudio" "Carbon" "ForceFeedback" "IOKit" "Cocoa" "CoreVideo")
endif()

foreach(STANDARD_STATIC_LIB ${STANDARD_STATIC_LIBRARIES})
	target_link_libraries(camsample "-l${STANDARD_STATIC_LIB}")
endforeach(STANDARD_STATIC_LIB)
foreach(LIB ${STATIC_LIBRARIES})
	message(STATUS "Static Lib: lib${LIB}.a")
endforeach(LIB)
foreach(G_STATIC_LIB ${G_STATIC_LIBRARIES})
	target_link_libraries(camsample "${CMAKE_SOURCE_DIR}/../../lib/lib${G_STATIC_LIB}.a")
	message(STATUS "${CMAKE_SOURCE_DIR}/../../lib/lib${G_STATIC_LIB}.a")
endforeach(G_STATIC_LIB)

if (APPLE)
foreach(FMWK ${STATIC_FRAMEWORKS})
	target_link_libraries(camsample "-framework ${FMWK}")
	message(STATUS "Framework: ${FMWK}")
endforeach(FMWK)

message(STATUS "-----------------------------")
endif()


