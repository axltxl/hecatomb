#
# Source files used by all targets
#

set (COMMON_DIR ${SRC_DIR}/common)
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
    ${COMMON_DIR}/shared/flash.c
    ${COMMON_DIR}/shared/rand.c
    ${COMMON_DIR}/shared/shared.c
    ${COMMON_DIR}/unzip/ioapi.c
    ${COMMON_DIR}/unzip/unzip.c

    PARENT_SCOPE 
    )
