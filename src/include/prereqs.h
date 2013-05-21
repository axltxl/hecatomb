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
 * Prequisites
 */

 #ifndef PREREQS_H
 #define PREREQS_H

 // Configuration file
 #include "config.h"

 // ISO C headers
 #if HT_HAVE_ASSERT_H
 # include <assert.h>
 #endif
 #if HT_HAVE_MATH_H
 # include <math.h>
 #endif
 #if HT_HAVE_STRING_H
 # include <string.h>
 #endif
 #if HT_HAVE_STDARG_H
 # include <stdarg.h>
 #endif
 #if HT_HAVE_STDIO_H
 # include <stdio.h>
 #endif
 #if HT_HAVE_STDLIB_H
 # include <stdlib.h>
 #endif
 #if HT_HAVE_CTYPE_H
 # include <ctype.h>
 #endif
 #if HT_HAVE_SETJMP_H
 # include <setjmp.h>
 #endif
 #if HT_HAVE_SIGNAL_H
 # include <signal.h>
 #endif
 #if HT_HAVE_TIME_H
 # include <time.h>
 #endif
 #if HT_HAVE_LOCALE_H
 # include <locale.h>
 #endif
 #if HT_HAVE_ASSERT_H
 # include <errno.h>
 #endif
 #if HT_HAVE_ASSERT_H
 # include <stdint.h>
 #endif

 // Common
 #include "common/common.h"

 #endif // PREREQS_H

