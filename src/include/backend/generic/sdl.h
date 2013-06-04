/*
 * Copyright (C) 2013 Alejandro Ricoveri
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * SDL backend (platform-specific)
 *
 * =======================================================================
 */

 #ifndef SDL_WRAPPER_H
 #define SDL_WRAPPER_H

 #include "prereqs.h"

 #ifdef HT_USE_SDL2
 # ifdef HT_OS_WINDOWS
 #  include "SDL2/SDL.h"
 # elif defined(HT_OS_OSX)
 #  include <SDL2/SDL.h>
 # endif
 #else
 # ifdef HT_OS_WINDOWS
 #  include "SDL/SDL.h"
 # elif defined(HT_OS_OSX)
 #  include <SDL/SDL.h>
 # endif
 #endif
 #ifdef HT_OS_UNIX
 // Wonderful UNIX
 # include <SDL.h>
 #endif

 #endif /* SDL_WRAPPER_H */
