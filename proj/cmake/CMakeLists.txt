cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project(core)			
set(SOURCE_LIB ../../src/video.cpp)	
#add_subdirectory(../../../../../proj/cmake)
include_directories(../../../../../include)	
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
add_library(core STATIC ${SOURCE_LIB})
