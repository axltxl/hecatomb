#
# Hecatomb
# A Quake II convolution  
# Copyright (c) 2013, Alejandro Ricoveri
#
# CMake build script
#

set (SERVER_DIR ${SRC_DIR}/server)
set (
    SERVER_SRC

    ${SERVER_DIR}/sv_cmd.c
    ${SERVER_DIR}/sv_conless.c
    ${SERVER_DIR}/sv_entities.c
    ${SERVER_DIR}/sv_game.c
    ${SERVER_DIR}/sv_init.c
    ${SERVER_DIR}/sv_main.c
    ${SERVER_DIR}/sv_save.c
    ${SERVER_DIR}/sv_send.c
    ${SERVER_DIR}/sv_user.c
    ${SERVER_DIR}/sv_world.c
    )
set (SERVER_EXEC_SRC
    
    ${COMMON_SRC}
    ${BACKEND_SERVER_SRC} 
    ${SERVER_SRC}

    PARENT_SCOPE
    )

# Export the whole thing
set (SERVER_SRC ${SERVER_SRC} PARENT_SCOPE)
