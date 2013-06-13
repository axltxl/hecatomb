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
 * This file implements the low level part of the Hunk_* memory system
 * Generic implementation based on malloc/free
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "system.h"
 #include "memory.h"

 byte *membase;
 int maxhunksize;
 int curhunksize;

 /* ========================================================================= */
 char *
 Sys_HunkDriver ( void )
 {
   return "stdc-generic";
 }

 /* ========================================================================= */
 void *
 Sys_HunkBegin ( int maxsize )
 {
   maxhunksize = maxsize;
   curhunksize = 0;

   if ( ! (membase = Mem_malloc (maxsize)) ) {
     Sys_Error ( "unable to virtual allocate %d bytes", maxsize );
   }
   else {
    memset (membase, 0, maxsize);
   }
   return membase;
 }

 /* ========================================================================= */
 void *
 Sys_HunkAlloc ( int size )
 {
   byte *buf;

   if ( curhunksize + size > maxhunksize ) {
     Sys_Error ( "Hunk_Alloc overflow" );
   }

   buf = membase + curhunksize;
   curhunksize += size;
   return buf;
 }

 /* ========================================================================= */
 int
 Sys_HunkEnd ( void )
 {
   return curhunksize;
 }

 /* ========================================================================= */
 void
 Sys_HunkFree ( void *base )
 {
   if ( base ) {
     Mem_free ( base );
     base = NULL;
   }
 }

