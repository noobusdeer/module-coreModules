cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )
get_filename_component( PLUGIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )
get_filename_component( MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../" ABSOLUTE )
get_filename_component( CINDER_PATH "${MODULE_PATH}/../../../" ABSOLUTE)


set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../" )

project(Plugin)	

include_directories( PUBLIC "${PLUGIN_PATH}/include" "${MODULE_PATH}/include")

list( APPEND SOURCES
		${PLUGIN_PATH}/src/coreModules.cpp
		${PLUGIN_PATH}/src/video.cpp
		${PLUGIN_PATH}/src/template.cpp
	)


add_library(Plugin SHARED ${SOURCES})

if( NOT TARGET cinder )
    include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
    find_package( cinder REQUIRED PATHS
        "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
        "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
endif()

if( NOT TARGET NanoVG )
    get_filename_component( nanoVgComp "${CINDER_PATH}/blocks/NanoVG/proj/cmake/" ABSOLUTE )
    find_package( "NanoVG" PATHS "${nanoVgComp}" NO_DEFAULT_PATH )
endif()

target_link_libraries( Plugin PRIVATE cinder PUBLIC NanoVG )
