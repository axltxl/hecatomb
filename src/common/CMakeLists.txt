#
# Yamagi Quake II
# http://www.yamagi.org/quake2
# http://github.com/yquake2
#
# CMake build automation scripts
# Author: Alejandro Ricoveri <alejandroricoveri@gmail.com>
#
# Source files used by all targets
# --------------------------------
#

# Set base directory
set (COMMON_DIR ${SRC_DIR}/common)

# Shared sources
set (
  COMMON_SHARED_SRC

  ${COMMON_DIR}/shared/flash.c
  ${COMMON_DIR}/shared/rand.c
  ${COMMON_DIR}/shared/shared.c
)

# All common sources
set (
  COMMON_SRC

  ${COMMON_DIR}/argproc.c
  ${COMMON_DIR}/clientserver.c
  ${COMMON_DIR}/collision.c
  ${COMMON_DIR}/crc.c
  ${COMMON_DIR}/cmdparser.c
  ${COMMON_DIR}/cvar.c
  ${COMMON_DIR}/filesystem.c
  ${COMMON_DIR}/glob.c
  ${COMMON_DIR}/md4.c
  ${COMMON_DIR}/movemsg.c
  ${COMMON_DIR}/misc.c
  ${COMMON_DIR}/netchan.c
  ${COMMON_DIR}/pmove.c
  ${COMMON_DIR}/szone.c
  ${COMMON_DIR}/zone.c  
  ${COMMON_SHARED_SRC}
)

# Add some specific sources for .pk3 file support
if (YQ2_WITH_ZIP)
  list (APPEND COMMON_SRC ${COMMON_DIR}/unzip/ioapi.c ${COMMON_DIR}/unzip/unzip.c)
endif()

# Export the whole thing
set (COMMON_SRC ${COMMON_SRC} PARENT_SCOPE)
set (COMMON_SHARED_SRC ${COMMON_SHARED_SRC} PARENT_SCOPE)
