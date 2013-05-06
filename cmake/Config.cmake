#
# Routine for OS and compiler detection
# Thanks to SFML guys (www.sfml-dev.org)
#

# detect the architecture (note: this test won't work for cross-compilation)
include(CheckTypeSize)
check_type_size(void* SIZEOF_VOID_PTR)
if("${SIZEOF_VOID_PTR}" STREQUAL "4")
  set(ARCH_32 1)
elseif("${SIZEOF_VOID_PTR}" STREQUAL "8")
  set(ARCH_64 1)
else()
  message(FATAL_ERROR "Unsupported architecture")
  return()
endif()

# detect the OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set (LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
  set (BSD 1)
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
    message(FATAL_ERROR "Unsupported operating system (for the moment)")
    return()
endif()

# detect the compiler and its version
#
# Base CFLAGS.
#

# GCC
if ("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
  set (COMPILER_GCC 1)

  # -g to build always with debug symbols. Please DO NOT
  #  CHANGE THIS, since it's our only chance to debug this
  #  crap when random crashes happen!
  set (CMAKE_C_FLAGS "-Wall -pipe")

  # -O2 are enough optimizations.
  #
  # -fno-strict-aliasing since the source doesn't comply
  #  with strict aliasing rules and it's next to impossible
  #  to get it there...
  #
  # -fomit-frame-pointer since the framepointer is mostly
  #  useless for debugging Quake II and slows things down.
  set (CMAKE_C_FLAGS_RELEASE "-O2 -fno-strict-aliasing -fomit-frame-pointer")

  # -MMD to generate header dependencies. (They cannot be
  #  generated if building universal binaries on OSX)
  if (OSX)
    list (APPEND CMAKE_C_FLAGS "-MMD")
  endif()

# clang
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
  set (COMPILER_CLANG 1)
  set (CMAKE_C_FLAGS "-Weverything")

  #
  # Link-time optimizations need llvm-gold plugin
  # which comes out-of-the-box on OSX but not on Linux
  # (Needs some double checking)
  if (OSX AND OSX_VERSION GREATER 8 )
    set (CMAKE_C_FLAGS_RELEASE "-O4")
  elseif (LINUX)
    set (CMAKE_C_FLAGS_RELEASE "-O3")
  endif()

# Unsupported compiler
else()
    message(FATAL_ERROR "Unsupported compiler. Current supported compilers are gcc and clang.")
    return()
endif()
