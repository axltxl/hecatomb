/*
 * Copyright (C) 2012 Yamagi Burmeister
 * Copyright (C) 2010 skuller.net
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
 * Low level, platform depended "qal" API implementation. This files
 * provides functions to load, initialize, shutdown und unload the
 * OpenAL library and connects the "qal" funtion pointers to the
 * OpenAL functions. It shopuld work on Windows and unixoid Systems,
 * other platforms may need an own implementation. This source file
 * was taken from Q2Pro and modified by the YQ2 authors.
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "system.h"
 #include "client/sound/local.h"
 #include "backend/generic/qal.h"

 static ALCcontext *context;
 static ALCdevice *device;
 static cvar_t *al_device;

 /*
  * Gives information over the OpenAL
  * implementation and it's state
  */
 void QAL_SoundInfo()
 {
   Com_Printf ( "OpenAL settings:\n" );
   Com_Printf ( "AL_VENDOR: %s\n", qalGetString ( AL_VENDOR ) );
   Com_Printf ( "AL_RENDERER: %s\n", qalGetString ( AL_RENDERER ) );
   Com_Printf ( "AL_VERSION: %s\n", qalGetString ( AL_VERSION ) );
   Com_Printf ( "AL_EXTENSIONS: %s\n", qalGetString ( AL_EXTENSIONS ) );

   if ( qalcIsExtensionPresent ( NULL, "ALC_ENUMERATE_ALL_EXT" ) ) {
     const char *devs = qalcGetString ( NULL, ALC_ALL_DEVICES_SPECIFIER );
     Com_Printf ( "\nAvailable OpenAL devices:\n" );

     if ( devs == NULL ) {
       Com_Printf ( "- No devices found. Depending on your\n" );
       Com_Printf ( "  platform this may be expected and\n" );
       Com_Printf ( "  doesn't indicate a problem!\n" );
     } else {
       while ( devs && *devs ) {
         Com_Printf ( "- %s\n", devs );
         devs += strlen ( devs ) + 1;
       }
     }
   }

   if ( qalcIsExtensionPresent ( NULL, "ALC_ENUMERATE_ALL_EXT" ) ) {
     const char *devs = qalcGetString ( device, ALC_DEVICE_SPECIFIER );
     Com_Printf ( "\nCurrent OpenAL device:\n" );

     if ( devs == NULL ) {
       Com_Printf ( "- No OpenAL device in use\n" );
     } else {
       Com_Printf ( "- %s\n", devs );
     }
   }
 }

 /*
  * Shuts OpenAL down, frees all context and
  * device handles and unloads the shared lib.
  */
 void
 QAL_Shutdown()
 {
   if ( context ) {
     qalcMakeContextCurrent ( NULL );
     qalcDestroyContext ( context );
     context = NULL;
   }

   if ( device ) {
     qalcCloseDevice ( device );
     device = NULL;
   }
 }

 /*
  * Loads the OpenAL shared lib, creates
  * a context and device handle.
  */
 qboolean
 QAL_Init()
 {
   al_device = Cvar_Get ( "al_device", "", CVAR_ARCHIVE );

   /* Open the OpenAL device */
   Com_Printf ( "Opening OpenAL device: " );
   device = qalcOpenDevice ( al_device->string[0] ? al_device->string : NULL );

   if ( !device ) {
     Com_DPrintf ( "failed\n" );
     QAL_Shutdown();
     return false;
   }

   Com_Printf ( "ok\n" );

   /* Create the OpenAL context */
   Com_Printf ( "Creating OpenAL context: " );
   context = qalcCreateContext ( device, NULL );

   if ( !context ) {
     Com_DPrintf ( "failed\n" );
     QAL_Shutdown();
     return false;
   }

   Com_Printf ( "ok\n" );

   /* Set the created context as current context */
   Com_Printf ( "Making context current: " );

   if ( !qalcMakeContextCurrent ( context ) ) {
     Com_DPrintf ( "failed\n" );
     QAL_Shutdown();
     return false;
   }

   Com_Printf ( "ok\n" );

   /* Print OpenAL informations */
   Com_Printf ( "\n" );
   QAL_SoundInfo();
   Com_Printf ( "\n" );
   return true;
 }
