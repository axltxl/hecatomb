/*
 * Copyright (C) 1997-2001 Id Software, Inc.
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
 * Main header file for the client
 *
 * =======================================================================
 */

 #ifndef SYSTEM_H
 #define SYSTEM_H

 #include "prereqs.h"

/* NON-PORTABLE SYSTEM SERVICES */

 void Sys_Init ( void );
 void Sys_UnloadGame ( void );
 void *Sys_GetGameAPI ( void *parms );

 char *Sys_ConsoleInput ( void );
 void Sys_ConsoleOutput ( char *string );
 void Sys_SendKeyEvents ( void );
 void Sys_Error ( char *error, ... );
 void Sys_Quit ( void );
 char *Sys_GetHomeDir ( void );

 void Sys_FreeLibrary ( void *handle );
 void *Sys_LoadLibrary ( const char *path, const char *sym, void **handle );
 void *Sys_GetProcAddress ( void *handle, const char *sym );

 #endif /* SYSTEM_H */
