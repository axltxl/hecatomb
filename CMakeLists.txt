#
# division : A minimalist FPS game
# Copyright (c) 2012, Alejandro Ricoveri
#
# CMake build script
#

cmake_minimum_required(VERSION 2.8.8)

# define a macro that helps defining an option
macro(div_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# set a default build type if none was provided
# this has to be done before the project() instruction!
div_set_option(CMAKE_BUILD_TYPE Debug STRING "Choose the type of build (Debug or Release)")

# setup version numbers
set (PROJ_NAME "division")
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_PATCH 0)
set (VERSION_NICK "penelope")
set (VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR})

# set project name
project (${PROJ_NAME})

# Define sources and executable
set (EXECUTABLE_NAME "division")

# Set debug flag
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (BUILD_DEBUG 1)
    add_definitions(-DDIV_DEBUG)
endif()

# Set default log treshold
if (BUILD_DEBUG)
    set (LOG_TRESHOLD 2)
else()
    set (LOG_TRESHOLD 5)
endif()

# Helpful modules are here
set (CMAKE_GOODIES_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH "${CMAKE_GOODIES_PATH}/modules"
    ${CMAKE_MODULE_PATH})

# detect OS, compiler, architecture
include(${CMAKE_GOODIES_PATH}/Config.cmake)

# Useful macros
include(${CMAKE_GOODIES_PATH}/Macros.cmake)

# Architecture name string
# Used in WINDOW_CAPTION
if(ARCH_32BITS)
    set (ARCH_NAME "x86")
else()
    set (ARCH_NAME "x86_64")
endif()

# This string will be used in the main window's caption
set(WINDOW_CAPTION "${PROJ_NAME} ${VERSION_STRING} (${CMAKE_SYSTEM_NAME}-${ARCH_NAME})")

# OpenGL
find_package(OpenGL REQUIRED)

# SFML
find_package(SFML 2.0 QUIET COMPONENTS system window graphics network audio)

# Lua
find_package (Lua 5.2 REQUIRED)

# Couldn't find SFML.
if( NOT SFML_FOUND )
	set( SFML_ROOT "" CACHE PATH "SFML root directory" )
	message( FATAL_ERROR "CMake couldn't find SFML. Set the SFML_ROOT entry to SFML's root directory (containing \"include\" and \"lib\" directories)." )
endif()

# Source files root directory
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configuration definitions for Config.h
if (WINDOWS)
    add_definitions (-DDIV_OS_WIN32)
elseif (MACOSX)
    add_definitions (-DDIV_OS_OSX)
    add_definitions (-DDIV_OS_POSIX)
elseif (LINUX)
    add_definitions (-DDIV_OS_LINUX)
    add_definitions (-DDIV_OS_POSIX)
else()
    add_definitions (-DDIV_OS_POSIX)
endif ()

# Config.h
# Configuration file
 configure_file(
  "${SRC_DIR}/Config.h.in"
  "${SRC_DIR}/Config.h"
)

#
# Source files
#
set (
    SRC

    # Core Interfaces
    ${SRC_DIR}/CVar.cpp
    ${SRC_DIR}/Core.cpp
    ${SRC_DIR}/GameException.cpp

    # Logger
    ${SRC_DIR}/log/Log.cpp
    ${SRC_DIR}/log/FileLog.cpp
    ${SRC_DIR}/log/StdLog.cpp

    # Input
    ${SRC_DIR}/input/Basic.cpp

    # Renderer
    ${SRC_DIR}/renderer/Basic.cpp

    # Script Engine
    ${SRC_DIR}/script/Basic.cpp
    ${SRC_DIR}/script/API_Core.cpp

    # Our beloved main()
    ${SRC_DIR}/Main.cpp
)

# Include path
include_directories (${SFML_INCLUDE_DIR})
include_directories (${LUA_INCLUDE_DIR})
include_directories (${SRC_DIR})

# Executable name
add_executable (${EXECUTABLE_NAME} ${SRC})

# Link with libraries
target_link_libraries(${EXECUTABLE_NAME}
    ${OPENGL_LIBRARIES} ${SFML_LIBRARIES} ${LUA_LIBRARIES})
