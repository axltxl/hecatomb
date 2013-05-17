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
 * Filesystem API
 *
 * =======================================================================
 */

 #ifndef FS_H
 #define FS_H

 #include "prereqs.h"

/**
 * A handle to a file
 */
 typedef int fileHandle_t;

/**
 * File access mode
 */
 typedef enum {
   FS_READ,
   FS_WRITE,
   FS_APPEND
 } fsMode_t;

/**
 *
 */
 typedef enum {
   FS_SEEK_CUR,
   FS_SEEK_SET,
   FS_SEEK_END
 } fsOrigin_t;

/**
 * Search criteria
 */
 typedef enum {
   FS_SEARCH_PATH_EXTENSION,
   FS_SEARCH_BY_FILTER,
   FS_SEARCH_FULL_PATH
 } fsSearchType_t;

/**
 * Boot up the filesystem
 */
 void FS_Startup ( void );

 /**
  * Shut down the filesystem
  */
 void FS_Shutdown ( void );

 /**
  * Finds the file in the search path. Returns filesize and an open FILE *. Used
  * for streaming data out of either a pak file or a separate file.
  */
 int FS_FOpenFile ( const char *name, fileHandle_t *f, fsMode_t mode );

 /**
  * Other dll's can't just call fclose() on files returned by FS_FOpenFile.
  */
 void FS_FCloseFile ( fileHandle_t f );

 /**
  * Read a chunk of data from a file
  */
 int FS_Read ( void *buffer, int size, fileHandle_t f );

 /**
  * Read a chunk of data from a file.
  * Properly handles partial reads of size up to count times. No error if it
  * can't read.
  */
 int FS_FRead ( void *buffer, int size, int count, fileHandle_t f );

 /**
  * Delete a file
  */
 void FS_DeleteFile ( const char *path );

 /**
  * Create a list of files that match a criteria.
  */
 char **FS_ListFiles ( char *findname, int *numfiles,
                       unsigned musthave, unsigned canthave );


 /**
  * Create a list of files that match a criteria.
  * Searchs are relative to the game directory and use all the search paths
  * including .pak and .pk3 files.
  */
 char **FS_ListFiles2 ( char *findname, int *numfiles,
                        unsigned musthave, unsigned canthave );

 /**
  * Free list of files created by FS_ListFiles().
  */
 void FS_FreeList ( char **list, int nfiles );

 /**
  * Setup the filesystem cvars and initial (game) directory
  */
 void FS_InitFilesystem ( void );

 /**
  * Sets the gamedir and path to a different directory.
  */
 void FS_SetGamedir ( char *dir );

 /**
  * Get game directory
  */
 char *FS_Gamedir ( void );

 /**
  * Allows enumerating all of the directories in the search path.
  */
 char *FS_NextPath ( char *prevpath );

 /**
  * Execute autoexec.cfg
  */
 void FS_ExecAutoexec ( void );

 /**
  * Filename are relative to the quake search path. A null buffer will just
  * return the file length without loading. It returns -1 if file doesn't exists.
  */
 int FS_LoadFile ( char *path, void **buffer );


 /**
  * Free buffer created from file
  */
 void FS_FreeFile ( void *buffer );

 /**
  * Creates any directories needed to store the given filename.
  */
 void FS_CreatePath ( char *path );

 #endif /* FS_H */
