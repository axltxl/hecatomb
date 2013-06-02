#
# Hecatomb
# A portable Quake II client
# http://github.com/alericoveri/hecatomb
#
# CMake build automation scripts
# Author: Alejandro Ricoveri <alejandroricoveri@gmail.com>
#
# Refresher source files
# --------------------------------
#

set (REF_DIR ${SRC_DIR}/refresh )
set (REF_SRC
    ${REF_DIR}/r_draw.c
    ${REF_DIR}/r_image.c
    ${REF_DIR}/r_light.c
    ${REF_DIR}/r_lightmap.c
    ${REF_DIR}/r_main.c
    ${REF_DIR}/r_mesh.c
    ${REF_DIR}/r_misc.c
    ${REF_DIR}/r_model.c
    ${REF_DIR}/r_scrap.c
    ${REF_DIR}/r_surf.c
    ${REF_DIR}/r_warp.c
    ${REF_DIR}/files/md2.c
    ${REF_DIR}/files/pcx.c
    ${REF_DIR}/files/sp2.c
    ${REF_DIR}/files/tga.c
    ${REF_DIR}/files/wal.c
    )

# Include JPEG support
if ( HT_WITH_RETEXTURE )
  list ( APPEND REF_SRC ${REF_DIR}/files/jpeg.c )
endif()

# Export it!
set (REF_SRC ${REF_SRC} PARENT_SCOPE)
