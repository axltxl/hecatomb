#Hecatomb Quake II
A portable Quake II client  

[![Build Status](https://drone.io/github.com/alericoveri/hecatomb/status.png)](https://drone.io/github.com/alericoveri/hecatomb/latest)

This is the Hecatomb Quake II Client (a.k.a. *htq2*), another great Quake II client who's being intensely developed towards *high portability potential*. Serious decisions are being made. 
The main focus is portability, modernization and expansion capabilities, that means *htq2* is not only portable but also extensible. 
With the power and stability of Yamagi Quake II, 
Hecatomb has full support of 64-bit architectures.
processors and operating systems. This code is based upon the solid codebase of [Yamagi's Quake II](http://github.com/yquake2), which itself is based upon Icculus Quake II, which itself is built upon id
Software's original code drop indeed, oh well ... 

##Compiling
#####Here's what you'll need:
* [CMake](http://www.cmake.org) 2.8+ and a toolchain (compiler, linker, etc.)
* [mingw-w64](http://mingw-w64.sourceforge.net/) is the only toolchain officially supported on Windows
* On *nix you'll need at least: 
  * [SDL 1.2](http://www.libsdl.org/)
  * An OpenGL implementation ([Mesa3D](http://www.mesa3d.org), nvidia-glx, AMD Catalyst, etc.)
  * [libjpeg](http://www.ijg.org/) (if `HT_WITH_RETEXTURE` option is set to `true`)
  * [libvorbisfile](http://www.vorbis.com/) (if `HT_WITH_OGG` option is set to `true`)
  * (On *nix but not OSX) libX11 (if `HT_WITH_X11GAMMA` option is set to `true`)
  * An [OpenAL](http://connect.creativelabs.com/openal) implementation (if `HT_WITH_OPENAL` option is set to `true`)
* On Windows and OSX: dependencies are bundled into the source tree, so don't worry, it'll build out-of-the-box :)

#####Now it's time to compile it:
* Download latest snapshot of the source code  
  `$ git clone git://github.com/alericoveri/hecatomb.git /path/to/hecatomb`
* Create a build directory for holding up CMake-related files  
  `$ mkdir /path/to/htq2-build`
* Go to it and generate your CMake build files (it's your choice what you want to generate: a Makefile, a XCode project, etc.)  
  `$ cd /path/to/htq2-build && cmake /path/to/hecatomb`
* Let's say you wanted generate a sweet and plain Makefile, now you can actually build it:  
  `$ make`
* Le voilà, you can already see the binaries on `/path/to/htq2-build/bin/<architecture>`a and test them:  
  `$ cd /path/to/htq2-build/bin/<architecture>`  
  `$ ./htq2 +set vid_fullscreen 0 +set deathmatch 1 +map q2dm1`
* It's highly probable that you'll be eager to edit your config files to your liking, they are located at your home directory:
  * On *nix and OSX, user files are located at `~/.htq2`
  * On Windows, user files are located at `%UserProfile%/Documents/Hecatomb Quake II`
* (On *nix) When you're happy with it, you can install your binaries:  
  `$ sudo make install`
* Enjoy!. Happy fragging!, there are great Q2 servers @ www.q2servers.com ;) ...
* At this point, you may wish to visit the [wiki](https://github.com/alericoveri/hecatomb/wiki) for more info!
* Please take a time to read the [FAQ](https://github.com/alericoveri/hecatomb/wiki/FAQ), thank you :)

##IRC
Come and join us in our IRC channel to have realtime information and latest updates about Hecatomb Quake II.
Feel free to chat with us, tell us about your ideas and proposals, make your questions, bug reports, etc.
Connect to *irc.freenode.net* and join *#htq2*.

##Supported platforms
* Windows XP+
* GNU/Linux
* FreeBSD
* OpenBSD
* Apple OSX 10.7+

##Supported architectures
* IA32  (a.k.a. *x86*)
* AMD64 (a.k.a. *x86_64*)
* IA64 (Intel Itanium)

#You wish to contribute?
That will be great from you!, *htq2* it's on its way to be a highly portable Quake II client.
These are the established milestones. Your contribution through *proper pull requests* will
be greatly appreciated.

##Current milestone is *0.1*
* Code layout/refactoring [DONE]
* Solid codebase with porting capabilities [DONE]
* CMake build system fully automated for all supported platforms [DONE]
* No QAL pointers [DONE]
* Get rid of CD-Audio playback [DONE]
* Generic Hunk allocator (based on plain `malloc`/`free`) [DONE]
* Bug fixes [DONE]

### Milestone 0.2
* No QGL pointers
* Optional use of dlmalloc
* C99 fixed integer types

### Milestone 0.3
* OpenGL extensions handling through GLEW *-proposed-*
* A more open music file system in the OGG backend *-proposed-*

### Milestone 0.4
* OpenGL ES 2.0+ support
