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
 * This file implements the high level part of the Hunk_* memory system
 * This is the memory allocation interface used by the engine for large
 * objects.
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "system.h"

 extern cvar_t *hunk_trace;
 extern cvar_t *hunk_driver;

 // This will only keep the current hunk on use
 // as it's only used for logging when hunk_trace is set to 1
 static void *mbase = NULL;

 /* ========================================================================= */
 void *
 Hunk_Begin ( q_int32_t maxsize )
 {
   if (hunk_trace->value) {
     mbase = Sys_HunkBegin ( maxsize );
     Com_DPrintf ( "> [%p]: %d byte(s) allocated\n", mbase, maxsize );
     return mbase;
   }
   else {
    return Sys_HunkBegin ( maxsize );
  }
 }

 /* ========================================================================= */
 void *
 Hunk_Alloc ( q_int32_t size )
 {
   if (hunk_trace->value)
    Com_DPrintf ( "! [%p]: %d byte(s) claimed\n", mbase, size );
  return Sys_HunkAlloc ( size );
 }

 /* ========================================================================= */
 q_int32_t
 Hunk_End ( void )
 {
   if (hunk_trace->value)
    Com_DPrintf ( "< [%p]: Dismissed\n", mbase );
   return Sys_HunkEnd();
 }

 /* ========================================================================= */
 void
 Hunk_Free ( void *base )
 {
   if (hunk_trace->value)
    Com_DPrintf ( "* [%p]: Deallocated\n", base);
   Sys_HunkFree ( base );
 }


