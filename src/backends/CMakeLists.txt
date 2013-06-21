#
# Hecatomb
# A portable Quake II client
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

# Init backend sources for client and server
set (BACKEND_CLIENT_SRC ${BACKEND_GENERIC_SRC})
set (BACKEND_SERVER_SRC)

# dlmalloc as the memory allocator
if (HT_MEM_DLMALLOC)
  set  (DLMALLOC_SRC ${BACKEND_GENERIC_DIR}/dlmalloc.c)
  list (APPEND BACKEND_CLIENT_SRC ${DLMALLOC_SRC})
  list (APPEND BACKEND_SERVER_SRC ${DLMALLOC_SRC})
endif()

# SDL Backend
set (BACKEND_SDL_DIR ${BACKEND_DIR}/sdl)
set (
  BACKEND_SDL_SRC

  ${BACKEND_SDL_DIR}/input.c
  ${BACKEND_SDL_DIR}/refresh.c
  ${BACKEND_SDL_DIR}/sound.c
)

# SDLMain.m (OSX)
# On SDL1.2 putting SDLmain.m BEFORE main.c will link them properly
if (OSX AND NOT HT_USE_SDL2)
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

# SDLMain.m (OSX)
# On SDL2 putting SDLmain.m AFTER main.c will link them properly
if (OSX AND HT_USE_SDL2)
  list (APPEND BACKEND_SDL_SRC ${BACKEND_DIR}/sdl_osx/SDLMain.m)
endif()

# Windows backend
if (WINDOWS)
  set (BACKEND_WINDOWS_DIR ${BACKEND_DIR}/windows)
  set (
    BACKEND_WINDOWS_SRC

    ${BACKEND_WINDOWS_DIR}/network.c
    ${BACKEND_WINDOWS_DIR}/system.c
    ${BACKEND_WINDOWS_DIR}/icon.rc
  )
  if (NOT HT_HUNKDRIVER_GENERIC)
    list (APPEND BACKEND_WINDOWS_SRC ${BACKEND_WINDOWS_DIR}/hunk.c)
  else()
    list (APPEND BACKEND_WINDOWS_SRC ${BACKEND_GENERIC_DIR}/hunk.c)
  endif()
  list (APPEND BACKEND_CLIENT_SRC ${BACKEND_WINDOWS_SRC})
  list (APPEND BACKEND_SERVER_SRC ${BACKEND_WINDOWS_SRC})
endif()

# Export everything
set (BACKEND_GENERIC_DIR ${BACKEND_GENERIC_DIR} PARENT_SCOPE)
set (BACKEND_CLIENT_SRC ${BACKEND_CLIENT_SRC} PARENT_SCOPE)
set (BACKEND_SERVER_SRC ${BACKEND_SERVER_SRC} PARENT_SCOPE)

