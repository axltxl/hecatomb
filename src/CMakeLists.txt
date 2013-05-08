#
# Hecatomb
# A Quake II Engine Extension
# http://github.com/alericoveri/hecatomb
#
# CMake build automation scripts
# Author: Alejandro Ricoveri <alejandroricoveri@gmail.com>
#
# Source files
# --------------------------------
#

# Define sources and executable
set (CLIENT_EXEC "ht")
set (SERVER_EXEC "htded")

# Definitions
if (WINDOWS)
  set (HT_OS_WIN32 1)
elseif (MACOSX)
  set (HT_OS_OSX 1)
elseif (LINUX)
  set (HT_OS_LINUX 1)
elseif (BSD)
  set (HT_OS_BSD 1)
endif ()

if (UNIX)
  set (HT_OS_UNIX 1)
endif()

# Source files root directory
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Link against this libraries
set (LIBS m)

# .pk3 files support
if (HT_WITH_ZIP)
  add_definitions (-DNOUNCRYPT)
  list (APPEND INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})  # zlib
  list (APPEND LIBS ${ZLIB_LIBRARIES})
endif()

#
# Client-specific
#
# Include directories
set (INCLUDE_DIRS ${SRC_DIR}/include) # for future use
list (APPEND INCLUDE_DIRS ${SDL_INCLUDE_DIR})    # libSDL
list (APPEND INCLUDE_DIRS ${OPENGL_INCLUDE_DIR}) # OpenGL

# Libraries
set (CLIENT_LIBS ${OPENGL_LIBRARIES}) # OpenGL
list (APPEND CLIENT_LIBS ${SDL_LIBRARY}) # SDL

# X11 hardware gamma
if (HT_WITH_X11GAMMA)
  list (APPEND INCLUDE_DIRS ${X11_xf86vmode_INCLUDE_PATH}) # X11
  list (APPEND CLIENT_LIBS ${X11_Xxf86vm_LIB})
endif()

# Retexturing support
if (HT_WITH_RETEXTURE)
  list (APPEND INCLUDE_DIRS ${JPEG_INCLUDE_DIR}) # libjpeg
  list (APPEND CLIENT_LIBS ${JPEG_LIBRARY}) # jpeg
endif()

# OpenAL
if (HT_WITH_OPENAL)

  # AL driver for QAL
  if (UNIX)
    set (AL_DRIVER libopenal.so)
  endif()

  if (WINDOWS)
    set (AL_DRIVER openal32.dll)
  endif()

  # Necessary definitions
  add_definitions (-DUSE_OPENAL -DDEFAULT_OPENAL_DRIVER="${AL_DRIVER}")

  # OpenAL headers
  list (APPEND INCLUDE_DIRS ${OPENAL_INCLUDE_DIR})

  # OpenAL libraries
  list (APPEND CLIENT_LIBS ${OPENAL_LIBRARY})
endif()

# OGG Vorbis
if (HT_WITH_OGG)
  list (APPEND INCLUDE_DIRS ${OGG_INCLUDE_DIR} ${VORBIS_INCLUDE_DIR})
  list (APPEND CLIENT_LIBS ${OGG_LIBRARY} ${VORBIS_LIBRARY} ${VORBIS_FILE_LIBRARY})
endif()

# Unix specific libraries
if (UNIX)
  # dlopen, dlsym, dlclose, etc ...
  find_package (LibDL REQUIRED)
  list (APPEND INCLUDE_DIRS ${LIBDL_INCLUDE_DIR})
  list (APPEND LIBS ${LIBDL_LIBRARY}) # libdl
endif()

# Include path
include_directories (${INCLUDE_DIRS})

# Configuration file
configure_file (${SRC_DIR}/include/config.h.in ${SRC_DIR}/include/config.h)

#
# Platform-specific backends
#
add_subdirectory (backends)

# Common
add_subdirectory (common)

# Server
add_subdirectory (server)

# Refresher
add_subdirectory (refresh)

# Client
add_subdirectory (client)

# The game itself
add_subdirectory (game)

# Server exec
add_executable (server ${SERVER_EXEC_SRC})

# -DDEDICATED_ONLY for dedicated server
set_target_properties(server PROPERTIES COMPILE_DEFINITIONS "DEDICATED_ONLY")
set_target_properties(server PROPERTIES OUTPUT_NAME "${SERVER_EXEC}")
target_link_libraries (server ${LIBS})

# Client exec
add_executable (client ${CLIENT_EXEC_SRC})
set_target_properties(client PROPERTIES OUTPUT_NAME "${CLIENT_EXEC}")
target_link_libraries(client ${LIBS} ${CLIENT_LIBS})
