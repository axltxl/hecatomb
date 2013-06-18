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
 * Memory subsystem backend
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "memory.h"

 /* ========================================================================= */
 void
 Mem_mallinfo_f ( void )
 {
 #if HT_HAVE_MALLINFO
   struct mallinfo mi;
   mi = Mem_mallinfo();
 #endif
   Com_Printf ( "============== Memory allocation information ==============\n" );
   Com_Printf ( "Implementation:                         %s\n", HT_MALLOC_IMP );
 #if HT_HAVE_MALLINFO
   Com_Printf ( "Total non-mmapped bytes (arena):        %d\n", mi.arena );
   Com_Printf ( "Number of free chunks (ordblks):        %d\n", mi.ordblks );
   Com_Printf ( "Number of free fastbin blocks (smblks): %d\n", mi.smblks );
   Com_Printf ( "Number of mapped regions (hblks):       %d\n", mi.hblks );
   Com_Printf ( "Bytes in mapped regions (hblkhd):       %d\n", mi.hblkhd );
   Com_Printf ( "Max. total allocated space (usmblks):   %d\n", mi.usmblks );
   Com_Printf ( "Free bytes held in fastbins (fsmblks):  %d\n", mi.fsmblks );
   Com_Printf ( "Total allocated space (uordblks):       %d\n", mi.uordblks );
   Com_Printf ( "Total free space (fordblks):            %d\n", mi.fordblks );
   Com_Printf ( "Topmost releasable block (keepcost):    %d\n", mi.keepcost );
 #endif
 }

 /* ========================================================================= */
 void
 Mem_Init ( void )
 {
   Cmd_AddCommand ( "mallinfo", Mem_mallinfo_f );
 }

