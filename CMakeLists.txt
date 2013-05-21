#
# Hecatomb
# A Quake II Engine Extension
# http://github.com/alericoveri/hecatomb
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
# ---------------------
macro(ht_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# set a default build type if none was provided
# this has to be done before the project() instruction!
# ---------------------
ht_set_option(CMAKE_BUILD_TYPE Debug STRING
    "Choose the type of build (Debug or Release)")


# set project name
# ---------------------
set (PROJ_NAME "hecatomb")
project (${PROJ_NAME})

# Essential info
# ---------------------
set (PROJ_DEVNAME "htq2")
set (PROJ_URL "github.com/alericoveri/hecatomb")
set (PROJ_GIT_URL "git://github.com/alericoveri/hecatomb.git")
set (PROJ_PRODUCT_NAME "Hecatomb Quake II")
set (PROJ_EMAIL "alejandroricoveri@gmail.com")
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)
set (VERSION "${VERSION_MAJOR}.${VERSION_MINOR}${VERSION_PATCH}")

# Helpful modules are here
# ---------------------
set (CMAKE_GOODIES_PATH ${CMAKE_SOURCE_DIR}/cmake)
set (CMAKE_MODULE_PATH "${CMAKE_GOODIES_PATH}/modules" ${CMAKE_MODULE_PATH})

# detect OS, compiler, architecture
# ---------------------
include (${CMAKE_GOODIES_PATH}/Config.cmake)

