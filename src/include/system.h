/*
 * Copyright (C) 2013 Alejandro Ricoveri
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

 /**
  * Boot up system implementation
  */
 void Sys_Init ( void );

  /**
   * Loads the game dll
   */
 void *Sys_GetGameAPI ( void *parms );

 /**
  * Unloads game DLL
  */
 void Sys_UnloadGame ( void );

 /**
  * Read from (not necessarily) stdin
  */
 char *Sys_ConsoleInput ( void );

 /**
  * Print to (not necessarily) stdout
  */
 void Sys_ConsoleOutput ( char *string );

 /**
  * Grab input from backend (this is the main capture function called each frame)
  */
 void Sys_SendKeyEvents ( void );

 /**
  * Print some error
  */
 void Sys_Error ( char *error, ... );

 /**
  * Shut down the whole thing
  */
 void Sys_Quit ( void );

 /**
  * Get user home directory (e.g. /home/alericoveri on unix systems)
  */
 char *Sys_GetHomeDir ( void );

 /**
  * Load a dynamic library (e.g. dlopen on unix systems)
  */
 void *Sys_LoadLibrary ( const char *path, const char *sym, void **handle );

  /**
   * Release a dynamic library
   */
 void Sys_FreeLibrary ( void *handle );

 /**
  * Get a pointer to a dynamic library function
  */
 void *Sys_GetProcAddress ( void *handle, const char *sym );

 /**
  * pass in an attribute mask of things you wish to REJECT
  */
 char *Sys_FindFirst ( char *path, unsigned musthave, unsigned canthave );

 /**
  *
  */
 char *Sys_FindNext ( unsigned musthave, unsigned canthave );

 /**
  *
  */
 void Sys_FindClose ( void );

 /**
  * Get time (in milliseconds) since last frame
  */
 int Sys_Milliseconds ( void );

 /**
  * Create a directory
  */
 void Sys_Mkdir ( char *path );

 /**
  * Get current working directory
  */
 char *Sys_GetCurrentDirectory ( void );

 /**
  * Returns the name of the low level Hunk memory allocator
  * currently in use
  */
 char *Sys_HunkDriver ( void );

 /**
  * Reserve a huge chunk of base memory, but don't commit any yet
  */
 void * Sys_HunkBegin ( int maxsize );

 /**
  * Commit a portion of the previous allocated base memory
  */
 void *Sys_HunkAlloc ( int size );

 /**
  * Release current portion of the previous allocated base memory in use
  */
 int Sys_HunkEnd ( void );

 /**
  * Release the chunk of base memory
  */
 void Sys_HunkFree ( void *base );

 #endif /* SYSTEM_H */
