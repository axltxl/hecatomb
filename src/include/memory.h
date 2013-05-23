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
 * High level part of the Hunk_* memory system
 * This is actually an interface to the low level Hunk_* memory allocator
 * which varies among platforms. See Sys_Hunk* functions @ system.h.
 *
 * =======================================================================
 */

 #ifndef MEM_H
 #define MEM_H

 #include "prereqs.h"

 /**
  * Reserve a huge chunk of memory, but don't commit any yet
  */
 void *Hunk_Begin ( int maxsize );

 /**
  * Commit a portion of the previous allocated base memory
  */
 void *Hunk_Alloc ( int size );

 /**
  * Release the chunk of base memory
  */
 void Hunk_Free ( void *buf );

 /**
  * Release current portion of the previous allocated base memory in use
  */
 int Hunk_End ( void );

 #endif /* MEM_H */
