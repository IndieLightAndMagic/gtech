#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(TARGET_NAME G0)
project(${TARGET_NAME})

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
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "-----------------------------")


#CREATE STATIC LIBRARY
aux_source_directory(${CMAKE_SOURCE_DIR} SOURCE_LIST)
message(STATUS "Sources added to build target: lib${TARGET_NAME}.a")
foreach (x ${SOURCE_LIST})
	message(STATUS ${x})
endforeach(x)

add_library(${TARGET_NAME} STATIC ${SOURCE_LIST})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
include_directories(${INCLUDE_DIR})

#COPY THIS STATIC LIBRARY TO LIB_DIR

add_custom_target(copy)
if (${CMAKE_GENERATOR} STREQUAL "Xcode")
	add_custom_command(
		TARGET copy PRE_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/Debug/lib${TARGET_NAME}.a ${LIB_DIR}/lib${TARGET_NAME}.a)
elseif(${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
	add_custom_command(
		TARGET copy PRE_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/lib${TARGET_NAME}.a ${LIB_DIR}/lib${TARGET_NAME}.a)
endif()

add_dependencies(copy ${TARGET_NAME})

