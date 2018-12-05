#CMAKE TO MAKE A STATIC LIBRARY
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(TARGET_NAME ShaderMan)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 17)

#Installation directory 
get_filename_component(GTECH_DIR $ENV{GTECH_ROOT} ABSOLUTE)
set(GTECH_DIR_LIB ${GTECH_DIR}/3rd/lib/)
set(GTECH_DIR_INC ${GTECH_DIR}/3rd/include/${TARGET_NAME})

#DIRECTORIES
get_filename_component(ROOT_DIR ${CMAKE_SOURCE_DIR} ABSOLUTE)
message(STATUS "-----------------------------")
message(STATUS "GTECH_DIR: ${GTECH_DIR}" )
message(STATUS "GTECH_DIR_LIB: ${GTECH_DIR_LIB}" )
message(STATUS "GTEC_DIR_INC + TARGET: ${GTECH_DIR_INC}" )
message(STATUS "-----------------------------")
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ROOT_DIR: ${ROOT_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "-----------------------------")

#GLM
set(GLM_DIR "${GTECH_DIR}/GLM")
message(STATUS "GLM_DIR: ${GLM_DIR}" )


add_library(${TARGET_NAME} STATIC
 
	prgrm.cpp
	shdr.cpp
	shdr_src.cpp 
	
)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
target_include_directories(${TARGET_NAME} PUBLIC ${GLM_DIR})

file(MAKE_DIRECTORY ${GTECH_DIR})
file(MAKE_DIRECTORY ${GTECH_DIR_LIB})
file(MAKE_DIRECTORY ${GTECH_DIR_INC})



#POST BUILD COMMANDS 
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy lib${TARGET_NAME}.a ${GTECH_DIR_LIB}
	COMMAND ${CMAKE_COMMAND} -E copy ${ROOT_DIR}/*.h ${GTECH_DIR_INC}
    ) 

