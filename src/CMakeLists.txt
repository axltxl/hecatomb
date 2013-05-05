#
# Hecatomb
# A Quake II convolution  
# Copyright (c) 2013, Alejandro Ricoveri
#
# CMake build script
#

#
# Source files
# --------------------------------
#

# Define sources and executable
set (CLIENT_EXEC "ht")
set (SERVER_EXEC "htded")

# Definitions
if (WINDOWS)
  add_definitions (-DHT_OS_WIN32)
elseif (MACOSX)
  add_definitions (-DHT_OS_OSX)
  add_definitions (-DHT_OS_UNIX)
elseif (LINUX)
  add_definitions (-DHT_OS_LINUX)
  add_definitions (-DHT_OS_UNIX)
else()
  add_definitions (-DHT_OS_UNIX)
endif ()

# zlib necessary definitions
add_definitions (-DZIP -DNOUNCRYPT)

# Source files root directory
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Include directories
set (INCLUDE_DIRS ${SRC_DIR}/include)
list (APPEND INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})  # zlib
list (APPEND INCLUDE_DIRS ${SDL_INCLUDE_DIR})    # libSDL
list (APPEND INCLUDE_DIRS ${OPENGL_INCLUDE_DIR}) # OpenGL

# Include path
include_directories (${INCLUDE_DIRS})

# Link against this libraries
set (LIBS ${ZLIB_LIBRARIES} m)

# Client-specific
set (CLIENT_LIBS ${OPENGL_LIBRARIES}) # OpenGL
list (APPEND CLIENT_LIBS ${SDL_LIBRARY}) # SDL 

# OpenAL
if (UNIX)
  set (AL_DRIVER libopenal.so)
endif()
add_definitions (-DUSE_OPENAL -DDEFAULT_OPENAL_DRIVER="${AL_DRIVER}")

# OpenAL headers
list (APPEND INCLUDE_DIRS ${OPENAL_INCLUDE_DIR})

# OpenAL libraries 
list (APPEND CLIENT_LIBS ${OPENAL_LIBRARY})

# OGG Vorbis
add_definitions (-DOGG)
list (APPEND INCLUDE_DIRS ${OGG_INCLUDE_DIR} ${VORBIS_INCLUDE_DIR})
list (APPEND CLIENT_LIBS ${OGG_LIBRARY} ${VORBIS_LIBRARY} ${VORBIS_FILE_LIBRARY})


if (UNIX)
  
  # dlopen, dlsym, dlclose, etc ...
  list (APPEND LIBS dl) # libdl

  # X11 hardware gamma
  if (YQ2_X11GAMMA)
    add_definitions (-DX11GAMMA)
  endif()

  # System wide assets
  if (YQ2_SYSTEMWIDE)
    add_definitions (-DSYSTEMWIDE -DSYSTEMDIR="${YQ2_SYSTEMDIR}")
  endif()
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
set_target_properties(server PROPERTIES COMPILE_DEFINITIONS "DEDICATED_ONLY")
set_target_properties(server PROPERTIES OUTPUT_NAME "${SERVER_EXEC}") 
target_link_libraries (server ${LIBS})

# Client exec
add_executable (client ${CLIENT_EXEC_SRC})
set_target_properties(client PROPERTIES OUTPUT_NAME "${CLIENT_EXEC}") 
target_link_libraries(client ${LIBS} ${CLIENT_LIBS})
