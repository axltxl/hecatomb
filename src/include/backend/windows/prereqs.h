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
 * Windows Prequisites
 */
 
 #ifndef WIN_PREREQS_H
 #define WIN_PREREQS_H
 
 #include "prereqs.h"

 #define WIN32_MEAN_AND_LEAN
 
 /* Require Win XP or higher */
 #define _WIN32_WINNT 0x0501
 
 #include <windows.h>
 #include <winsock2.h>
 #include <ws2tcpip.h>
 #include <wsipx.h>
 
 #include <float.h>
 #include <fcntl.h>
 #include <direct.h>
 #include <io.h>
 #include <conio.h>
 #include <shlobj.h>

 #endif /* WIN_PREREQS_H */

