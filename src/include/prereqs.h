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
 #include <assert.h>
 #include <math.h>
 #include <string.h>
 #include <stdarg.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include <setjmp.h>
 #include <signal.h>
 #include <ctype.h>
 #include <time.h>
 #include <locale.h>
 #include <errno.h>

 // Standard integer types
 #if HT_HAVE_STDINT_H
 # include <stdint.h>
 #else
 #endif

 // Common
 #include "common/common.h"

 #endif // PREREQS_H

