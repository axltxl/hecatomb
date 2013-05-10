#
# Yamagi Quake II
# http://www.yamagi.org/quake2
# http://github.com/yquake2
#
# CMake build automation scripts
# Author: Alejandro Ricoveri <alejandroricoveri@gmail.com>
#
# Source files
# --------------------------------
#

# Define sources and executable
set (CLIENT_EXEC "quake2")
set (SERVER_EXEC "q2ded")

# Definitions
if (WINDOWS)
  add_definitions (-DYQ2_OS_WIN32)
elseif (OSX)
  add_definitions (-DYQ2_OS_OSX) 
elseif (LINUX)
  add_definitions (-DYQ2_OS_LINUX)
elseif (BSD)
  add_definitions (-DYQ2_OS_BSD)
endif ()

if (UNIX)
  add_definitions (-DYQ2_OS_UNIX)
endif()

# Source files root directory
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# CD audio playback
if (YQ2_WITH_CDA)
  add_definitions (-DCDA)
endif()

# Link against this libraries
set (LIBS m)

# .pk3 files support
if (YQ2_WITH_ZIP)
  add_definitions (-DZIP -DNOUNCRYPT)
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
if (YQ2_WITH_X11GAMMA)
  add_definitions (-DX11GAMMA)
  #list (APPEND INCLUDE_DIRS ${X11_INCLUDE_DIR}) # X11
  list (APPEND INCLUDE_DIRS ${X11_xf86vmode_INCLUDE_PATH}) # X11
  #list (APPEND CLIENT_LIBS  ${X11_LIBRARIES}) # X11 libraries
  #list (APPEND CLIENT_LIBS xf86vm) # Xf86vmode library
  list (APPEND CLIENT_LIBS ${X11_Xxf86vm_LIB})
  #message (FATAL_ERROR ${X11_LIBRARIES})
endif()

# Retexturing support
if (YQ2_WITH_RETEXTURE)
  add_definitions (-DRETEXTURE)
  list (APPEND INCLUDE_DIRS ${JPEG_INCLUDE_DIR}) # libjpeg
  list (APPEND CLIENT_LIBS ${JPEG_LIBRARY}) # jpeg
endif()

# OpenAL
if (YQ2_WITH_OPENAL)
  
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
if (YQ2_WITH_OGG)
  add_definitions (-DOGG)
  list (APPEND INCLUDE_DIRS ${OGG_INCLUDE_DIR} ${VORBIS_INCLUDE_DIR})
  list (APPEND CLIENT_LIBS 
    ${OGG_LIBRARY} ${VORBIS_LIBRARY} ${VORBIS_FILE_LIBRARY})
endif()


# System wide assets
if (YQ2_SYSTEMWIDE)
  add_definitions (-DSYSTEMWIDE -DSYSTEMDIR="${YQ2_SYSTEMDIR}")
endif()

# Windows specific libraries
if (WINDOWS)
  # Winsock and WinMM
  list (APPEND LIBS ws2_32 winmm )
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

# Set output directory
set (OUTPUT_DIR ${PROJECT_SOURCE_DIR}/bin)
if (ARCH_32)
  set (OUTPUT_DIR "${OUTPUT_DIR}/x86")
else()
  set (OUTPUT_DIR "${OUTPUT_DIR}/x64")
endif()

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

# Set output directory
set_target_properties (client server 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
