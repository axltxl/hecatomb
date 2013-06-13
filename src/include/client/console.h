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
 * Header file for the console
 *
 * =======================================================================
 */

 #ifndef CL_HEADER_CONSOLE_H
 #define CL_HEADER_CONSOLE_H

 #include "prereqs.h"

 #define NUM_CON_TIMES 4
 #define CON_TEXTSIZE  32768


 /**
  *
  */
 typedef struct {
   qboolean  initialized;

   char  text[CON_TEXTSIZE];
   q_int32_t   current; /* line where next message will be printed */
   q_int32_t   x; /* offset in current line for next print */
   q_int32_t   display; /* bottom of console displays this line */

   q_int32_t   ormask; /* high bit mask for colored characters */

   q_int32_t   linewidth; /* characters across screen */
   q_int32_t   totallines; /* total lines in console scrollback */

   float cursorspeed;

   q_int32_t   vislines;

   float times[NUM_CON_TIMES]; /* cls.realtime time the line was generated */
 } console_t;

 extern  console_t con;

 /**
  * If the line width has changed, reformat the buffer.
  */
 void Con_CheckResize ( void );

 /**
  *
  */
 void Con_Init ( void );

 /**
  * Draws the console with the solid background
  */
 void Con_DrawConsole ( float frac );

 /**
  * Handles cursor positioning, line wrapping, etc All console printing
  * must go through this in order to be logged to disk If no console is
  * visible, the text will appear at the top of the game window
  */
 void Con_Print ( char *txt );

 /**
  *
  */
 void Con_CenteredPrint ( char *text );

 /**
  *
  */
 void Con_Clear_f ( void );

 /**
  * Draws the last few lines of output transparently over the game top
  */
 void Con_DrawNotify ( void );

 /**
  *
  */
 void Con_ClearNotify ( void );

 /**
  *
  */
 void Con_ToggleConsole_f ( void );

 #endif /* CL_HEADER_CONSOLE_H */
