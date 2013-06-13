#
# Hecatomb
# A portable Quake II client
# http://github.com/alericoveri/hecatomb
#
# CMake build automation scripts
# Author: Alejandro Ricoveri <alejandroricoveri@gmail.com>
#
# Source files
# --------------------------------
#

#
# Define sources and executable
# ---------------------

set (CLIENT_EXEC "htq2")
set (SERVER_EXEC "htq2d")

#
# Definitions
# ---------------------
#

# Windows
if (WINDOWS)
  set (HT_OS_WINDOWS 1)
endif()

# UNIX
if (UNIX)

  set (HT_OS_UNIX 1)

  # BSD variants
  if (BSD)
    set (HT_OS_BSD 1)
    if (OPENBSD)
      set (HT_OS_OPENBSD 1)
    endif()
    if (FREEBSD)
      set (HT_OS_FREEBSD 1)
    endif()
  endif ()

  # Linux
  if (LINUX)
    set (HT_OS_LINUX 1)
  endif()

  # Apple OSX
  if (OSX)
    set (HT_OS_OSX 1)
  endif()

endif()

# An unknown operating system
if (UNK_OS)
  set (HT_OS_UNKNOWN 1)
endif()

# Source files root directory
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Link against this libraries
set (LIBS m)

# Include directories
set (INCLUDE_DIRS ${SRC_DIR}/include) # for future use

# .pk3 files support
if (HT_WITH_ZIP)
  list (APPEND INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})  # zlib
  list (APPEND LIBS ${ZLIB_LIBRARIES})
endif()

# Jemalloc as the memory allocator
if (HT_MEM_JEMALLOC)
  list (APPEND INCLUDE_DIRS ${JEMALLOC_INCLUDE_DIRS})
  list (APPEND LIBS ${JEMALLOC_LIBRARIES})
endif()

#
# Client-specific
# ---------------------
#

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

  # OpenAL headers
  list (APPEND INCLUDE_DIRS ${OPENAL_INCLUDE_DIR})

  # OpenAL libraries
  list (APPEND CLIENT_LIBS ${OPENAL_LIBRARY})

endif()

# OGG Vorbis
if (HT_WITH_OGG)
  list (APPEND INCLUDE_DIRS ${OGG_INCLUDE_DIR} ${VORBIS_INCLUDE_DIR})
  list (APPEND CLIENT_LIBS
    ${OGG_LIBRARY} ${VORBIS_LIBRARY} ${VORBIS_FILE_LIBRARY})
endif()

# Windows specific libraries
if (WINDOWS)
  # Winsock and WinMM
  list (APPEND LIBS ws2_32 winmm)
  list (APPEND CLIENT_LIBS -mwindows)
endif()

# Unix specific libraries
if (UNIX)

  # dl
  list (APPEND INCLUDE_DIRS ${LIBDL_INCLUDE_DIR})
  list (APPEND LIBS ${LIBDL_LIBRARY}) # libdl

  # execinfo
  if (HT_HAVE_EXECINFO)
    list (APPEND INCLUDE_DIRS ${LIBEXECINFO_INCLUDE_DIR})
    list (APPEND LIBS ${LIBEXECINFO_LIBRARIES}) # libexecinfo
  endif()
endif()

# Include path
include_directories (${INCLUDE_DIRS})

# Add headers to the project
add_subdirectory (include)

# Set output directory
set (OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin/${ARCH}")

#
# Platform-specific backends
# ---------------------
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

# Configuration file
# ---------------------
configure_file (${SRC_DIR}/include/config.h.in ${SRC_DIR}/include/config.h)

# -DDEDICATED_ONLY for dedicated server
# ---------------------
set_target_properties(server PROPERTIES COMPILE_DEFINITIONS "DEDICATED_ONLY")
set_target_properties(server PROPERTIES OUTPUT_NAME "${SERVER_EXEC}")
target_link_libraries (server ${LIBS})

# Client exec
# ---------------------
add_executable (client ${CLIENT_EXEC_SRC} ${HEADERS})
set_target_properties(client PROPERTIES OUTPUT_NAME "${CLIENT_EXEC}")
target_link_libraries(client ${LIBS} ${CLIENT_LIBS})

# Set output directory
# ---------------------
set_target_properties (client server
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# Install
# ---------------------
#
if ( NOT WINDOWS )
  install (TARGETS client server RUNTIME DESTINATION bin)
endif()
