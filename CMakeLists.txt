#
# quake2
# Copyright (c) 2013, Alejandro Ricoveri
#
# CMake build script
#

cmake_minimum_required(VERSION 2.8.8)

# define a macro that helps defining an option
macro(q2_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# set a default build type if none was provided
# this has to be done before the project() instruction!
q2_set_option(CMAKE_BUILD_TYPE Debug STRING "Choose the type of build (Debug or Release)")

# setup version numbers
set (PROJ_NAME "quake2")
set (VERSION_MAJOR 5)
set (VERSION_MINOR 10)
set (VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR})

# set project name
project (${PROJ_NAME})

# Define sources and executable
set (EXECUTABLE_NAME "quake2")

# Set debug flag
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (BUILD_DEBUG 1)
    add_definitions(-DDIV_DEBUG)
endif()

# Helpful modules are here
set (CMAKE_GOODIES_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH "${CMAKE_GOODIES_PATH}/modules"
    ${CMAKE_MODULE_PATH})

# detect OS, compiler, architecture
include(${CMAKE_GOODIES_PATH}/Config.cmake)

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

# Source files root directory
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Definitions
if (WINDOWS)
    add_definitions (-DDIV_OS_WIN32)
elseif (MACOSX)
    add_definitions (-DDIV_OS_OSX)
    add_definitions (-DDIV_OS_UNIX)
elseif (LINUX)
    add_definitions (-DDIV_OS_LINUX)
    add_definitions (-DDIV_OS_UNIX)
else()
    add_definitions (-DDIV_OS_UNIX)
endif ()

#
# Source files
#

# Platform-specific backends
set (
    BACKENDS_SRC

    ${SRC_DIR}/backends/generic/qal.c
    ${SRC_DIR}/backends/generic/vid.c
    ${SRC_DIR}/backends/sdl/cd.c
    ${SRC_DIR}/backends/sdl/sound.c
    ${SRC_DIR}/backends/windows/network.c
    ${SRC_DIR}/backends/windows/system.c
    ${SRC_DIR}/backends/windows/shared/mem.c
    ${SRC_DIR}/backends/unix/main.c
    ${SRC_DIR}/backends/unix/network.c
    ${SRC_DIR}/backends/unix/signalhandler.c
    ${SRC_DIR}/backends/unix/system.c
    ${SRC_DIR}/backends/unix/shared/hunk.c
    ${SRC_DIR}/backends/sdl_osx/SDLMain.m
)

# Common
set (
    COMMON_SRC

    ${SRC_DIR}/common/argproc.c
    ${SRC_DIR}/common/clientserver.c
    ${SRC_DIR}/common/collision.c
    ${SRC_DIR}/common/crc.c
    ${SRC_DIR}/common/cmdparser.c
    ${SRC_DIR}/common/cvar.c
    ${SRC_DIR}/common/filesystem.c
    ${SRC_DIR}/common/glob.c
    ${SRC_DIR}/common/md4.c
    ${SRC_DIR}/common/movemsg.c
    ${SRC_DIR}/common/misc.c
    ${SRC_DIR}/common/netchan.c
    ${SRC_DIR}/common/pmove.c
    ${SRC_DIR}/common/szone.c
    ${SRC_DIR}/common/zone.c
    ${SRC_DIR}/common/shared/flash.c
    ${SRC_DIR}/common/shared/rand.c
    ${SRC_DIR}/common/shared/shared.c
    ${SRC_DIR}/common/unzip/ioapi.c
    ${SRC_DIR}/common/unzip/unzip.c 
    )

# Server
set (
    SERVER_SRC

    ${SRC_DIR}/server/sv_cmd.c
    ${SRC_DIR}/server/sv_conless.c
    ${SRC_DIR}/server/sv_entities.c
    ${SRC_DIR}/server/sv_game.c
    ${SRC_DIR}/server/sv_init.c
    ${SRC_DIR}/server/sv_main.c
    ${SRC_DIR}/server/sv_save.c
    ${SRC_DIR}/server/sv_send.c
    ${SRC_DIR}/server/sv_user.c
    ${SRC_DIR}/server/sv_world.c
    )

# Client
set (
    CLIENT_SRC

    ${SRC_DIR}/client/cl_cin.c
    ${SRC_DIR}/client/cl_console.c
    ${SRC_DIR}/client/cl_download.c
    ${SRC_DIR}/client/cl_effects.c
    ${SRC_DIR}/client/cl_entities.c
    ${SRC_DIR}/client/cl_input.c
    ${SRC_DIR}/client/cl_inventory.c
    ${SRC_DIR}/client/cl_keyboard.c
    ${SRC_DIR}/client/cl_lights.c
    ${SRC_DIR}/client/cl_main.c
    ${SRC_DIR}/client/cl_network.c
    ${SRC_DIR}/client/cl_parse.c
    ${SRC_DIR}/client/cl_particles.c
    ${SRC_DIR}/client/cl_prediction.c
    ${SRC_DIR}/client/cl_screen.c
    ${SRC_DIR}/client/cl_tempentities.c
    ${SRC_DIR}/client/cl_view.c
    ${SRC_DIR}/client/menu/menu.c
    ${SRC_DIR}/client/menu/qmenu.c
    ${SRC_DIR}/client/menu/videomenu.c
    ${SRC_DIR}/client/sound/ogg.c
    ${SRC_DIR}/client/sound/openal.c
    ${SRC_DIR}/client/sound/sound.c
    ${SRC_DIR}/client/sound/wave.c

    ${SERVER_SRC} 
    ${REF_SRC}
    ${BACKENDS_SRC}
    )

# Include path
include_directories (${SRC_DIR})

# Executable name
add_executable (${CLIENT_EXEC} ${CLIENT_SRC})
add_executable (${SERVER_EXEC} ${SERVER_SRC})

# Link with libraries
target_link_libraries(${CLIENT_EXEC} ${OPENGL_LIBRARIES} )
