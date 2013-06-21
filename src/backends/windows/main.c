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
 * Windows main function. Containts the
 * initialization code and the main loop
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "backend/windows/prereqs.h"
 #include "backend/windows/winquake.h"
 #include "system.h"

 #define MAX_NUM_ARGVS 128

 unsigned int sys_msg_time;

 #ifndef DEDICATED_ONLY
 int argc;
 char *argv[MAX_NUM_ARGVS];

 /* ======================================================================= */
 void
 ParseCommandLine ( LPSTR lpCmdLine )
 {
   argc = 1;
   argv[0] = "exe";

   while ( *lpCmdLine && ( argc < MAX_NUM_ARGVS ) ) {
     while ( *lpCmdLine && ( ( *lpCmdLine <= 32 ) || ( *lpCmdLine > 126 ) ) ) {
       lpCmdLine++;
     }

     if ( *lpCmdLine ) {
       argv[argc] = lpCmdLine;
       argc++;

       while ( *lpCmdLine && ( ( *lpCmdLine > 32 ) && ( *lpCmdLine <= 126 ) ) ) {
         lpCmdLine++;
       }

       if ( *lpCmdLine ) {
         *lpCmdLine = 0;
         lpCmdLine++;
       }
     }
   }
 }

 /* ================================================================ */
 void
 Sys_RedirectStdout ( void )
 {
   char *cur;
   char *home;
   char *old;
   char path_stdout[MAX_OSPATH];
   char path_stderr[MAX_OSPATH];

   if ( dedicated && dedicated->value ) {
     return;
   }

   home = Sys_GetHomeDir();

   if ( home == NULL ) {
     return;
   }

   cur = old = home;

   while ( cur != NULL ) {
     if ( ( cur - old ) > 1 ) {
       *cur = '\0';
       Sys_Mkdir ( home );
       *cur = '/';
     }

     old = cur;
     cur = strchr ( old + 1, '/' );
   }

   snprintf ( path_stdout, sizeof ( path_stdout ), "%s/%s", home, "stdout.txt" );
   snprintf ( path_stderr, sizeof ( path_stderr ), "%s/%s", home, "stderr.txt" );

   freopen ( path_stdout, "w", stdout );
   freopen ( path_stderr, "w", stderr );
 }
 #endif // DEDICATED_ONLY

 /* ========================================================================= */
 #ifdef DEDICATED_ONLY
 int main ( int argc, char *argv[] )
 #else
 int WINAPI
 WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance,
           LPSTR lpCmdLine, int nCmdShow )
 #endif // DEDICATED_ONLY
 {
 #ifndef DEDICATED_ONLY
   MSG msg;
 #endif

   int time, oldtime, newtime;

 #ifndef DEDICATED_ONLY
   /* Previous instances do not exist in Win32 */
   if ( hPrevInstance ) {
     return 0;
   }

   /* Make the current instance global */
   global_hInstance = hInstance;

   /* Redirect stdout and stderr into a file */
   Sys_RedirectStdout();
 #endif

   /* Print splash and features */
   Com_Splash();

   /* Seed PRNG */
   randk_seed();

 #ifndef DEDICATED_ONLY
   /* Parse the command line arguments */
   ParseCommandLine ( lpCmdLine );
 #endif

   /* Call the initialization code */
   Qcommon_Init ( argc, argv );

   /* Save our time */
   oldtime = Sys_Milliseconds();

   /* The legendary main loop */
   while ( 1 ) {
 #ifndef DEDICATED_ONLY
     /* If at a full screen console, don't update unless needed */
     if ( Minimized || ( dedicated && dedicated->value ) ) {
       Sleep ( 1 );
     }

     while ( PeekMessage ( &msg, NULL, 0, 0, PM_NOREMOVE ) ) {
       if ( !GetMessage ( &msg, NULL, 0, 0 ) ) {
         Com_Quit();
       }

       sys_msg_time = msg.time;
       TranslateMessage ( &msg );
       DispatchMessage ( &msg );
     }
 #endif

     do {
       newtime = Sys_Milliseconds();
       time = newtime - oldtime;
     } while ( time < 1 );

     _controlfp ( _PC_24, _MCW_PC );
     Qcommon_Frame ( time );

     oldtime = newtime;
   }

   /* never gets here */
   return TRUE;
 }
