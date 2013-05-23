#
# Hecatomb
# A Quake II Engine Extension
# http://github.com/alericoveri/hecatomb
#
# CMake build automation scripts
# Author: Alejandro Ricoveri <alejandroricoveri@gmail.com>
#
# Header files
# --------------------------------
#

# Base directory
set (HEADER_DIR ${SRC_DIR}/include)

set (
  HEADERS

  ${HEADER_DIR}/backend/generic/glwindow.h
  ${HEADER_DIR}/backend/generic/input.h
  ${HEADER_DIR}/backend/generic/qal.h
  ${HEADER_DIR}/backend/generic/qgl.h
  ${HEADER_DIR}/backend/generic/gl.h
  ${HEADER_DIR}/backend/generic/sdl.h
  ${HEADER_DIR}/backend/osx/SDLMain.h
  ${HEADER_DIR}/backend/unix/unix.h
  ${HEADER_DIR}/backend/unix/prereqs.h
  ${HEADER_DIR}/backend/windows/prereqs.h
  ${HEADER_DIR}/backend/windows/resource.h
  ${HEADER_DIR}/backend/windows/winquake.h
  ${HEADER_DIR}/client.h
  ${HEADER_DIR}/client/input.h
  ${HEADER_DIR}/client/screen.h
  ${HEADER_DIR}/client/vid.h
  ${HEADER_DIR}/client/console.h
  ${HEADER_DIR}/client/keyboard.h
  ${HEADER_DIR}/client/ref.h
  ${HEADER_DIR}/client/menu/qmenu.h
  ${HEADER_DIR}/client/sound/local.h
  ${HEADER_DIR}/client/sound/sound.h
  ${HEADER_DIR}/client/sound/vorbis.h
  ${HEADER_DIR}/game.h
  ${HEADER_DIR}/game/local.h
  ${HEADER_DIR}/game/savegame/tables/clientfields.h
  ${HEADER_DIR}/game/savegame/tables/gamefunc_decs.h
  ${HEADER_DIR}/game/savegame/tables/gamemmove_decs.h
  ${HEADER_DIR}/game/savegame/tables/levelfields.h
  ${HEADER_DIR}/game/savegame/tables/fields.h
  ${HEADER_DIR}/game/savegame/tables/gamefunc_list.h
  ${HEADER_DIR}/game/savegame/tables/gamemmove_list.h
  ${HEADER_DIR}/game/monster/berserker/berserker.h
  ${HEADER_DIR}/game/monster/boss3/boss31.h
  ${HEADER_DIR}/game/monster/boss3/boss32.h
  ${HEADER_DIR}/game/monster/chick/chick.h
  ${HEADER_DIR}/game/monster/float/float.h
  ${HEADER_DIR}/game/monster/gladiator/gladiator.h
  ${HEADER_DIR}/game/monster/hover/hover.h
  ${HEADER_DIR}/game/monster/insane/insane.h
  ${HEADER_DIR}/game/monster/misc/player.h
  ${HEADER_DIR}/game/monster/parasite/parasite.h
  ${HEADER_DIR}/game/monster/supertank/supertank.h
  ${HEADER_DIR}/game/monster/boss2/boss2.h
  ${HEADER_DIR}/game/monster/brain/brain.h
  ${HEADER_DIR}/game/monster/flipper/flipper.h
  ${HEADER_DIR}/game/monster/flyer/flyer.h
  ${HEADER_DIR}/game/monster/gunner/gunner.h
  ${HEADER_DIR}/game/monster/infantry/infantry.h
  ${HEADER_DIR}/game/monster/medic/medic.h
  ${HEADER_DIR}/game/monster/mutant/mutant.h
  ${HEADER_DIR}/game/monster/soldier/soldier.h
  ${HEADER_DIR}/game/monster/tank/tank.h
  ${HEADER_DIR}/common/common.h
  ${HEADER_DIR}/common/crc.h
  ${HEADER_DIR}/common/files.h
  ${HEADER_DIR}/common/glob.h
  ${HEADER_DIR}/common/shared.h
  ${HEADER_DIR}/common/zone.h
  ${HEADER_DIR}/common/unzip/ioapi.h
  ${HEADER_DIR}/common/unzip/unzip.h
  ${HEADER_DIR}/refresh/local.h
  ${HEADER_DIR}/refresh/model.h
  ${HEADER_DIR}/refresh/constants/anorms.h
  ${HEADER_DIR}/refresh/constants/anormtab.h
  ${HEADER_DIR}/refresh/constants/warpsin.h
  ${HEADER_DIR}/server.h
  ${HEADER_DIR}/system.h
  ${HEADER_DIR}/prereqs.h
  ${HEADER_DIR}/filesystem.h
  ${HEADER_DIR}/memory.h
  ${HEADER_DIR}/config.h

  PARENT_SCOPE
)
