#
# Hecatomb
# A Quake II convolution  
# Copyright (c) 2013, Alejandro Ricoveri
#
# CMake build script
#

cmake_minimum_required(VERSION 2.8.8)

# define a macro that helps defining an option
macro(ht_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# set a default build type if none was provided
# this has to be done before the project() instruction!
ht_set_option(CMAKE_BUILD_TYPE Debug STRING "Choose the type of build (Debug or Release)")

# setup version numbers
set (PROJ_NAME "hecatomb")

# set project name
project (${PROJ_NAME} C)

# Set debug/release definitions
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (BUILD_DEBUG 1)
    add_definitions(-DHT_DEBUG)
else()
    set (BUILD_RELEASE 1)
    add_definitions (-DNDEBUG -DHT_RELEASE)
endif()

# Helpful modules are here
set (CMAKE_GOODIES_PATH ${CMAKE_SOURCE_DIR}/cmake)
set (CMAKE_MODULE_PATH "${CMAKE_GOODIES_PATH}/modules" ${CMAKE_MODULE_PATH})

# detect OS, compiler, architecture
include (${CMAKE_GOODIES_PATH}/Config.cmake)

# Architecture name string
# Used in WINDOW_CAPTION
if(ARCH_32BITS)
    set (ARCH_NAME "x86")
else()
    set (ARCH_NAME "x86_64")
endif()

# OpenGL
find_package(OpenGL REQUIRED)

# OpenAL
find_package(OpenAL REQUIRED)

# SDL
find_package (SDL REQUIRED)

# Vorbis

# libjpeg

# zlib
find_package (ZLIB REQUIRED)

# Source files
add_subdirectory (src)
