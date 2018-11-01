#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(TARGET_NAME resourcer)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 17)

#Installation directory 
get_filename_component(GTECH_DIR $ENV{GTECH_ROOT} ABSOLUTE)
set(GTECH_DIR_LIB ${GTECH_DIR}/3rd/lib/)
set(GTECH_DIR_INC ${GTECH_DIR}/3rd/include/resourcer)

#DIRECTORIES
get_filename_component(ROOT_DIR "." ABSOLUTE)
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ROOT_DIR: ${ROOT_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "-----------------------------")



add_library(${TARGET_NAME} STATIC
 

)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_BUILD_TYPE debug)

target_include_directories(${TARGET_NAME} PUBLIC
    ${GTECH_DIR_INC} 
    )

file(MAKE_DIRECTORY ${GTECH_DIR_LIB})
file(MAKE_DIRECTORY ${GTECH_DIR_INC})


#POST BUILD COMMANDS 
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy lib${TARGET_NAME}.a ${GTECH_DIR}/3rd/lib
	COMMAND ${CMAKE_COMMAND} -E copy ${ROOT_DIR}/*.h ${GTECH_DIR}/3rd/include/resourcer
	) 

