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
	${HEADER_DIR}/backend/generic/al.h
	${HEADER_DIR}/backend/generic/qgl.h
	${HEADER_DIR}/backend/generic/gl.h
	${HEADER_DIR}/backend/generic/sdl.h
	${HEADER_DIR}/backend/osx/SDLMain.h
	${HEADER_DIR}/backend/unix/unix.h
	${HEADER_DIR}/backend/unix/prereqs.h
  ${HEADER_DIR}/backend/windows/prereqs.h
	${HEADER_DIR}/backend/windows/resource.h
	${HEADER_DIR}/backend/windows/winquake.h
	${HEADER_DIR}/client/client.h
	${HEADER_DIR}/client/input.h
	${HEADER_DIR}/client/screen.h
	${HEADER_DIR}/client/vid.h
	${HEADER_DIR}/client/console.h
	${HEADER_DIR}/client/keyboard.h
	${HEADER_DIR}/client/ref.h
	${HEADER_DIR}/client/menu/qmenu.h
	${HEADER_DIR}/client/sound/cdaudio.h
	${HEADER_DIR}/client/sound/local.h
	${HEADER_DIR}/client/sound/sound.h
	${HEADER_DIR}/client/sound/vorbis.h
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
	${HEADER_DIR}/server/server.h
 ${HEADER_DIR}/system.h
	${HEADER_DIR}/prereqs.h
	${HEADER_DIR}/config.h

	PARENT_SCOPE
)
