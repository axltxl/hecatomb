#
#
# Yamagi Quake II
# http://www.yamagi.org/quake2
# http://github.com/yquake2
#
# CMake build automation scripts
# Author: Alejandro Ricoveri <alejandroricoveri@gmail.com>
#
# ==================================================
# !!! DO NOT ALTER ANYTHING BELOW THIS LINE !!!
# (unless you know what you're doing)
# ==================================================
#
cmake_minimum_required(VERSION 2.8)

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
set (PROJ_NAME "yquake2")

# set project name
project (${PROJ_NAME} C)

# Set debug/release definitions
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (BUILD_DEBUG 1)
    add_definitions(-DYQ2_DEBUG)
else()
    set (BUILD_RELEASE 1)
    add_definitions (-DNDEBUG -DYQ2_RELEASE)
endif()

# Helpful modules are here
set (CMAKE_GOODIES_PATH ${CMAKE_SOURCE_DIR}/cmake)
set (CMAKE_MODULE_PATH "${CMAKE_GOODIES_PATH}/modules" ${CMAKE_MODULE_PATH})

# detect OS, compiler, architecture
include (${CMAKE_GOODIES_PATH}/Config.cmake)

# Enables CD audio playback. CD audio playback is used
# for the background music and doesn't add any further
# dependencies. It should work on all platforms where
# CD playback is supported by SDL.
ht_set_option(YQ2_WITH_CDA TRUE BOOL "CD audio playback support")

# Enables OGG/Vorbis support. OGG/Vorbis files can be
# used as a substitute of CD audio playback. Adds
# dependencies to libogg, libvorbis and libvorbisfile.
ht_set_option(YQ2_WITH_OGG TRUE BOOL "OGG/Vorbis support")

# Enables the optional OpenAL sound system.
# To use it your system needs libopenal.so.1
# or openal32.dll (we recommend openal-soft)
# installed
ht_set_option(YQ2_WITH_OPENAL FALSE BOOL "Use the OpenAL sound system")

# Enables retexturing support. Adds
# a dependency to libjpeg
ht_set_option(YQ2_WITH_RETEXTURE FALSE BOOL "Retexturing support")

if (UNIX)
  # Set the gamma via X11 and not via SDL. This works
  # around problems in some SDL version. Adds dependencies
  # to pkg-config, libX11 and libXxf86vm. Unsupported on
  # Windows and OS X.
  ht_set_option(YQ2_WITH_X11GAMMA FALSE BOOL "Set the gamma via X11 and not via SDL")
endif()

# Enables opening of ZIP files (also known as .pk3 packs).
# Adds a dependency to libz
ht_set_option(YQ2_WITH_ZIP FALSE BOOL "ZIP files support (for opening .pk3 packs)")

# Enable systemwide installation of game assets
ht_set_option(YQ2_SYSTEMWIDE TRUE BOOL "Enable systemwide installation of game assets")

# This will set the default SYSTEMDIR, a non-empty string
# would actually be used. On Windows normals slashes (/)
# instead of backslashed (\) should be used!
if (WINDOWS)
  set (SYSTEMDIR_DEFAULT c:\\quake2)
else()
  set (SYSTEMDIR_DEFAULT /usr/share/games/quake2)
endif()
ht_set_option(YQ2_SYSTEMDIR "${SYSTEMDIR_DEFAULT}" STRING "Location of system-wide game assets installation")

# Architecture name string
if (ARCH_32)
    set (ARCH_NAME "x86")
    add_definitions (-DYQ2_ARCH_32)
else()
    set (ARCH_NAME "x86_64")
    add_definitions (-DYQ2_ARCH_64)
endif()

# Compiler related definitions
if (COMPILER_GCC)
    add_definitions (-DYQ2_COMPILER_GCC)
elseif (COMPILER_CLANG)
    add_definitions (-DYQ2_COMPILER_CLANG)
endif()

# X11 libraries
if (YQ2_WITH_X11GAMMA)
  find_package (X11 REQUIRED)
endif()

# OpenGL
find_package(OpenGL REQUIRED)

# OpenAL
if (YQ2_WITH_OPENAL)
  find_package(OpenAL REQUIRED)
endif()

# SDL
find_package (SDL REQUIRED)

# OGG and Vorbis
if (YQ2_WITH_OGG)
  find_package (VORBIS REQUIRED)
endif()

# libjpeg
if (YQ2_WITH_RETEXTURE)
  find_package (JPEG REQUIRED)
endif()

# zlib
if (YQ2_WITH_ZIP)
  find_package (ZLIB REQUIRED)
endif()

# Source files
add_subdirectory (src)
