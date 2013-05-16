/*
 * Copyright (C) 2011 Yamagi Burmeister
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
 * This is a signal handler for printing some hints to debug problem in
 * the case of a crash. On Linux a backtrace is printed.
 *
 * =======================================================================
 */

 #include "prereqs.h"

 #ifdef HT_OS_LINUX
 # include <execinfo.h>
 #endif

 void
 printBacktrace ( int sig )
 {
 #ifdef HT_OS_LINUX
   void *array[15];
   size_t size;
   char **strings;
   int i;
   size = backtrace ( array, 15 );
   strings = backtrace_symbols ( array, size );
 #endif
   printf ( "%s - v%s\n", HT_DEV_NAME, HT_VERSION);
   printf ( "OS = %s\n", HT_OS_NAME );
   printf ( "arch = %s\n", HT_ARCH_NAME );
   printf ( "cc = %s-%d.%d.%d\n", HT_CC_ID, HT_CC_VERSION_MAJOR,
                                  HT_CC_VERSION_MINOR, HT_CC_VERSION_PATCH );
   printf ( "signal = %i\n", sig );
   printf ( "\nBacktrace:\n" );
 #ifdef HT_OS_LINUX
   for ( i = 0; i < size; i++ ) {
     printf ( "  %s\n", strings[i] );
   }
 #else
   printf ( "  Not available on this plattform.\n\n" );
 #endif
 }

 void
 signalhandler ( int sig )
 {
   printf ( "\n=======================================================\n" );
   printf ( "%s HAS CRASHED! This is embarassing indeed...\n", HT_PRODUCT_NAME );
   printf ( "\nMake sure that you're using the last version. It can\n" );
   printf ( "be found at %s. If you do,\n", HT_URL );
   printf ( "send a bug report to %s and include:\n\n", HT_EMAIL );
   printf ( " - This output\n" );
   printf ( " - The conditions that triggered the crash\n" );
   printf ( " - How to reproduce the crash (if known)\n" );
   printf ( " - The following files. None of them contains private\n" );
   printf ( "   data. They're necessary to analyze the backtrace:\n\n" );
   printf ( "    - quake2 (the executable / binary)\n\n" );
   printf ( "    - game.so (the game.so of the mod you were playing\n" );
   printf ( "      when the game crashed. %s/game.so for the\n", BASEDIRNAME );
   printf ( "      main game)\n\n" );
   printf ( " - Any other data which you think might be usefull\n" );
   printf ( "\nThank you very much for your help, making %s\n", HT_PRODUCT_NAME );
   printf ( "an even better source port. It's much appreciated.\n" );
   printf ( "=======================================================\n\n" );
   printBacktrace ( sig );

   /* make sure this is written */
   fflush ( stdout );

   /* reset signalhandler */
   signal ( SIGSEGV, SIG_DFL );
   signal ( SIGILL, SIG_DFL );
   signal ( SIGFPE, SIG_DFL );
   signal ( SIGABRT, SIG_DFL );

   /* pass signal to the os */
   raise ( sig );
 }

 void
 registerHandler ( void )
 {
   signal ( SIGSEGV, signalhandler );
   signal ( SIGILL, signalhandler );
   signal ( SIGFPE, signalhandler );
   signal ( SIGABRT, signalhandler );
 }
