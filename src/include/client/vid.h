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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
 * USA.
 *
 * =======================================================================
 *
 * ABI to the video oute driver
 *
 * =======================================================================
 */

 #ifndef CL_VID_H
 #define CL_VID_H

 #include "prereqs.h"

 /**
  *
  */
 typedef struct vrect_s {
   int       x, y, width, height;
 } vrect_t;

 /**
  *
  */
 typedef struct {
   int   width, height; /* coordinates from main game */
 } viddef_t;

 extern  viddef_t  viddef; /* global video state */

 /* Video module initialisation, etc */

 /**
  *
  */
 void  VID_Init ( void );

 /**
  *
  */
 void  VID_Shutdown ( void );

 /**
  * This function gets called once just before drawing each frame, and
  * it's sole purpose in life is to check to see if any of the video mode
  * parameters have changed, and if they have to update the refresh
  * and/or video mode to match.
  */
 void  VID_CheckChanges ( void );

 /**
  *
  */
 void  VID_MenuInit ( void );

 /**
  *
  */
 void  VID_MenuDraw ( void );

 /**
  *
  */
 const char *VID_MenuKey ( int );

 /**
  *
  */
 void VID_Printf ( int print_level, char *fmt, ... );

 /**
  *
  */
 void VID_Error ( int err_level, char *fmt, ... );

 /**
  *
  */
 void VID_NewWindow ( int width, int height );

 /**
  *
  */
 qboolean VID_GetModeInfo ( int *width, int *height, int mode );

 #endif /* CL_VID_H */
