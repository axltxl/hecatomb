#Hecatomb Quake II
A portable Quake II client  

[![Build Status](https://drone.io/github.com/alericoveri/hecatomb/status.png)](https://drone.io/github.com/alericoveri/hecatomb/latest)

This is the Hecatomb Quake II Client (a.k.a. *htq2*), another great Quake II client who's being intensely developed towards *high portability potential*. Serious decisions are being made. 
The main focus is portability, modernization and expansion capabilities, that means *htq2* is not only portable but also extensible. 
With the power and stability of Yamagi Quake II, 
Hecatomb has full support of 64-bit architectures.
processors and operating systems. This code is based upon the solid codebase of [Yamagi's Quake II](http://github.com/yquake2), which itself is based upon Icculus Quake II, which itself is built upon id
Software's original code drop indeed, oh well ... 

##I wish to test drive this!
OK, so you want to try it out?. Here's what you'll need:
* CMake 2.8+ and a toolchain (compiler, linker, etc.)
* On *nix you'll need at least libsdl1.2, libgl (for the client)

###Supported platforms
* Windows XP+
* GNU/Linux
* FreeBSD
* OpenBSD
* Apple OSX 10.7+

###Supported architectures
* IA32  (a.k.a. *x86*)
* AMD64 (a.k.a. *x86_64*)
* IA64 (Intel Itanium)

#You wish to contribute?
That will be great from you!, *htq2* it's on its way to be a highly portable q2 client.
These are the established milestones. Your contribution through proper pull request will
be greatly appreciated.

##Current milestone is *0.1*
* Code layout/refactoring
* Solid codebase with porting capabilities
* CMake build system fully automated for all supported platforms
* No QAL pointers
* Get rid of CD-Audio playback (it's like playing tapes on a Commodore64)
* Generic Hunk allocator (based on plain *malloc*)
* Bug fixes

### Milestone 0.2
* No QGL pointers
* Optional use of dlmalloc
* C99 integer types *(proposed)*

### Milestone 0.3
* OpenGL extensions handling through GLEW *(proposed)*

### Milestone 0.4
* OpenGL ES 2.0+ support

At this point, you may wish to visit the wiki for more info!
Namaste!
