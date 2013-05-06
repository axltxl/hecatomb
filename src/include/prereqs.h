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
 * Prequisites
 */
 
 #include "config.h"
 #include "common/common.h"
 
 #ifdef HT_OS_WIN32
    #include "backends/win32/prereqs.h"
 #endif
 
 #ifdef HT_OS_UNIX
    #include "backends/unix/prereqs.h"
 #endif
 
 #ifdef HT_OS_LINUX
    #include "backends/linux/prereqs.h"
 #endif
 
 #ifdef HT_OS_OSX
    #include "backends/osx/prereqs.h"
 #endif
 
 #ifdef HT_OS_BSD
    #include "backends/bsd/prereqs.h"
 #endif
 
