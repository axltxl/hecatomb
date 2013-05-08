#Hecatomb
A Q2 Engine Expansion  

[![Build Status](https://drone.io/github.com/alericoveri/hecatomb/status.png)](https://drone.io/github.com/alericoveri/hecatomb/latest)

This is the Hecatomb Quake II Client, an enhanced Version of [Yamagi's Quake 2](http://github.com/yquake2)
II. The main focus is engine modernization and expansion. With the power and stability of Yamagi Quake II, 
Hecatomb has full support of 64-bit architectures.
processors and operating systems. This code should run on Windows XP or later,
Mac OS X 10.6 or higher and on most unix-like operating systems (only FreeBSD,
Linux and OpenBSD are officially supported and tested, for other systems you'd
at least have to edit the `Makefile`), just type `make` or `gmake` to compile.

This code is based upon Yamagi Quake II, which itself is based upon Icculus Quake II, which itself is built upon id
Software's original code drop indeed. Additional code and patches by many contributers
were used. It's released under the terms of the GPL version 2. See the LICENSE
file for further information.

###Priorities at this time
* Good layout/organization of the code, that includes 2-space indentation and better header layout
* CMake build automation integration

###Priorities at future
* Better cross-architecture integer support

###Wishlist
* PhysFS backend for FS_ calls
* GLEW backend for dealing with OpenGL context and extensions on refresher


#FAQ

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

####The movement is fucked up! I can jump much higher and longer as it used to be! What's wrong?
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
  `./quake2 +connect "[2001:db8::1]"`
If you want to connect to a server with a non-standard port use the following
syntax:
  `./quake2 +connect "[2001:db8::1]:12345"`
For your server to show up in the server list you need to supply a multicast
interface to both the client and the server:
  `./q2ded +set multicast eth0`
  `./quake2 +set multicast eth0`
Normaly the server will listen to all IPv4 and IPv6 addresses. You can bind
it to an address with:
  `./q2ded +set ip "[2001:db8::1]"`

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
