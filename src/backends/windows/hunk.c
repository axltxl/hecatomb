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
 * This file implements the low level part of the Hunk_* memory system
 * Windows implementation
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "system.h"
 #include "backend/windows/winquake.h"

 byte *membase;
 int hunkcount;
 int maxhunksize;
 int curhunksize;

 /* ========================================================================= */
 char *
 Sys_HunkDriver ( void )
 {
   return "VirtualAlloc-windows";
 }

 /* ========================================================================= */
 void *
 Sys_HunkBegin ( int maxsize )
 {
   curhunksize = 0;
   maxhunksize = maxsize;
   membase = VirtualAlloc ( NULL, maxsize, MEM_RESERVE, PAGE_NOACCESS );

   if ( !membase ) {
     Sys_Error ( "VirtualAlloc reserve failed" );
   }
   return ( void * ) membase;
 }

 /* ========================================================================= */
 void *
 Sys_HunkAlloc ( int size )
 {
   void *buf;

   /* round to cacheline */
   size = ( size + 31 ) & ~31;

   /* commit pages as needed */
   buf = VirtualAlloc ( membase, curhunksize + size, MEM_COMMIT, PAGE_READWRITE );

   if ( !buf ) {
     FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                     NULL, GetLastError(), MAKELANGID ( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                     ( LPTSTR ) &buf, 0, NULL );
     Sys_Error ( "VirtualAlloc commit failed.\n%s", buf );
   }

   curhunksize += size;

   if ( curhunksize > maxhunksize ) {
     Sys_Error ( "Hunk_Alloc overflow" );
   }

   return ( void * ) ( membase + curhunksize - size );
 }

 /* ========================================================================= */
 int
 Sys_HunkEnd ( void )
 {
   hunkcount++;
   return curhunksize;
 }

 /* ========================================================================= */
 void
 Sys_HunkFree ( void *base )
 {
   if ( base ) {
     VirtualFree ( base, 0, MEM_RELEASE );
   }
   hunkcount--;
 }

