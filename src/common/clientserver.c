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
 * Client / Server interactions
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "system.h"
 #include "filesystem.h"

 #define MAXPRINTMSG 4096

 FILE *logfile;
 cvar_t *logfile_active;  /* 1 = buffer log, 2 = flush after each print */
 jmp_buf abortframe; /* an ERR_DROP occured, exit the entire frame */
 q_int32_t server_state;

 static q_int32_t rd_target;
 static char *rd_buffer;
 static q_int32_t rd_buffersize;
 static void ( *rd_flush ) ( q_int32_t target, char *buffer );

 /* ========================================================================= */
 void
 Com_BeginRedirect ( q_int32_t target, char *buffer, q_int32_t buffersize, void ( *flush ) )
 {
   if ( !target || !buffer || !buffersize || !flush ) {
     return;
   }

   rd_target = target;
   rd_buffer = buffer;
   rd_buffersize = buffersize;
   rd_flush = flush;
   *rd_buffer = 0;
 }

 /* ========================================================================= */
 void
 Com_EndRedirect ( void )
 {
   rd_flush ( rd_target, rd_buffer );
   rd_target = 0;
   rd_buffer = NULL;
   rd_buffersize = 0;
   rd_flush = NULL;
 }

 /*
  * Both client and server can use this, and it will output
  * to the apropriate place.
  */
 void
 Com_Printf ( char *fmt, ... )
 {
   va_list argptr;
   char msg[MAXPRINTMSG];
   va_start ( argptr, fmt );
   vsnprintf ( msg, MAXPRINTMSG, fmt, argptr );
   va_end ( argptr );

   if ( rd_target ) {
     if ( ( strlen ( msg ) + strlen ( rd_buffer ) ) > ( rd_buffersize - 1 ) ) {
       rd_flush ( rd_target, rd_buffer );
       *rd_buffer = 0;
     }

     strcat ( rd_buffer, msg );
     return;
   }

 #ifndef DEDICATED_ONLY
   Con_Print ( msg );
 #endif
   /* also echo to debugging console */
   Sys_ConsoleOutput ( msg );

   /* logfile */
   if ( logfile_active && logfile_active->value ) {
     char name[MAX_QPATH];

     if ( !logfile ) {
       Com_sprintf ( name, sizeof ( name ), "%s/qconsole.log", FS_Gamedir() );

       if ( logfile_active->value > 2 ) {
         logfile = fopen ( name, "a" );
       } else {
         logfile = fopen ( name, "w" );
       }
     }

     if ( logfile ) {
       fprintf ( logfile, "%s", msg );
     }

     if ( logfile_active->value > 1 ) {
       fflush ( logfile ); /* force it to save every time */
     }
   }
 }

// File path separator
#ifdef HT_OS_WINDOWS
# define FSEP '\\' // Stupid Windows always wanting to be 'different'
#else
# define FSEP '/'
#endif // HT_OS_WINDOWS
/*
 * Normally, compilers use full path on __FILE__, so it's best
 * to just shrink them a bit, this macro is compiler-safe, that
 * means that FLE will represent the full path to __FILE__ in
 * case it fails to shrink the file path
 */
#define FILENAME (strrchr(file, FSEP) ? strrchr(file, FSEP) + 1 : file)

 /*
  * A Com_Printf that only shows up if the "developer" cvar is set
  */
 void
 Com_DPrintfEx ( const char *function, char *file, q_int32_t line, char *fmt, ... )
 {
   va_list argptr;
   char msg[MAXPRINTMSG], // Brute message goes in here
        devstamp[MAXPRINTMSG];// Developer-stamp goes in here

   if ( !developer || !developer->value ) {
     return; /* don't confuse non-developers with techie stuff... */
   }

   va_start ( argptr, fmt );
   // Format the message
   vsnprintf ( msg, MAXPRINTMSG, fmt, argptr );
   va_end ( argptr );

   // Now, format the developer stamp (function, file and line)
   snprintf(devstamp, MAXPRINTMSG, "%s/%s:%d", function, FILENAME, line);

   // Forward a nice and pretty message to Com_Printf
   Com_Printf ("%-20s %s", devstamp, msg);
 }

 /*
  * A Com_Printf that only shows up when either the "modder" or "developer"
  * cvars is set
  */
 void
 Com_MDPrintf ( char *fmt, ... )
 {
   va_list argptr;
   char msg[MAXPRINTMSG];

   if ( ( !modder || !modder->value ) && ( !developer || !developer->value ) ) {
     return;
   }

   va_start ( argptr, fmt );
   vsnprintf ( msg, MAXPRINTMSG, fmt, argptr );
   va_end ( argptr );
   Com_Printf ( "%s", msg );
 }

 /*
  * Both client and server can use this, and it will
  * do the apropriate things.
  */
 void
 Com_Error ( q_int32_t code, char *fmt, ... )
 {
   va_list argptr;
   static char msg[MAXPRINTMSG];
   static qboolean recursive;

   if ( recursive ) {
     Sys_Error ( "recursive error after: %s", msg );
   }

   recursive = true;
   va_start ( argptr, fmt );
   vsnprintf ( msg, MAXPRINTMSG, fmt, argptr );
   va_end ( argptr );

   if ( code == ERR_DISCONNECT ) {
 #ifndef DEDICATED_ONLY
     CL_Drop();
 #endif
     recursive = false;
     longjmp ( abortframe, -1 );
   } else if ( code == ERR_DROP ) {
     Com_Printf ( "********************\nERROR: %s\n********************\n",
                  msg );
     SV_Shutdown ( va ( "Server crashed: %s\n", msg ), false );
 #ifndef DEDICATED_ONLY
     CL_Drop();
 #endif
     recursive = false;
     longjmp ( abortframe, -1 );
   } else {
     SV_Shutdown ( va ( "Server fatal crashed: %s\n", msg ), false );
 #ifndef DEDICATED_ONLY
     CL_Shutdown();
 #endif
   }

   if ( logfile ) {
     fclose ( logfile );
     logfile = NULL;
   }

   Sys_Error ( "%s", msg );
   recursive = false;
 }

 /*
  * Both client and server can use this, and it will
  * do the apropriate things.
  */
 void
 Com_Quit ( void )
 {
   Com_Printf ( "\n----------- shutting down ----------\n" );
   SV_Shutdown ( "Server quit\n", false );
   Sys_Quit();
 }

 /* ========================================================================= */
 q_int32_t
 Com_ServerState ( void )
 {
   return server_state;
 }

 /* ========================================================================= */
 void
 Com_SetServerState ( q_int32_t state )
 {
   server_state = state;
 }
