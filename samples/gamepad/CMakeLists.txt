cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

#Project Name and Resources 
set(TARGET_NAME camsample)


project(${TARGET_NAME})



aux_source_directory(${CMAKE_SOURCE_DIR} SOURCE_LIST)
if (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
	add_executable(${TARGET_NAME} ${SOURCE_LIST})
elseif (${CMAKE_GENERATOR} STREQUAL "Xcode")
	add_executable(${TARGET_NAME} MACOSX_BUNDLE ${SOURCE_LIST} )
endif()


#DEBUG
set(CMAKE_VERBOSE_MAKEFILE ON)

#DIRECTORIES
get_filename_component(ROOT_DIR "../.." ABSOLUTE)
set(INCLUDE_DIR "${ROOT_DIR}/inc")
set(LIB_DIR "${ROOT_DIR}/lib")
set(RES_DIR "${ROOT_DIR}/samples/Resources/")
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ROOT_DIR: ${ROOT_DIR}")
message(STATUS "INCLUDE_DIR: ${INCLUDE_DIR}")
message(STATUS "LIB_DIR: ${LIB_DIR}")
message(STATUS "RESOURCES_DIR: ${RES_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
message(STATUS "-----------------------------")

if (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
	message(STATUS "Unix Makefiles")
elseif(${CMAKE_GENERATOR} STREQUAL "Xcode")
	message(STATUS "Xcode")
endif()

#C++11
set(CPP11 "-std=c++11")
#MACRO DEFINITIONS
add_definitions(-DRES_DIR="${RES_DIR}")
#HEADER FILES
include_directories(${INCLUDE_DIR})
#COMPILE FLAGS
set(CMAKE_CXX_FLAGS "${CPP11}")

#LIBRARY LINKS
set(STANDARD_STATIC_LIBRARIES "iconv" "m")
set(G_STATIC_LIBRARIES "SDL2" "shdr" "Util" "Cam" "G0" "MeshComponent" "assimp" "IrrXML" "z")
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