# Set debug/release definitions
# ---------------------
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set (HT_BUILD_DEBUG 1)
  set (HT_CC_CFLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
else()
  set (HT_BUILD_RELEASE 1)
  add_definitions (-DNDEBUG)
  set (HT_CC_CFLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
endif()

# All goodies are available on Windows and OSX
# ---------------------
if (WINDOWS OR OSX)
  set (HT_WITH_OGG TRUE)
  set (HT_WITH_OPENAL TRUE)
  set (HT_WITH_ZIP TRUE)
  set (HT_WITH_RETEXTURE TRUE)
endif()

#
# Architecture settings
# ---------------------
if (ARCH STREQUAL "i386")
    set (HT_ARCH_x86 1)
elseif (ARCH STREQUAL "x86_64")
    set (HT_ARCH_x86_64 1)
elseif (ARCH STREQUAL "armv7")
    set (HT_ARCH_arm 1)
    set (HT_ARCH_armv7 1)
elseif (ARCH STREQUAL "armv6")
    set (HT_ARCH_arm 1)
    set (HT_ARCH_armv6 1)
elseif (ARCH STREQUAL "armv5")
    set (HT_ARCH_arm 1)
    set (HT_ARCH_armv5 1)
elseif (ARCH STREQUAL "arm")
    set (HT_ARCH_arm 1)
elseif (ARCH STREQUAL "ia64")
    set (HT_ARCH_ia64 1)
elseif (ARCH STREQUAL "ppc64")
    set (HT_ARCH_ppc64 1)
elseif (ARCH STREQUAL "ppc")
    set (HT_ARCH_ppc 1)
endif()

# Check basic C headers
# ---------------------
include (CheckIncludeFiles)
check_include_files (assert.h HT_HAVE_ASSERT_H)
check_include_files (math.h HT_HAVE_MATH_H)
check_include_files (string.h HT_HAVE_STRING_H)
check_include_files (stdarg.h HT_HAVE_STDARG_H)
check_include_files (stdio.h HT_HAVE_STDIO_H)
check_include_files (stdlib.h HT_HAVE_STDLIB_H)
check_include_files (ctype.h HT_HAVE_CTYPE_H)
check_include_files (setjmp.h HT_HAVE_SETJMP_H)
check_include_files (signal.h HT_HAVE_SIGNAL_H)
check_include_files (time.h HT_HAVE_TIME_H)
check_include_files (locale.h HT_HAVE_LOCALE_H)
check_include_files (errno.h HT_HAVE_ERRNO_H)
check_include_files (stdint.h HT_HAVE_STDINT_H)

# let CMake know about our additional libraries paths (on Windows and OS X)
# Thanks to SFML guys for this snippet
# ---------------------
set (EXTLIBS_BASE "${PROJECT_SOURCE_DIR}/extlibs")
set (EXTLIBS_HEADERS "${EXTLIBS_BASE}/include")
set (EXTLIBS_LIBS "${EXTLIBS_BASE}/libs")
set (EXTLIBS_BIN "${EXTLIBS_BASE}/bin")
if (WINDOWS)
  set (CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${EXTLIBS_HEADERS}")
  set (SDL_INCLUDE_DIR ${EXTLIBS_HEADERS})
  set (OPENAL_INCLUDE_DIR ${EXTLIBS_HEADERS})
  if (COMPILER_GCC)
    set (EXTLIBS_LIBS_MINGW "${EXTLIBS_LIBS}/mingw")
    if (HT_ARCH_x86)
      set (CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${EXTLIBS_LIBS_MINGW}/x86")
      set (CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${EXTLIBS_BIN}/x86")
    elseif(HT_ARCH_x86_64)
      set (CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${EXTLIBS_LIBS_MINGW}/x64")
      set (CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${EXTLIBS_BIN}/x64")
    endif()
  endif()
elseif (OSX)
  # default to searching for frameworks first
  set (CMAKE_FIND_FRAMEWORK FIRST)
  # set up the default search directories for frameworks
  set (CMAKE_SYSTEM_FRAMEWORK_PATH "${EXTLIBS_LIBS}/osx" ${CMAKE_SYSTEM_FRAMEWORK_PATH})
endif()

# Enables CD audio playback. CD audio playback is used
# for the background music and doesn't add any further
# dependencies. It should work on all platforms where
# CD playback is supported by SDL.
# ---------------------
ht_set_option(HT_WITH_CDA FALSE BOOL "CD audio playback support")

# Enables OGG/Vorbis support. OGG/Vorbis files can be
# used as a substitute of CD audio playback. Adds
# dependencies to libogg, libvorbis and libvorbisfile.
# This features won't be present on Windows
# until I find the right binaries for it
# ---------------------
ht_set_option(HT_WITH_OGG TRUE BOOL "OGG/Vorbis support")

# Enables retexturing support. Adds
# a dependency to libjpeg
# ---------------------
ht_set_option(HT_WITH_RETEXTURE FALSE BOOL "Retexturing support")

# Enables opening of ZIP files (also known as .pk3 packs).
# Adds a dependency to libz
# ---------------------
ht_set_option(HT_WITH_ZIP FALSE BOOL
  "ZIP files support (for opening .pk3 packs)")

# Enables the optional OpenAL sound system.
# To use it your system needs libopenal.so.1
# or openal32.dll (we recommend openal-soft)
# installed
# ---------------------
ht_set_option(HT_WITH_OPENAL FALSE BOOL
  "Use the OpenAL sound system")

# Set the gamma via X11 and not via SDL. This works
# around problems in some SDL version. Adds dependencies
# to pkg-config, libX11 and libXxf86vm. Unsupported on
# Windows and OS X.
# ---------------------
if (UNIX AND NOT OSX)
  ht_set_option(HT_WITH_X11GAMMA FALSE BOOL
    "Set the gamma via X11 and not via SDL")
endif()

# Enable systemwide installation of game assets
# ---------------------
ht_set_option(HT_WITH_SYSTEMWIDE TRUE BOOL
  "Enable systemwide installation of game assets")

# This will set the default SYSTEMDIR, a non-empty string
# would actually be used. On Windows normals slashes (/)
# instead of backslashed (\) should be used!
# ---------------------
if (WINDOWS)
  set (SYSTEMDIR_DEFAULT c:/quake2)
else()
  set (SYSTEMDIR_DEFAULT /usr/share/games/quake2)
endif()
ht_set_option(HT_WITH_SYSTEMDIR "${SYSTEMDIR_DEFAULT}"
    PATH "Location of system-wide game assets installation")

# Compiler related definitions
# ---------------------
if (COMPILER_GCC)
    set (HT_CC_GCC 1)
elseif (COMPILER_CLANG)
    set (HT_CC_CLANG 1)
else()
  set (HT_CC_UNK 1)
endif()

if (UNIX)

  # Optional execinfo support for backtracing on crashes
  # ---------------------
  find_package (Libexecinfo)
  if(LIBEXECINFO_LIB_FOUND)
    set(HT_HAVE_EXECINFO 1)
  endif()

  # dlopen, dlsym, dlclose, etc ...
  # ---------------------
  find_package (LibDL REQUIRED)
endif()

# X11 libraries
# ---------------------
if (HT_WITH_X11GAMMA)
  find_package (X11 REQUIRED)
endif()

# OpenGL
# ---------------------
find_package(OpenGL REQUIRED)

# OpenAL
# ---------------------
if (HT_WITH_OPENAL)
  find_package(OpenAL REQUIRED)
endif()

# SDL
# ---------------------
find_package (SDL REQUIRED)

# OGG and Vorbis
# ---------------------
if (HT_WITH_OGG)
  find_package (VORBIS REQUIRED)
endif()

# libjpeg
# ---------------------
if (HT_WITH_RETEXTURE)
  if (OSX)
    set (JPEG_NAMES libjpeg)
  endif()
  find_package (JPEG REQUIRED)
endif()

# zlib
# ---------------------
if (HT_WITH_ZIP)
  find_package (ZLIB REQUIRED)
endif()

# Source files
# ---------------------
add_subdirectory (src)
