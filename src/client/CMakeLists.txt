set (CLIENT_DIR ${SRC_DIR}/client)
set (
    CLIENT_SRC

    ${CLIENT_DIR}/cl_cin.c
    ${CLIENT_DIR}/cl_console.c
    ${CLIENT_DIR}/cl_download.c
    ${CLIENT_DIR}/cl_effects.c
    ${CLIENT_DIR}/cl_entities.c
    ${CLIENT_DIR}/cl_input.c
    ${CLIENT_DIR}/cl_inventory.c
    ${CLIENT_DIR}/cl_keyboard.c
    ${CLIENT_DIR}/cl_lights.c
    ${CLIENT_DIR}/cl_main.c
    ${CLIENT_DIR}/cl_network.c
    ${CLIENT_DIR}/cl_parse.c
    ${CLIENT_DIR}/cl_particles.c
    ${CLIENT_DIR}/cl_prediction.c
    ${CLIENT_DIR}/cl_screen.c
    ${CLIENT_DIR}/cl_tempentities.c
    ${CLIENT_DIR}/cl_view.c
    ${CLIENT_DIR}/menu/menu.c
    ${CLIENT_DIR}/menu/qmenu.c
    ${CLIENT_DIR}/menu/videomenu.c
    ${CLIENT_DIR}/sound/ogg.c
    ${CLIENT_DIR}/sound/openal.c
    ${CLIENT_DIR}/sound/sound.c
    ${CLIENT_DIR}/sound/wave.c
    )
set (CLIENT_EXEC_SRC
    
    ${COMMON_SRC}
    ${BACKEND_CLIENT_SRC}
    ${CLIENT_SRC}
    ${SERVER_SRC}
    ${REF_SRC}

    PARENT_SCOPE
    )
