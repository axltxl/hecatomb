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
 * Header file to the zone malloc
 *
 * =======================================================================
 */

 #ifndef CO_ZONE_H
 #define CO_ZONE_H

 #include "prereqs.h"

 /**
  *
  */
 typedef struct zhead_s {
   struct zhead_s  *prev, *next;
   q_int16_t magic;
   q_int16_t tag; /* for group free */
   q_int32_t   size;
 } zhead_t;

 /**
  * Get zone malloc statistics
  */
 void Z_Stats_f ( void );

 /**
  * Free some mem
  */
 void Z_Free ( void *ptr );

 /**
  * Allocate some mem
  */
 void *Z_Malloc ( q_int32_t size );        /* returns 0 filled memory */

/**
  * Allocate some tagged mem
  */
 void *Z_TagMalloc ( q_int32_t size, q_int32_t tag );

 /**
  * Free all tags
  */
 void Z_FreeTags ( q_int32_t tag );

 #endif /* CO_ZONE_H */
