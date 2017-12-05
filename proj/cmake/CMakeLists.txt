cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )
get_filename_component( MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../" ABSOLUTE )
get_filename_component( CINDER_PATH "${MODULE_PATH}/../../../" ABSOLUTE)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../" )
project(CoreModules)	

set(SOURCE_LIB ../../src/video.cpp)	
include_directories(${MODULE_PATH}/include)	

add_library(CoreModules SHARED ${SOURCE_LIB})

if( NOT TARGET cinder )
    include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
    find_package( cinder REQUIRED PATHS
        "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
        "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
endif()

if( NOT TARGET NanoVG )
    get_filename_component( nanoVgComp "${CINDER_PATH}/blocks/NanoVG/proj/cmake/" ABSOLUTE )
    find_package( "NanoVG" PATHS "${nanoVgComp}" NO_DEFAULT_PATH )
    add_dependencies( CoreModules NanoVG )
endif()

target_link_libraries( CoreModules PRIVATE cinder PUBLIC NanoVG )
