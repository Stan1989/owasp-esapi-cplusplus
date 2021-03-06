#!/bin/bash

# ====================================================================
#
# OWASP Enterprise Security API (ESAPI)
#
# This file is part of the Open Web Application Security Project (OWASP)
# Enterprise Security API (ESAPI) project. For details, please see
# http://www.owasp.org/index.php/ESAPI.
#
# Copyright (c) 2013 - The OWASP Foundation
#
# @author Kevin Wall, kevin.w.wall@gmail.com
# @author Jeffrey Walton, noloader@gmail.com
#
# ====================================================================
#
# Sets the cross compile environment for Android
# Based upon OpenSSL's setenv-android.sh (by TH, JW, and SM).
# See http://code.google.com/p/owasp-esapi-cplusplus/wiki/CrossCompile
# for details on usage.
#
# ====================================================================

#########################################
#####   User configurable options   #####
#########################################

# Define SETENV_VERBOSE=1 to print the configuration, including exported
# variables. If using SETENV_VERBOSE, the *only* empty variable will be
# SETENV_SIMULATOR in a device configuration. Otherwise, SETENV_SIMULATOR
# will be defined too. Any other missing values should be fixed (and
# should have caused an error).
# Invoke use `setenv-ios.sh verbose` for the setting.
SETENV_VERBOSE=1

# Default architecture
IOS_ARCH=armv7

########################################
#####         Command line         #####
########################################

# We only recognize Device, Simulator and Verbose
# We recognize Device so we can unset SETENV_SIMULATOR
for ARG in "$@"
do
  CL=`echo $ARG | tr '[A-Z]' '[a-z]'`

  #
  # Brief output (default)
  if [ "$CL" == "b" ] || [ "$CL" == "brief" ]; then
    SETENV_VERBOSE=0
  fi

  #
  # Verbose output. Prints environmental changes
  if [ "$CL" == "v" ] || [ "$CL" == "verbose" ]; then
    SETENV_VERBOSE=1
  fi

  #
  # Device target (default)
  if [ "$CL" == "d" ] || [ "$CL" == "dev" ] || [ "$CL" == "device" ]; then
    IOS_ARCH=armv7
  fi

  #
  # Simulator target
  if [ "$CL" == "s" ] || [ "$CL" == "sim" ] || [ "$CL" == "simulator" ]; then
        IOS_ARCH=i386
  fi

  #
  # ARMv5
  if [ "$CL" == "armv5" ]; then
    IOS_ARCH=armv5
  fi

  #
  # ARMv6
  if [ "$CL" == "armv6" ]; then
    IOS_ARCH=armv6

  fi

  #
  # ARMv7
  if [ "$CL" == "armv7" ]; then
    IOS_ARCH=armv7

  fi

  #
  # ARMv7s
  if [ "$CL" == "armv7s" ]; then
    IOS_ARCH=armv7s

  fi

done

########################################
#####       Error Condition        #####
########################################
SETENV_ERROR=0

#########################################
#####      Target configuration     #####
#########################################

#
# Tim/Steve: allow a user override? I think we should be doing this. The use case is:
# move /Applications/Xcode somewhere else for a side-by-side installation.
# These sorts of tricks are a required procedure on Apple's gear:
# http://stackoverflow.com/questions/11651773/install-simulator-sdk-4-3-to-xcode-4-4-on-mountain-lion
if [ -z "$XCODE_DEVELOPER" ]; then
  XCODE_DEVELOPER="/Applications/Xcode.app/Contents/Developer"
  XCODE_TOOLCHAIN="$XCODE_DEVELOPER/usr/bin"
fi

#
# http://developer.apple.com/library/mac/#documentation/Darwin/Reference/ManPages/man1/xcode-select.1.html
# XCODE_DEVELOPER=`xcode-select -print-path`
# XCODE_DEVELOPER="/Applications/Xcode.app/Contents/Developer"

if [ ! -d "$XCODE_DEVELOPER" ]; then
  echo "ERROR: unable to find XCODE_DEVELOPER directory."
  SETENV_ERROR=1
fi

#
# XCODE_DEVELOPER_TOP is the top of the development tools tree
if [ "$IOS_ARCH" == "i386" ]; then
  XCODE_DEVELOPER_TOP="$XCODE_DEVELOPER/Platforms/iPhoneSimulator.platform/Developer"
  if [ ! -d "$XCODE_DEVELOPER_TOP" ]; then
    echo "ERROR: unable to find Xcode Simulator directory."
    SETENV_ERROR=1
  fi
else
  export XCODE_DEVELOPER_TOP="$XCODE_DEVELOPER/Platforms/iPhoneOS.platform/Developer"
  if [ ! -d "$XCODE_DEVELOPER_TOP" ]; then
    echo "ERROR: unable to find Xcode Device directory."
    SETENV_ERROR=1
  fi
fi

#
# IOS_TOOLCHAIN is the location of the actual compiler tools.
if [ -d "$XCODE_DEVELOPER/Toolchains/XcodeDefault.xctoolchain/usr/bin/" ]; then
  IOS_TOOLCHAIN="$XCODE_DEVELOPER/Toolchains/XcodeDefault.xctoolchain/usr/bin/"
