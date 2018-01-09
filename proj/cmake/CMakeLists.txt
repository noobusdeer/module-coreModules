cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE )
get_filename_component( MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." ABSOLUTE )
get_filename_component( CINDER_PATH "${MODULE_PATH}/deps/Cinder" ABSOLUTE)

project(Plugin)	

include_directories( PUBLIC "${APP_PATH}/include")
list( APPEND SOURCES
        ${APP_PATH}/src/coreModules.cpp
        ${APP_PATH}/src/video.cpp
        ${APP_PATH}/src/template.cpp
	)

add_library(Plugin SHARED ${SOURCES})

if( NOT TARGET cinder )
    include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
    find_package( cinder REQUIRED PATHS
        "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
        "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
endif()

if( NOT TARGET moduleCore )
    add_library(moduleCore SHARED IMPORTED)
    set_target_properties(moduleCore PROPERTIES
        INTERFACE_COMPILE_DEFINITIONS "FT2_BUILD_LIBRARY;FT_DEBUG_LEVEL_TRACE;_UNIX;_GLFW_X11 -D_GLFW_GLX -D_GLFW_USE_OPENGL"
        INTERFACE_COMPILE_OPTIONS "-std=c++14"
        INTERFACE_INCLUDE_DIRECTORIES "${MODULE_PATH}/libs/moduleCore/include"
        INTERFACE_LINK_LIBRARIES "${MODULE_PATH}/libs/libmoduleCore.so"
    )
    set_property(TARGET moduleCore APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
    set_target_properties(moduleCore PROPERTIES
        IMPORTED_LOCATION_DEBUG "${MODULE_PATH}/libs/libmoduleCore.so"
        IMPORTED_SONAME_DEBUG "libmoduleCore.so"
    )
endif()

if( NOT TARGET NanoVG )
    add_library(NanoVG SHARED IMPORTED)
    set_target_properties(NanoVG PROPERTIES
        INTERFACE_COMPILE_DEFINITIONS "FT2_BUILD_LIBRARY;FT_DEBUG_LEVEL_TRACE;_UNIX;_GLFW_X11 -D_GLFW_GLX -D_GLFW_USE_OPENGL"
        INTERFACE_COMPILE_OPTIONS "-std=c++14"
        INTERFACE_INCLUDE_DIRECTORIES "${MODULE_PATH}/deps/NanoVG/include;${MODULE_PATH}/deps/NanoVG/deps/nanovg/src"
        INTERFACE_LINK_LIBRARIES "${MODULE_PATH}/deps/libNanoVG.so"
    )
    set_property(TARGET NanoVG APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
    set_target_properties(NanoVG PROPERTIES
        IMPORTED_LOCATION_DEBUG "${MODULE_PATH}/deps/libNanoVG.so"
        IMPORTED_SONAME_DEBUG "libNanoVG.so"
    )
endif()

target_link_libraries( Plugin PRIVATE cinder PUBLIC moduleCore NanoVG )

set_target_properties( Plugin
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${APP_PATH}"
    LIBRARY_OUTPUT_DIRECTORY "${APP_PATH}"
    RUNTIME_OUTPUT_DIRECTORY "${APP_PATH}"
)
