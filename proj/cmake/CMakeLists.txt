cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../" ABSOLUTE )

project(core)	

set(SOURCE_LIB ../../src/video.cpp)	
include_directories(../../../../../include)	


set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
add_library(core SHARED ${SOURCE_LIB})


if( NOT TARGET cinder )
    include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
    find_package( cinder REQUIRED PATHS
        "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
        "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
endif()

target_link_libraries( core PRIVATE cinder )