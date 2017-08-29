cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

#Project Name and Resources 
set(TARGET_NAME componentsample)


project(${TARGET_NAME})



aux_source_directory(${CMAKE_SOURCE_DIR} SOURCE_LIST)
if (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
	add_executable(${TARGET_NAME} ${SOURCE_LIST})
elseif (${CMAKE_GENERATOR} STREQUAL "Xcode")
	set_source_files_properties(${SHADERS} PROPERTIES MACOSX_PACKAGE_LOCATION ../..)
	add_executable(${TARGET_NAME} MACOSX_BUNDLE ${SHADERS} ${SOURCE_LIST} )
endif()


#DEBUG
set(CMAKE_VERBOSE_MAKEFILE ON)

#DIRECTORIES
get_filename_component(ROOT_DIR "../../.." ABSOLUTE)
set(INCLUDE_DIR "${ROOT_DIR}/inc")
set(LIB_DIR "${ROOT_DIR}/lib")
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ROOT_DIR: ${ROOT_DIR}")
message(STATUS "INCLUDE_DIR: ${INCLUDE_DIR}")
message(STATUS "LIB_DIR: ${LIB_DIR}")
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
#HEADER FILES
include_directories(${INCLUDE_DIR})
#COMPILE FLAGS
set(CMAKE_CXX_FLAGS "${CPP11}")

#LIBRARY LINKS
set(STANDARD_STATIC_LIBRARIES "iconv" "m")
set(G_STATIC_LIBRARIES "G0")
set(STATIC_LIBRARIES ${STANDARD_STATIC_LIBRARIES} ${G_STATIC_LIBRARIES})



if (APPLE)
	message(STATUS "Setting Apple Frameworks")
	set(STATIC_FRAMEWORKS "")
endif()

foreach(STANDARD_STATIC_LIB ${STANDARD_STATIC_LIBRARIES})
	target_link_libraries(${TARGET_NAME} "-l${STANDARD_STATIC_LIB}")
endforeach(STANDARD_STATIC_LIB)
foreach(LIB ${STATIC_LIBRARIES})
	message(STATUS "Static Lib: lib${LIB}.a")
endforeach(LIB)
foreach(G_STATIC_LIB ${G_STATIC_LIBRARIES})
	target_link_libraries(${TARGET_NAME} "${LIB_DIR}/lib${G_STATIC_LIB}.a")
	message(STATUS "${LIB_DIR}/lib${G_STATIC_LIB}.a")
endforeach(G_STATIC_LIB)

if (APPLE)
foreach(FMWK ${STATIC_FRAMEWORKS})
	target_link_libraries(${TARGET_NAME} "-framework ${FMWK}")
	message(STATUS "Framework: ${FMWK}")
endforeach(FMWK)

message(STATUS "-----------------------------")
endif()

if (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
	add_custom_target(run)
	foreach(SHADER ${SHADERS})
		add_custom_command(
			TARGET run PRE_BUILD 
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/)	
	endforeach(SHADER)
endif()