elif [ -d "$XCODE_DEVELOPER_TOP/usr/bin/" ]; then
  IOS_TOOLCHAIN="$XCODE_DEVELOPER_TOP/usr/bin/"
fi

if [ -z "$IOS_TOOLCHAIN" ] || [ ! -d "$IOS_TOOLCHAIN" ]; then
  echo "ERROR: unable to find Xcode cross-compiler tools."
  SETENV_ERROR=1
fi

#
# XCODE_SDK is the SDK name/version being used - adjust the list as appropriate.
# For example, remove 4.3, 6.2, and 6.1 if they are not installed. Note: Apple 
# makes this available under Xcode via $(SDK_NAME).
for i in 7.2 7.1 7.0 6.2 6.1 6.0 5.1 5.0 4.3 do
# for i in 0.1 0.5 1.0 2.0 do
do

  if [ "$IOS_ARCH" == "i386" ]; then
    if [ -d "$XCODE_DEVELOPER/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator"$i".sdk" ]; then
      SDKVER=$i
      export XCODE_SDK=iPhoneSimulator"$SDKVER".sdk
      break
    fi
  else
    if [ -d "$XCODE_DEVELOPER/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS"$i".sdk" ]; then
      SDKVER=$i
      export XCODE_SDK=iPhoneOS"$SDKVER".sdk
      break
    fi
  fi
done

#
# Die if we did not find an SDK
if [ -z "$SDKVER" ]; then
  echo "ERROR: unable to find a valid SDK."
  SETENV_ERROR=1
fi

#
# Simulator uses i386, Device uses ARMv5, ARMv6, ARMv7, or ARMv7s
#
# Apple deprecated ARMv5 at iOS 4.0, and ARMv6 at iOS 5.0
# http://stackoverflow.com/questions/7488657/how-to-build-for-armv6-and-armv7-architectures-with-ios-5

case "$IOS_ARCH" in
    i386)
      echo "Configuring for Simulator (i386)"
      ;;
    armv5)
      echo "Configuring for Device (ARMv5)"
      ;;
    armv6)
      echo "Configuring for Device (ARMv6)"
      ;;
    armv7)
      echo "Configuring for Device (ARMv7)"
      ;;
    armv7s)
      echo "Configuring for Device (ARMv7s)"
      ;;
    *)
      echo "ERROR: unable to determine architecture."
        SETENV_ERROR=1
      ;;
esac

#
# -arch is used by the makefile.
export IOS_ARCH

#
# --sysroot is used by the makefile.
export IOS_SYSROOT="$XCODE_DEVELOPER_TOP"/SDKs/"$XCODE_SDK"

#######################################
#####          Verbose           #####
#######################################

if [ "$SETENV_VERBOSE" == "1" ]; then

  echo "XCODE_SDK:" $XCODE_SDK
  echo "XCODE_DEVELOPER: $XCODE_DEVELOPER"
  echo "XCODE_TOOLCHAIN: $XCODE_TOOLCHAIN"
  echo "XCODE_DEVELOPER_TOP: $XCODE_DEVELOPER_TOP"
  echo "IOS_ARCH: $IOS_ARCH"
  echo "IOS_TOOLCHAIN: $IOS_TOOLCHAIN"
  echo "IOS_SYSROOT: $IOS_SYSROOT"
fi

#######################################
#####         SYSROOT Test        #####
#######################################

if [ ! -d "$IOS_SYSROOT" ]; then
  echo "ERROR: SYSROOT will not be valid for Configure."
  SETENV_ERROR=1
else
  if [ "$SETENV_VERBOSE" == "1" ]; then
    echo "SYSROOT TEST: found valid sysroot, we're go for launch"
  fi
fi

########################################
#####     Path with Toolchains     #####
########################################

# Only modify/export PATH if IOS_TOOLCHAIN good
if [ ! -z "$IOS_TOOLCHAIN" ] && [ ! -z "$XCODE_TOOLCHAIN" ]; then

  # And only modify PATH if IOS_TOOLCHAIN is not present
  TOOL_PATH="$IOS_TOOLCHAIN:$XCODE_TOOLCHAIN"
  LEN=${#TOOL_PATH}
  SUBSTR=${PATH:0:$LEN}
  if [ "$SUBSTR" != "$TOOL_PATH" ]; then
    export PATH="$TOOL_PATH":"$PATH"
  fi
else
    echo "ERROR: unable to set new PATH."
fi

########################################
#####        Tool Test Time        #####
########################################

# Test for various tools needed during cross compilation.
# FOUND_ALL starts high, and pushes low on failure
FOUND_ALL=1

# Apple's embedded g++ cannot compile integer.cpp
TARGET_TOOLS="llvm-gcc llvm-g++ ar ranlib libtool ld"
for tool in $TARGET_TOOLS
do
  if [ ! -e "$IOS_TOOLCHAIN/$tool" ] && [ ! -e "$XCODE_TOOLCHAIN/$tool" ]; then
    echo "WARNING: unable to find $tool at IOS_TOOLCHAIN or XCODE_TOOLCHAIN"
    FOUND_ALL=0
  fi
done

if [ "$SETENV_VERBOSE" == "1" ] && [ "$FOUND_ALL" == "1" ]; then
  echo "TOOL TEST: found all tools, this might actually work"
fi
