#
# Routine for OS and compiler detection
# Thanks to SFML guys (www.sfml-dev.org)
#

# detect the architecture (note: this test won't work for cross-compilation)
include (TargetArch)
target_architecture(ARCH)
if (ARCH STREQUAL "unknown")
  message (FATAL_ERROR "Unknown architecture!")
endif()

# detect the OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set (LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
  set (BSD 1)
  set (FREEBSD 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD")
  set (BSD 1)
  set (OPENBSD 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set (OSX 1)
    # detect OS X version. (use '/usr/bin/sw_vers -productVersion' to extract V from '10.V.x'.)
    EXEC_PROGRAM(/usr/bin/sw_vers ARGS -productVersion OUTPUT_VARIABLE OSX_VERSION_RAW)
    STRING(REGEX REPLACE "10\\.([0-9]).*" "\\1" OSX_VERSION "${OSX_VERSION_RAW}")
    if(${OSX_VERSION} LESS 7)
        message(FATAL_ERROR "Unsupported version of OS X : ${OSX_VERSION_RAW}")
        return()
    endif()
else()
    message (WARNING "Unsupported platform: This will be an experimental build at best.")
    set (OS_UNK 1)
endif()

# detect the compiler and its version
#
# Base CFLAGS.
#

# GCC
if ("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")

  # Basic compiler flags
  set (COMPILER_GCC 1)
  set (CMAKE_C_FLAGS "-Wall -pipe")

  # -O2 are enough optimizations.
  #
  # -fno-strict-aliasing since the source doesn't comply
  #  with strict aliasing rules and it's next to impossible
  #  to get it there...
  #
  # -fomit-frame-pointer since the framepointer is mostly
  #  useless for debugging Quake II and slows things down.
  #
  # -g to build always with debug symbols. Please DO NOT
  #  CHANGE THIS, since it's our only chance to debug this
  #  crap when random crashes happen!
  set (CMAKE_C_FLAGS_RELEASE "-O2 -fno-strict-aliasing -fomit-frame-pointer -g")

  # -MMD to generate header dependencies. (They cannot be
  #  generated if building universal binaries on OSX)a
  if (OSX)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -MMD")
  endif()

# clang
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")

  # Basic compiler flags
  set (COMPILER_CLANG 1)
  set (CMAKE_C_FLAGS "-Weverything")

  #
  # Link-time optimizations need llvm-gold plugin
  # which comes out-of-the-box on OSX but not on Linux
  # (Needs some double checking)
  if (OSX AND OSX_VERSION GREATER 8 )
    set (CMAKE_C_FLAGS_RELEASE "-O4")
  else ()
    set (CMAKE_C_FLAGS_RELEASE "-O3")
  endif()

  # -g to build always with debug symbols. Please DO NOT
  #  CHANGE THIS, since it's our only chance to debug this
  #  crap when random crashes happen!a
  set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -g")

# Unsupported compiler
else()
    message(FATAL_ERROR "Unsupported compiler. Current supported compilers are gcc and clang.")
    return()
endif()

# clang++ (Only for OS X)
if (OSX)
  if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    # Basic compiler flags
    set (COMPILER_CLANGXX 1)
    set (CMAKE_CXX_FLAGS "-Weverything")
    set (CMAKE_CXX_FLAGS_RELEASE "-O4 -g")
  endif()
endif()
