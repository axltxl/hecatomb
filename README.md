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
* The following dependencies are optional:
  * [libjpeg](http://www.ijg.org/) (if `HT_WITH_RETEXTURE` option is set to `true`)
  * [libvorbisfile](http://www.vorbis.com/) (if `HT_WITH_OGG` option is set to `true`)
  * (On *nix but not OSX) libX11 (if `HT_WITH_X11GAMMA` option is set to `true`)
  * An [OpenAL](http://connect.creativelabs.com/openal) implementation (if `HT_WITH_OPENAL` option is set to `true`)
  * [zlib](http://www.zlib.net) (if `HT_WITH_ZIP` option is set to `true`)
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

##FAQ

####How do I open the console?   
Press `^` or `~`, depending on your keyboard layout.
Actually, pressing `Shift + Ctrl` will open up the console on any keyboard layout.

####How do I get the frame counter?
Set `cl_drawfps` to 1

####How do I make a benchmark?
Set `timedemo` to 1 and play a demo.

####How do I play demos?
`demomap name.dm2`. Note that the extension .dm2 is important!

####How do I record a demo?
`record name` and `stop` to stop.

####When playing in window mode my cursor is locked onto the window. Can I change
that, so that Quake II behaves like a normal window?
Open the console by pressing `~` or `^` or drop into the menu. If you want Quake
II to never  grab the mouse set `in_grab` to 0, if Quake II should never
release the mouse set 1, for releasing the mouse when the console or the
menu is opened set to 2. The default is 2.

####Hey, my screensaver crashes Quake II or I experience strange crashes after a
fixed amount of time!
This is a known bug in some linux distributions. SDL fails to disable
the screensaver even if we tell him to do so. See [this Ubuntu bugreport](https://bugs.launchpad.net/ubuntu/+source/gnome-screensaver/+bug/32457).
As a work around use the startscript in stuff/quake-start.sh It deactivates
the screensaver before starting Quake II and reenables it after exiting the
game.

####The movement is screwed up! I can jump much higher and longer as it used to be! What's wrong?
You're experiencing the Quake II version of the famous Q3A 125hz bug.
When Quake II draws more than about 100 FPS the movement calculations go
wrong and you can jump much higher. To solve this set `cl_maxfps` to about
95 FPS. And no, we won't fix it since it would be very invasive and most
likely break a lot of other things.

####I'm creating a package or port for my system. Is a system wide install
possible without patching the source?
Yes. Just set -DSYSTEMWIDE. If you want to change the default
directory from /usr/share/games/quake2/, just set -DSYSTEMDIR
to the desired path.

####Can I connect to an IPv6 server?
Yes, the same way as connecting to an IPv4 server. Since the Quake II console
has problems with the characters `:`, `[` and `]` we suggest to submit the
connection command as command line argument:
  `ht +connect "[2001:db8::1]"`
If you want to connect to a server with a non-standard port use the following
syntax:
  `ht +connect "[2001:db8::1]:12345"`
For your server to show up in the server list you need to supply a multicast
interface to both the client and the server:
  `htded +set multicast eth0`
  `ht +set multicast eth0`
Normaly the server will listen to all IPv4 and IPv6 addresses. You can bind
it to an address with:
  `htded +set ip "[2001:db8::1]"`

####Where can I find the configuration file?
It's located at ~/.yq2/game/config.cfg (FreeBSD, Linux, OpenBSD and OS X) or
...\Documents\YamagiQ2\game\config.cfg (Windows). Replace "game" by the mod
name, e.g. "baseq2/" for the main game.

####My mod crashes at startup.
This is known problem of some mods. A workaround is to create the working
directory by hand:
  `mkdir -p ~/.yq2/$moddir` (FreeBSD, Linux, OpenBSD and OS X)
  `...\Documents\YamagiQ2\$moddir` (Windows)

####Only parts of the maps are rendered!
By default the maximum view distance is 2300 units. You can widen it up
to 4096 units by setting `gl_farsee` to "1".

####What is yq2.cfg for?
yq2.cfg is an alternate startup script, used to override some bad
decisions in the original defaults.cfg. Please do not alter it,
unless you know what you're doing! It might break the game!.

####Why isn't there an "underwater sound effect" when playing under OS X?
That's a limitation of OS X. Apple's OpenAL implementation doesn't
support sound effects.

####Why is the FOV different than in id Software's client?
id Softwares client was designed to work an 4:3 screens only. Setting
the FOV kept the aspect ratio, expanded the view angle in height and 
width. Setting a higher FOV on wider screens was common, but the image
distorted lightly. Yamagi Quake II calculates a correct FOV without
distortions. You can get the old behavior if you select an aspect
ratio other than "auto" in the video menu or by setting the `horplus`
cvar to "0".

####Why doesn't gl_showtris work?
`gl_showtris` requires `gl_ext_multitexturing` set to 0.

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
