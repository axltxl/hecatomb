#
# Hecatomb
# A Quake II Engine Extension
# http://github.com/alericoveri/hecatomb
#
# CMake build automation scripts
# Author: Alejandro Ricoveri <alejandroricoveri@gmail.com>
#
# Platform-specific backends
# --------------------------------
#

# Base directory
set (BACKEND_DIR ${SRC_DIR}/backends)

# Generic backend
set (BACKEND_GENERIC_DIR ${BACKEND_DIR}/generic)
set (
  BACKEND_GENERIC_SRC

  ${BACKEND_GENERIC_DIR}/vid.c
  ${BACKEND_GENERIC_DIR}/qgl.c
)

# OpenAL support (QAL)
if (HT_WITH_OPENAL)
  list (APPEND BACKEND_GENERIC_SRC ${BACKEND_GENERIC_DIR}/qal.c)
endif()
set (BACKEND_CLIENT_SRC ${BACKEND_GENERIC_SRC})

# SDL Backend
set (BACKEND_SDL_DIR ${BACKEND_DIR}/sdl)
set (
  BACKEND_SDL_SRC

  ${BACKEND_SDL_DIR}/input.c
  ${BACKEND_SDL_DIR}/refresh.c
  ${BACKEND_SDL_DIR}/sound.c
)

# SDLMain.m (OSX)
if (OSX)
  list (APPEND BACKEND_SDL_SRC ${BACKEND_DIR}/sdl_osx/SDLMain.m)
endif()
# SDL will be only for the client
list (APPEND BACKEND_CLIENT_SRC ${BACKEND_SDL_SRC})

# Unix backend
if (UNIX)
  set (BACKEND_UNIX_DIR ${BACKEND_DIR}/unix)
  set (
    BACKEND_UNIX_SRC

    ${BACKEND_UNIX_DIR}/main.c
    ${BACKEND_UNIX_DIR}/network.c
    ${BACKEND_UNIX_DIR}/signalhandler.c
    ${BACKEND_UNIX_DIR}/system.c
  )
  if (NOT HT_HUNKDRIVER_GENERIC)
    list (APPEND BACKEND_UNIX_SRC ${BACKEND_UNIX_DIR}/hunk.c)
  else()
    list (APPEND BACKEND_UNIX_SRC ${BACKEND_GENERIC_DIR}/hunk.c)
  endif()
  list (APPEND BACKEND_CLIENT_SRC ${BACKEND_UNIX_SRC})
  list (APPEND BACKEND_SERVER_SRC ${BACKEND_UNIX_SRC})
endif()

# Windows backend
if (WINDOWS)
  set (BACKEND_WINDOWS_DIR ${BACKEND_DIR}/windows)
  set (
    BACKEND_WINDOWS_SRC

    ${BACKEND_WINDOWS_DIR}/network.c
    ${BACKEND_WINDOWS_DIR}/system.c
  )
  if (NOT HT_HUNKDRIVER_GENERIC)
    list (APPEND BACKEND_WINDOWS_SRC ${BACKEND_WINDOWS_DIR}/hunk.c)
  else()
    list (APPEND BACKEND_WINDOWS_SRC ${BACKEND_GENERIC_DIR}/hunk.c)
  endif()
  list (APPEND BACKEND_CLIENT_SRC ${BACKEND_WINDOWS_SRC})
  list (APPEND BACKEND_SERVER_SRC ${BACKEND_WINDOWS_SRC})
endif()

# OSX backend

# Export everything
set (BACKEND_CLIENT_SRC ${BACKEND_CLIENT_SRC} PARENT_SCOPE)
set (BACKEND_SERVER_SRC ${BACKEND_SERVER_SRC} PARENT_SCOPE)

