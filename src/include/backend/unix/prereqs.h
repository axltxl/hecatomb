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
 * A header file for some of the plattform dependend stuff.
 *
 * =======================================================================
 */

 #ifndef UNIX_PREREQS_H
 #define UNIX_PREREQS_H

 #include "prereqs.h"

 #include <fcntl.h>
 #include <unistd.h>

 #include <sys/socket.h>
 #include <sys/time.h>
 #include <sys/types.h>
 #include <sys/param.h>
 #include <sys/ioctl.h>
 #include <sys/uio.h>
 #include <sys/ipc.h>
 #include <sys/shm.h>
 #include <sys/stat.h>
 #include <sys/wait.h>
 #include <sys/mman.h>

 #include <arpa/inet.h>
 #include <net/if.h>
 #include <netinet/in.h>
 #include <netdb.h>

 #include <dlfcn.h>
 #include <dirent.h>

 #endif /* UNIX_PREREQS_H */
