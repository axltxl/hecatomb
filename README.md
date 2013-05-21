#Hecatomb Quake II
A portable Quake II client  

[![Build Status](https://drone.io/github.com/alericoveri/hecatomb/status.png)](https://drone.io/github.com/alericoveri/hecatomb/latest)

This is the Hecatomb Quake II Client (a.k.a. *htq2*), an enhanced Version of [Yamagi's Quake II](http://github.com/yquake2) 
who's being intensely developed towards *portability*. Serious decisions are being made. 
The main focus is engine portability, modernization and expansion capabilities, that means HTQ2 is not only portable but also extensible. 
With the power and stability of Yamagi Quake II, 
Hecatomb has full support of 64-bit architectures.
processors and operating systems. This code should run on Windows XP or later,
Mac OS X 10.6 or higher and on most unix-like operating systems (only FreeBSD,
Linux and OpenBSD are officially supported and tested, for other systems you'd
at least have to edit the `Makefile`), just type `make` or `gmake` to compile.

This code is based upon the solid codebase of Yamagi Quake II, which itself is based upon Icculus Quake II, which itself is built upon id
Software's original code drop indeed, oh well ... 

Additional code and patches by many contributers
were used. It's released under the terms of the GPL version 2. See the LICENSE
file for further information.

###Priorities at this time
* Good layout/organization of the code, that includes 2-space indentation and better header layout
* CMake build system fully automated for all supported platforms

###Priorities at future
* Better cross-architecture integer support

###Wishlist
* PhysFS backend for FS_ calls
* GLEW backend for dealing with OpenGL context and extensions on refresher

#***Please watch the FAQ before doing anything!***
