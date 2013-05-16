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

 #define SFF_INPACK 0x20

 extern int file_from_pak;

 typedef int fileHandle_t;

 typedef enum {
   FS_READ,
   FS_WRITE,
   FS_APPEND
 } fsMode_t;

 typedef enum {
   FS_SEEK_CUR,
   FS_SEEK_SET,
   FS_SEEK_END
 } fsOrigin_t;

 typedef enum {
   FS_SEARCH_PATH_EXTENSION,
   FS_SEARCH_BY_FILTER,
   FS_SEARCH_FULL_PATH
 } fsSearchType_t;

 void FS_Startup ( void );
 void FS_Shutdown ( void );
 void FS_DPrintf ( const char *format, ... );
 FILE *FS_FileForHandle ( fileHandle_t f );
 int FS_FOpenFile ( const char *name, fileHandle_t *f, fsMode_t mode );
 void FS_FCloseFile ( fileHandle_t f );
 int FS_Read ( void *buffer, int size, fileHandle_t f );
 int FS_FRead ( void *buffer, int size, int count, fileHandle_t f );
 int FS_Write ( const void *buffer, int size, fileHandle_t f );
 void FS_Seek ( fileHandle_t f, int offset, fsOrigin_t origin );
 int FS_FTell ( fileHandle_t f );
 int FS_Tell ( fileHandle_t f );
 qboolean FS_FileExists ( char *path );
 void FS_CopyFile ( const char *srcPath, const char *dstPath );
 void FS_RenameFile ( const char *oldPath, const char *newPath );
 void FS_DeleteFile ( const char *path );
 int FS_GetFileList ( const char *path, const char *extension,
                      char *buffer, int size, fsSearchType_t searchType );
 char **FS_ListPak ( char *find, int *num );
 char **FS_ListFiles ( char *findname, int *numfiles,
                       unsigned musthave, unsigned canthave );
 char **FS_ListFiles2 ( char *findname, int *numfiles,
                        unsigned musthave, unsigned canthave );
 void FS_FreeList ( char **list, int nfiles );

 void FS_InitFilesystem ( void );
 void FS_SetGamedir ( char *dir );
 char *FS_Gamedir ( void );
 char *FS_NextPath ( char *prevpath );
 void FS_ExecAutoexec ( void );
 int FS_LoadFile ( char *path, void **buffer );

 /* a null buffer will just return the file length without loading */
 /* a -1 length is not present */

 /* properly handles partial reads */

 void FS_FreeFile ( void *buffer );
 void FS_CreatePath ( char *path );

 #endif /* FS_H */
