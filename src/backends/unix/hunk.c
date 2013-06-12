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
 * Unix implementation
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "system.h"
 #include "backend/unix/prereqs.h"

 byte *membase;
 q_int32_t maxhunksize;
 q_int32_t curhunksize;

 /* ========================================================================= */
 char *
 Sys_HunkDriver ( void )
 {
   return "mmap-unix";
 }

 /* ========================================================================= */
 void *
 Sys_HunkBegin ( q_int32_t maxsize )
 {
   /* reserve a huge chunk of memory, but don't commit any yet */
   maxhunksize = maxsize + sizeof ( q_int32_t );
   curhunksize = 0;
   membase = mmap ( 0, maxhunksize, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );

   if ( ( membase == NULL ) || ( membase == ( byte * ) - 1 ) ) {
     Sys_Error ( "unable to virtual allocate %d bytes", maxsize );
   }

   * ( ( q_int32_t * ) membase ) = curhunksize;
   return membase + sizeof ( q_int32_t );
 }

 /* ========================================================================= */
 void *
 Sys_HunkAlloc ( q_int32_t size )
 {
   byte *buf;
   /* round to cacheline */
   size = ( size + 31 ) & ~31;

   if ( curhunksize + size > maxhunksize ) {
     Sys_Error ( "Hunk_Alloc overflow" );
   }

   buf = membase + sizeof ( q_int32_t ) + curhunksize;
   curhunksize += size;
   return buf;
 }

 /* ========================================================================= */
 q_int32_t
 Sys_HunkEnd ( void )
 {
   byte *n = NULL;
 #ifdef HT_OS_LINUX
   n = ( byte * ) mremap ( membase, maxhunksize, curhunksize + sizeof ( q_int32_t ), 0 );
 #elif defined(HT_OS_FREEBSD)
   size_t old_size = maxhunksize;
   size_t new_size = curhunksize + sizeof ( q_int32_t );
   void *unmap_base;
   size_t unmap_len;
   new_size = round_page ( new_size );
   old_size = round_page ( old_size );

   if ( new_size > old_size ) {
     n = 0; /* error */
   } else if ( new_size < old_size ) {
     unmap_base = ( caddr_t ) ( membase + new_size );
     unmap_len = old_size - new_size;
     n = munmap ( unmap_base, unmap_len ) + membase;
   }

 #else
 #ifndef round_page
 #define round_page(x) (((size_t)(x) + (page_size - 1)) / page_size) * \
   page_size
 #endif
   size_t old_size = maxhunksize;
   size_t new_size = curhunksize + sizeof ( q_int32_t );
   void *unmap_base;
   size_t unmap_len;
   q_int32_t page_size;
   page_size = sysconf ( _SC_PAGESIZE );

   if ( page_size == -1 ) {
     Sys_Error ( "Hunk_End: sysconf _SC_PAGESIZE failed (%d)", errno );
   }

   new_size = round_page ( new_size );
   old_size = round_page ( old_size );

   if ( new_size > old_size ) {
     n = 0; /* error */
   } else if ( new_size < old_size ) {
     unmap_base = ( caddr_t ) ( membase + new_size );
     unmap_len = old_size - new_size;
     n = munmap ( unmap_base, unmap_len ) + membase;
   }

 #endif

   if ( n != membase ) {
     Sys_Error ( "Hunk_End: Could not remap virtual block (%d)", errno );
   }

   * ( ( q_int32_t * ) membase ) = curhunksize + sizeof ( q_int32_t );
   return curhunksize;
 }

 /* ========================================================================= */
 void
 Sys_HunkFree ( void *base )
 {
   byte *m;

   if ( base ) {
     m = ( ( byte * ) base ) - sizeof ( q_int32_t );

     if ( munmap ( m, * ( ( q_int32_t * ) m ) ) ) {
       Sys_Error ( "Hunk_Free: munmap failed (%d)", errno );
     }
   }
 }
