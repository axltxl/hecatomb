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

 /* ========================================================================= */
 void
 Com_Features ( void )
 {
 #ifndef DEDICATED_ONLY
   printf ( "Features: " );
 #ifdef HT_WITH_OGG
   printf ( " OGG" );
 #endif
 #ifdef HT_WITH_OPENAL
   printf ( " OpenAL" );
 #endif
 #ifdef HT_WITH_ZIP
   printf ( " Zip" );
 #endif
 #ifdef HT_WITH_RETEXTURE
   printf ( " JPEG" );
 #endif
 #ifdef HT_WITH_X11GAMMA
   printf ( " X11Gamma" );
 #endif
   printf ( "\n" );
 #endif /* DEDICATED_ONLY */
   printf ( "Platform: %s\n", HT_OS_NAME );
   printf ( "Architecture: %s\n", HT_ARCH_NAME );
   printf ( "Byte ordering: " );
 #ifdef HT_ENDIAN_BIG
   printf ( "Big endian" );
 #else
   printf ( "Little endian" );
 #endif
   printf ( "\n" );
 }

 /* ========================================================================= */
 void Com_Splash()
 {
   /* Print program information */
   printf ( "%s v%s - %s\n", HT_PRODUCT_NAME, HT_VERSION, HT_URL );
   printf ( "=====================\n" );
   Com_Features();
   printf ( "=====================\n" );
 }
