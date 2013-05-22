#Hecatomb Quake II
A portable Quake II client  

[![Build Status](https://drone.io/github.com/alericoveri/hecatomb/status.png)](https://drone.io/github.com/alericoveri/hecatomb/latest)

This is the Hecatomb Quake II Client (a.k.a. *htq2*), an enhanced Version of [Yamagi's Quake II](http://github.com/yquake2) 
who's being intensely developed towards *portability*. Serious decisions are being made. 
The main focus is portability, modernization and expansion capabilities, that means *htq2* is not only portable but also extensible. 
With the power and stability of Yamagi Quake II, 
Hecatomb has full support of 64-bit architectures.
processors and operating systems.

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

This code is based upon the solid codebase of Yamagi Quake II, which itself is based upon Icculus Quake II, which itself is built upon id
Software's original code drop indeed, oh well ... 

##Current milestone is *0.1*
* Layout/refactoring of the code
* CMake build system fully automated for all supported platforms
* No QAL whatsoever
* Get rid of CD-Audio playback (it's like playing LP's on a Commodore64)
* Bug fixes

### Milestone 0.2
* No QGL

At this point, you may wish to visit the wiki for more info!
Namaste!
