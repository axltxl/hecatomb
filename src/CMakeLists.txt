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
list (APPEND INCLUDE_DIRS ${OPENAL_INCLUDE_DIR}) # OpenAL
list (APPEND INCLUDE_DIRS ${OPENGL_INCLUDE_DIR}) # OpenGL

# Include path
include_directories (${INCLUDE_DIRS})

# Link against this libraries
set (LIBS ${ZLIB_LIBRARIES} m dl)

# Client-specific
set (CLIENT_LIBS ${OPENGL_LIBRARIES}) # OpenGL
list (APPEND CLIENT_LIBS ${SDL_LIBRARY}) # libSDL 
list (APPEND CLIENT_LIBS ${OPENAL_LIBRARY}) # OpenAL

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

# Server 
add_executable (${SERVER_EXEC} ${SERVER_EXEC_SRC})
set_target_properties(${SERVER_EXEC} PROPERTIES COMPILE_DEFINITIONS "DEDICATED_ONLY")
target_link_libraries (${SERVER_EXEC} ${LIBS})

# Client exec
add_executable (${CLIENT_EXEC} ${CLIENT_EXEC_SRC})
target_link_libraries(${CLIENT_EXEC} ${LIBS} ${CLIENT_LIBS})
