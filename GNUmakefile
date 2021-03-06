# OWASP Enterprise Security API (ESAPI)
# This file is part of the Open Web Application Security Project (OWASP)
# Enterprise Security API (ESAPI) project. For details, please see
# http://www.owasp.org/.
#
# The ESAPI is published by OWASP under the BSD license. You should read and
# accept the LICENSE before you use, modify, and/or redistribute this software.
#
# Copyright (c) 2011 - The OWASP Foundation

# Note: we use both $CPPFLAGS and $CXXFLAGS for recipes which include $CXX.
# See http://www.gnu.org/s/hello/manual/make/Catalogue-of-Rules.html.

# Comeau C++ Compiler
#   CXX = como
# Clang C++ Compiler
#   CXX = clang++
# Intel ICC
#   CXX = icpc
# GNU C++ Compiler
#   CXX =	g++

# Default rule for `make`
default: test

# Clear unneeded implicit rules
.SUFFIXES:
.SUFFIXES: .c .cc .cpp .cxx .o .h .hpp

# Override on the command line as you see fit, eg `make install CP=~/my-cool-cp`.
# Otherwise, we take defaults from paths in the environment.
AR = ar
CP = cp
RM = rm
CC = gcc
CPP = cpp
CXX = g++
EGREP = egrep
UNAME = uname
MKDIR = mkdir
RANLIB = ranlib
INSTALL = install
ARFLAGS = -rcs

# Extension will be changed for Mac OS X below.
DYNAMIC_LIB =	libesapi-c++.so
STATIC_LIB =	libesapi-c++.a

# This might get messy….
ESAPI_CPP_STD = -std=c++03

# Try and pick up on targets/goals.
# See https://lists.owasp.org/pipermail/owasp-esapi-c++/2011-August/000157.html for mixing and matching Debug/Release/Test from goals.
WANT_DEBUG = 0
WANT_TEST = 0
WANT_RELEASE = 0

DEBUG_GOALS = $(filter $(MAKECMDGOALS), debug)
ifneq ($(DEBUG_GOALS),)
  WANT_DEBUG := 1
  WANT_TEST := 0
  WANT_RELEASE := 0
endif

TEST_GOALS = $(filter $(MAKECMDGOALS), test)
ifneq ($(TEST_GOALS),)
  WANT_DEBUG := 0
  WANT_TEST := 1
  WANT_RELEASE := 0
endif

RELEASE_GOALS = $(filter $(MAKECMDGOALS), release all $(DYNAMIC_LIB) $(STATIC_LIB) crypto codec codecs err errors ref reference)
ifneq ($(RELEASE_GOALS),)
  WANT_DEBUG := 0
  WANT_TEST := 0
  WANT_RELEASE := 1
endif

# If nothing is specified, default to Release.
ifeq ($(WANT_DEBUG),0)
  ifeq ($(WANT_TEST),0)
    WANT_RELEASE := 1
  endif
endif

# libstdc++ debug: http://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode.html
ifeq ($(WANT_DEBUG),1)
  # Whoops, ABI compatibility issues with pre-built DSOs
  # ESAPI_CXXFLAGS += -D_GLIBCXX_DEBUG=1 -DDEBUG=1 -g3 -ggdb -O0 -Dprivate=public -Dprotected=public
  ESAPI_OPTIMIZE = -O0
  ESAPI_CFLAGS += -DDEBUG=1 -UNDEBUG -g3 -ggdb $(ESAPI_OPTIMIZE) -Dprivate=public -Dprotected=public
  ESAPI_CXXFLAGS += -DDEBUG=1 -UNDEBUG -g3 -ggdb $(ESAPI_OPTIMIZE) -Dprivate=public -Dprotected=public
endif

ifeq ($(WANT_RELEASE),1)
  ESAPI_OPTIMIZE = -O2
  ESAPI_CFLAGS += -DNDEBUG=1 -UDEBUG -g $(ESAPI_OPTIMIZE)
  ESAPI_CXXFLAGS += -DNDEBUG=1 -UDEBUG -g $(ESAPI_OPTIMIZE)
endif

ifeq ($(WANT_TEST),1)
  ESAPI_OPTIMIZE = -O2
  ESAPI_CFLAGS += -DESAPI_NO_ASSERT=1 -DESAPI_BUILD_TEST=1 -g2 -ggdb $(ESAPI_OPTIMIZE) -Dprivate=public -Dprotected=public
  ESAPI_CXXFLAGS += -DESAPI_NO_ASSERT=1 -DESAPI_BUILD_TEST=1 -g2 -ggdb $(ESAPI_OPTIMIZE) -Dprivate=public -Dprotected=public
endif

# For SafeInt. Painting with a broad brush, unsigned negation is bad becuase
# the bit pattern is negated, but the type remains the same. So a positive
# integer is never transformed into a negative integer as expected. It morphs
# into a bigger or smaller unsigned integer.
ESAPI_CXXFLAGS += -DSAFEINT_DISALLOW_UNSIGNED_NEGATION=1

IS_LINUX = $(shell $(UNAME) 2>&1 | $(EGREP) -i -c 'linux')
IS_SOLARIS = $(shell $(UNAME) -a 2>&1 | $(EGREP) -i -c 'solaris')
IS_BSD = $(shell $(UNAME) 2>&1 | $(EGREP) -i -c '(openbsd|freebsd|netbsd)')
IS_DARWIN = $(shell $(UNAME) 2>&1 | $(EGREP) -i -c 'darwin')
IS_APPLE = $(shell $(CPP) -dM < /dev/null 2>&1 | $(EGREP) -i -c "__apple__")
IS_GENTOO = $(shell $(UNAME) -a | $(EGREP) -i -c "gentoo")
IS_ANDROID = $(shell $(CPP) -dM < /dev/null 2>&1 | $(EGREP) -i -c "__android__")
IS_X86_OR_X64 = $(shell uname -m | $(EGREP) -i -c "i.86|x86|i86|i386|i686|amd64|x86_64")

# Don't know a good test for this....
http://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_8.html#SEC82
ifneq "$(origin IOS_SYSROOT)" "undefined"
  IS_IOS = 1
endif

ifneq "$(origin ANDROID_SYSROOT)" "undefined"
  IS_ANDROID = 1
endif

GCC_COMPILER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version')
INTEL_COMPILER = $(shell $(CXX) --version 2>&1 | $(EGREP) -i -c '\(icc\)')
COMEAU_COMPILER = $(shell $(CXX) --version 2>&1 | $(EGREP) -i -c 'comeau')
SUN_COMPILER = $(shell $(CXX) -V 2>&1 | $(EGREP) -i -c 'cc: sun')
CLANG_COMPILER = $(shell $(CXX) --version 2>&1 | $(EGREP) -i -c "clang")

GCC40_OR_LATER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version (4\.[0-9]|[5-9])')
GCC41_OR_LATER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version (4\.[1-9]|[5-9])')
GCC42_OR_LATER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version (4\.[2-9]|[5-9])')
GCC43_OR_LATER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version (4\.[3-9]|[5-9])')
GCC44_OR_LATER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version (4\.[4-9]|[5-9])')
GCC45_OR_LATER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version (4\.[5-9]|[5-9])')
GCC46_OR_LATER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version (4\.[6-9]|[5-9])')
GCC47_OR_LATER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version (4\.[7-9]|[5-9])')
GCC48_OR_LATER = $(shell $(CXX) -v 2>&1 | $(EGREP) -i -c '^gcc version (4\.[8-9]|[5-9])')

# -z nodlopen: Do not allow an attacker to dlopen us
# --exclude-libs: keep other library symbols (which we depend upon) from being exported (by us)
# -z relro: Make the GOT read-only after starting to mitigate overwrite attacks
# -z now: No lazy binding to mitigate PLT attacks

# For -nodlopen, which appeared around 2000 (Binutils 2.10).
# http://sourceware.org/ml/binutils/2011-09/msg00049.html
GNU_LD210_OR_LATER = $(shell $(LD) -v 2>&1 | $(EGREP) -i -c '^gnu ld .* (2\.1[0-9]|2\.[2-9])')
# For -noexecstack and -noexecheap, which appeared around 2003 (Binutils 2.14) (see the ld/ChangeLog-2003 in BinUtils).
GNU_LD214_OR_LATER = $(shell $(LD) -v 2>&1 | $(EGREP) -i -c '^gnu ld .* (2\.1[4-9]|2\.[2-9])')
# For -relro and -now, which appeared around 6/2004 (Binutils 2.15) (see the ld/ChangeLog-2004 in BinUtils).
GNU_LD215_OR_LATER = $(shell $(LD) -v 2>&1 | $(EGREP) -i -c '^gnu ld .* (2\.1[5-9]|2\.[2-9])')
# For --exclude-libs, which appeared around 4/2002, but was ELF'd in 10/2005 
# http://sourceware.org/ml/binutils/2011-09/msg00064.html
GNU_LD216_OR_LATER = $(shell $(LD) -v 2>&1 | $(EGREP) -i -c '^gnu ld .* (2\.1[6-9]|2\.[2-9])')

# See http://code.google.com/p/owasp-esapi-cplusplus/wiki/CrossCompile
ifeq ($(IS_IOS),1)
  CXX = clang++

  IS_CROSS_COMPILE = 1
  
  # Optimize for size, not speed
  ifneq ($(ESAPI_OPTIMIZE),-O0)
    ESAPI_OPTIMIZE = -Os
  endif
endif

# See http://code.google.com/p/owasp-esapi-cplusplus/wiki/CrossCompile
ifeq ($(IS_ANDROID),1)
  IS_CROSS_COMPILE = 1

  # For shared_ptr and unordered_map
  # ESAPI_CFLAGS += -D_STLP_USE_BOOST_SUPPORT=1
  # ESAPI_CXXFLAGS += -D_STLP_USE_BOOST_SUPPORT=1
  
  # Optimize for size, not speed
  ifneq ($(ESAPI_OPTIMIZE),-O0)
    ESAPI_OPTIMIZE = -Os
  endif
  
  ifeq ($(WANT_DEBUG),1)
      ESAPI_CFLAGS += -DNDK_DEBUG=1
      ESAPI_CXXFLAGS += -DNDK_DEBUG=1
  endif
endif

# Fall back to g++ if CXX is not specified
ifeq (($strip $(CXX)),)
  CXX = g++
endif

# Unset the host switches for the cross compiled target
ifeq ($(IS_CROSS_COMPILE),1)
  IS_LINUX = 0
  IS_SOLARIS = 0
  IS_BSD = 0
  IS_DARWIN = 0
  IS_GENTOO = 0
  IS_X86_OR_X64 = 0
  
  # Cross-compile Android on Mac OS X
  ifeq ($(IS_ANDROID),1)
    IS_APPLE = 0
  endif
endif

# Fix file extension and AR/ARFLAGS for Apple platforms
ifeq ($(IS_APPLE),1)
  CXX = clang++
  AR = libtool
  ARFLAGS = -static -o
  DYNAMIC_LIB = libesapi-c++.dylib
endif

# Try and pick up SunStudio on Solaris. For whatever reason OpenSolaris is using CXX=g++
# (from the environment?), which is blowing up on OpenSolaris with a 'g++: command not found'.
# Failure is a mystery, as it appears gcc/g++ installed correctly. So we force 'CC' from
# Sun Studio, see http://opensolaris.org/jive/thread.jspa?messageID=523996.
# If Solaris is not picked up automatically, invoke make with CC: `make test CXX=CC`
ifeq ($(IS_SOLARIS),1)
  CXX = CC
endif

# Would like -fvisibility=hidden for ICC, but Intel's syntax hinders hidden by default:
# int foo(int a) __attribute__ ((visibility ("default")));
# MS and GCC allow the attribute at the beginning of the declaraion, ICC does not...
# http://software.intel.com/sites/products/documentation/studio/composer/en-us/2011/compiler_c/optaps/common/optaps_cmp_visib.htm
ifeq ($(INTEL_COMPILER),1)
  ESAPI_CFLAGS += -pipe -Wall -wd1011
  ESAPI_CXXFLAGS += -pipe -Wall -wd1011
endif

# GCC is usually a signed char, but not always (cf, ARM). We'd also like to cut the UTF-16 problem
# off at the pass, but it looks like we need to re-complile a bunch of stuff when using -fshort-wchar.
# -fwrapv: http://www.airs.com/blog/archives/120.
# http://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options
ifeq ($(GCC_COMPILER),1)
  ESAPI_CFLAGS += -pipe -fsigned-char
  ESAPI_CFLAGS += -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations
  ESAPI_CFLAGS += -Wformat=2 -Wformat-security
  ESAPI_CFLAGS += -Wuninitialized -Wshadow -Wno-unused
  ESAPI_CFLAGS += -fstrict-aliasing

  ESAPI_CXXFLAGS += -pipe -fsigned-char -Woverloaded-virtual -Wreorder
  ESAPI_CXXFLAGS += -Wformat=2 -Wformat-security
  ESAPI_CXXFLAGS += -Wuninitialized -Wno-unused
  ESAPI_CXXFLAGS += -fstrict-aliasing

  ifneq ($(IS_ANDROID),1)
    ESAPI_CFLAGS += -Wconversion
    ESAPI_CXXFLAGS += -Wconversion
  endif

#  Too much Boost noise
#  ESAPI_CXXFLAGS += -Weffc++ -Wno-non-virtual-dtor
endif

# http://gcc.gnu.org/wiki/Visibility
# http://people.redhat.com/drepper/dsohowto.pdf
ifeq ($(GCC40_OR_LATER),1)
  ESAPI_CFLAGS += -fvisibility=hidden
  ESAPI_CXXFLAGS += -fvisibility=hidden
endif

# http://gcc.gnu.org/onlinedocs/gcc-4.1.0/gcc/Optimize-Options.html
# http://www.linuxfromscratch.org/hints/downloads/files/ssp.txt
ifeq ($(GCC41_OR_LATER),1)

    # GCC 4.7 warns of FORTIFY_SOURCE with -O0 (used with Debug and Test)
    ifneq ($(WANT_DEBUG),1)
        ESAPI_CFLAGS += -D_FORTIFY_SOURCE=2
        ESAPI_CXXFLAGS += -D_FORTIFY_SOURCE=2
    endif
    ESAPI_CFLAGS += -fstack-protector-all
    ESAPI_CXXFLAGS += -fstack-protector-all
endif

# -Wstrict-overflow: http://www.airs.com/blog/archives/120
ifeq ($(GCC42_OR_LATER),1)
  ESAPI_CXXFLAGS += -Wstrict-overflow
endif

# -Wno-type-limit: for unsigned t<0 on template code, http://gcc.gnu.org/bugzilla/show_bug.cgi?id=23587
# "C++0X features first appear", http://gcc.gnu.org/onlinedocs/libstdc++/manual/api.html#api.rel_430
ifeq ($(GCC43_OR_LATER),1)
  ESAPI_CPP_STD = -std=c++0x
  ESAPI_CFLAGS += -Wall -Wextra -Wno-unused -Wtrampolines
  ESAPI_CXXFLAGS += -Wall -Wextra -Wno-unused -Wno-type-limits
  ESAPI_CXXFLAGS += -Wtrampolines
endif

# http://gcc.gnu.org/gcc-4.8/changes.htm, https://code.google.com/p/address-sanitizer/
# and http://code.google.com/p/data-race-test/wiki/ThreadSanitizer
ifeq ($(GCC48_OR_LATER),1)
  ifeq ($(WANT_DEBUG),1)
    ESAPI_CFLAGS += -fsanitize=memory -fsanitize=thread
    ESAPI_CXXFLAGS += -fsanitize=memory -fsanitize=thread
  endif
endif

# http://lists.debian.org/debian-devel/2003/10/msg01538.html
ifeq ($(IS_LINUX),1)
  ESAPI_CFLAGS += -D_REENTRANT
  ESAPI_CXXFLAGS += -D_REENTRANT
  LDLIBS += -lpthread
endif

# Options for Clang compilers
ifeq ($(CLANG_COMPILER),1)
  ESAPI_CFLAGS += -pipe -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-tautological-compare
  ESAPI_CXXFLAGS += -pipe -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-tautological-compare
    
  # Add these for Clang 3.1/3.2 and IOC (http://embed.cs.utah.edu/ioc/)
  ifneq ($(WANT_RELEASE),1)
    # ESAPI_CFLAGS += -fcatch-undefined-ansic-behavior -fcatch-undefined-c99-behavior
    # ESAPI_CFLAGS += -fcatch-undefined-cxx98-behavior -fcatch-undefined-cxx0x-behavior

    # ESAPI_CXXFLAGS += -fcatch-undefined-ansic-behavior -fcatch-undefined-c99-behavior
    # ESAPI_CXXFLAGS += -fcatch-undefined-cxx98-behavior -fcatch-undefined-cxx0x-behavior
  endif
endif

# Add paths
ESAPI_CFLAGS	+= -I. -I./esapi -I./deps
ESAPI_CXXFLAGS	+= -I. -I./esapi -I./deps

# We extract shared_ptr and use it. We don't carry around the entire Boost distribution.
# ESAPI_CFLAGS      += -I./deps/boost-1.54.0
# ESAPI_CXXFLAGS    += -I./deps/boost-1.54.0

# Everything except cross-compile gets these
ifneq ($(IS_CROSS_COMPILE),1)
  ESAPI_CFLAGS 		+= -I/usr/local/include -I/usr/include
  ESAPI_CXXFLAGS	+= -I/usr/local/include -I/usr/include
endif

ifeq ($(IS_ANDROID),1)
  ESAPI_CFLAGS      += -I./deps/boost-1.54.0
  ESAPI_CXXFLAGS    += -I./deps/boost-1.54.0
endif

# Android variables - see http://code.google.com/p/owasp-esapi-cplusplus/wiki/CrossCompile
ifeq ($(IS_ANDROID),1)
  ESAPI_CFLAGS      += -I./deps/cryptopp-541-android
  ESAPI_CXXFLAGS    += -I./deps/cryptopp-541-android

  ESAPI_CFLAGS      += --sysroot=$(ANDROID_SYSROOT)
  ESAPI_CXXFLAGS    += -I$(ANDROID_STL_INC) --sysroot=$(ANDROID_SYSROOT)
endif

# iOS variables - see http://code.google.com/p/owasp-esapi-cplusplus/wiki/CrossCompile
ifeq ($(IS_IOS),1)
  ESAPI_CFLAGS      += -I./deps/cryptopp-541-ios
  ESAPI_CXXFLAGS    += -I./deps/cryptopp-541-ios

  ESAPI_CFLAGS      += -arch $(IOS_ARCH) --sysroot=$(IOS_SYSROOT)
  ESAPI_CXXFLAGS    += -arch $(IOS_ARCH) --sysroot=$(IOS_SYSROOT)
endif

# Default prefix for make install and uninstall. The names and default values are taken from
# Stallman's GNU Make, Chapter 14, Section 4, Variables for Installation Directories
ifeq ($(prefix),)
  prefix = /usr/local
endif

ifeq ($(exec_prefix),)
  exec_prefix = $(prefix)
endif

ifeq ($(bindir),)
  bindir = $(exec_prefix)/bin
endif

ifeq ($(libdir),)
  libdir = $(exec_prefix)/lib
endif

ifeq ($(includedir),)
  includedir = $(prefix)/include
endif

ROOTSRCS =	src/EncoderConstants.cpp \
			src/ValidationErrorList.cpp \
			src/DummyConfiguration.cpp

CODECSRCS =	src/codecs/Codec.cpp \
			src/codecs/PushbackString.cpp \
			src/codecs/HTMLEntityCodec.cpp \
			src/codecs/UnixCodec.cpp \
			src/codecs/WindowsCodec.cpp \
			src/codecs/DB2Codec.cpp \
			src/codecs/MySQLCodec.cpp \
			src/codecs/LDAPCodec.cpp 

CRYPTOSRCS = src/crypto/PlainText.cpp \
			src/crypto/CipherSpec.cpp \
			src/crypto/CipherText.cpp \
			src/crypto/SecretKey.cpp \
			src/crypto/SecureRandom.cpp \
			src/crypto/SecureRandomImpl.cpp \
			src/crypto/KeyGenerator.cpp \
			src/crypto/CryptoHelper.cpp \
			src/crypto/IvParameterSpec.cpp \
			src/crypto/MessageDigest.cpp \
			src/crypto/MessageDigestImpl.cpp \
			src/crypto/RandomPool-Shared.cpp \
			src/crypto/RandomPool-Starnix.cpp \
			src/crypto/KeyDerivationFunction.cpp

ERRSRCS =   src/errors/EnterpriseSecurityException.cpp \
			src/errors/ValidationException.cpp

REFSRCS =   src/reference/Configuration.cpp \
			src/reference/DefaultEncoder.cpp \
			src/reference/DefaultEncryptor.cpp \
			src/reference/DefaultExecutor.cpp \
			src/reference/DefaultValidator.cpp \
			src/reference/PropertiesConfiguration.cpp \
			src/reference/validation/BaseValidationRule.cpp
# 			src/reference/validation/StringValidationRule.cpp

UTILSRCS =	src/util/Mutex.cpp \
			src/util/AlgorithmName.cpp \
			src/util/TextConvert-Starnix.cpp

LIBSRCS =	$(ROOTSRCS) \
			$(CODECSRCS) \
			$(CRYPTOSRCS) \
			$(ERRSRCS) \
			$(REFSRCS) \
			$(UTILSRCS)

TESTSRCS = 	test/TestMain.cpp \
			test/codecs/CodecTest.cpp \
			test/codecs/PushbackStringTest.cpp \
			test/codecs/HTMLEntityCodecTest.cpp \
			test/codecs/LDAPCodecTest.cpp \
			test/codecs/MySQLCodecTest.cpp \
			test/codecs/UnixCodecTest.cpp \
			test/crypto/PlainTextTest.cpp \
			test/crypto/CipherSpecTest.cpp \
			test/crypto/CipherTextTest.cpp \
			test/crypto/SecretKeyTest.cpp \
			test/crypto/IvParameterTest.cpp \
			test/crypto/SecureRandomTest.cpp \
			test/crypto/KeyGeneratorTest.cpp \
			test/crypto/CryptoHelperTest.cpp \
			test/crypto/MessageDigestTest.cpp \
			test/crypto/KeyDerivationFunctionTest.cpp \
			test/errors/ValidationExceptionTest.cpp \
			test/reference/ConfigurationTest1.cpp \
			test/reference/ConfigurationTest2.cpp \
			test/reference/DefaultEncoderTest.cpp \
			test/reference/DefaultEncryptorTest.cpp \
			test/reference/GenericAccessReferenceMapTest.cpp \
			test/reference/IntegerAccessReferenceMapTest.cpp \
			test/reference/RandomAccessReferenceMapTest.cpp \
			test/reference/PropertiesConfigurationTest.cpp \
			test/util/zAllocatorTest.cpp \
			test/util/AlgorithmNameTest.cpp \
			test/util/SecureByteArrayTest.cpp \
			test/util/SecureIntArrayTest.cpp \
			test/util/SecureStringTest1.cpp \
			test/util/SecureStringTest2.cpp \
			test/util/TextConvertTest.cpp
#			test/reference/validation/StringValidationRuleTest.cpp \

ROOTOBJS =		$(ROOTSRCS:.cpp=.o)
CODECOBJS =		$(CODECSRCS:.cpp=.o)
CRYPTOOBJS =	$(CRYPTOSRCS:.cpp=.o)
ERROBJS =		$(ERRCSRCS:.cpp=.o)
REFOBJS =		$(REFCSRCS:.cpp=.o)
UTILOBJS =		$(UTILSRCS:.cpp=.o)

LIBOBJS =		$(LIBSRCS:.cpp=.o)

TESTOBJS =		$(TESTSRCS:.cpp=.o)

ifneq ($(IS_CROSS_COMPILE),1)
  ESAPI_LDFLAGS +=	-L/usr/local/lib -L/usr/lib
endif

# Linker hardening
ifeq ($(GNU_LD210_OR_LATER),1)
  ESAPI_LDFLAGS +=	-Wl,-z,nodlopen -Wl,-z,nodump
endif

# No-exec the heap and the stack (this is a best effort, the kernel or PaX might ignore)
# PT_GNU_HEAP is a Gentoo extension. Also see http://www.airs.com/blog/archives/518
ifeq ($(GNU_LD214_OR_LATER),1)
  ESAPI_LDFLAGS +=	-Wl,-z,noexecstack
  ifeq ($(IS_GENTOO),1)
    ESAPI_LDFLAGS += -Wl,-z,noexecheap
  endif
endif

# Linker hardening
ifeq ($(GNU_LD215_OR_LATER),1)
  ESAPI_LDFLAGS +=	-Wl,-z,relro -Wl,-z,now
endif

# Add -PIE to x86 executables (missing on HPPA, ARM, and others)
ifeq ($(GNU_LD216_OR_LATER),1)
  ifeq ($(IS_X86_OR_X64),1)
    EXE_ASLR = -fpie -Wl,-pie
  endif
endif

# Reduce the size of the export table
ifeq ($(GNU_LD216_OR_LATER),1)
  ESAPI_LDFLAGS += -Wl,--exclude-libs,ALL
endif

ifneq ($(IS_CROSS_COMPILE),1)
  ESAPI_LDLIBS += -lpthread -lcryptopp -lboost_regex -lboost_system
endif

# iconvert library. For GNU Linux, its included in glibc
ifeq ($(IS_BSD),1)
  ESAPI_LDLIBS += -liconv
endif

ifeq ($(IS_DARWIN),1)
  ESAPI_LDLIBS += -liconv
endif

ifeq ($(IS_IOS),1)
  ESAPI_LDLIBS += -liconv ./deps/cryptopp-541-ios/armv7x/libcryptopp.a
endif

ifeq ($(IS_ANDROID),1)
  ESAPI_LDLIBS += $(ANDROID_STL_LIB) ./deps/cryptopp-541-android/armv7/libcryptopp.a
endif

# Merge ESAPI flags with user supplied flags. We perform the extra step to ensure
# user options follow our options, which should give user option's preference.
override CFLAGS   := $(ESAPI_CFLAGS) $(CFLAGS)
override CXXFLAGS := $(ESAPI_CPP_STD) $(ESAPI_CXXFLAGS) $(CXXFLAGS)
override LDFLAGS  := $(ESAPI_LDFLAGS) $(LDFLAGS)
override LDLIBS   := $(ESAPI_LDLIBS) $(LDLDLIBS)

TEST_CXXFLAGS += $(CXXFLAGS)
TEST_LDFLAGS  += $(ESAPI_LDFLAGS)
TEST_LDLIBS   += $(LDLIBS) -lboost_unit_test_framework

# No extension, so no implicit rule. Hence we provide an empty rule for the dependency.
TEST_TARGET = test/run_esapi_tests

# `make all` builds the DSO and Archive. OPT=O2, SYM=G1, Asserts are off.
all: $(STATIC_LIB) $(DYNAMIC_LIB)
static: $(STATIC_LIB)
dynamic: $(DYNAMIC_LIB)

# If you are missing libcrypto++ or libcryptopp, see
# https://code.google.com/p/owasp-esapi-cplusplus/wiki/DevPrerequisites
$(DYNAMIC_LIB):	$(LIBOBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o lib/$@ $(LIBOBJS) $(LDFLAGS) -shared $(LDLIBS)

$(STATIC_LIB): $(LIBOBJS)
	$(AR) $(ARFLAGS) lib/$@ $(LIBOBJS)
	$(RANLIB) lib/$@

# `make debug` builds the DSO and runs the tests. OPT=O0, SYM=G3, ASSERTs are on.
debug: $(DYNAMIC_LIB) test

# `make release` is `make all`. OPT=O2, SYM=G1, ASSERTs are off.
release: $(DYNAMIC_LIB) test

# `make test` builds the DSO and runs the tests. OPT=O2, SYM=G3, ASSERTs are off.
test check: $(DYNAMIC_LIB) $(TESTOBJS) $(TEST_TARGET)
	$(CXX) $(CPPFLAGS) $(TEST_CXXFLAGS) $(EXE_ASLR) -o $(TEST_TARGET) $(TESTOBJS) $(TEST_LDFLAGS) $(TEST_LDLIBS) lib/$(DYNAMIC_LIB)
	./$(TEST_TARGET)

directories:
	-$(MKDIR) -p $(includedir)/esapi/codecs
	-$(MKDIR) -p $(includedir)/esapi/crypto
	-$(MKDIR) -p $(includedir)/esapi/errors
	-$(MKDIR) -p $(includedir)/esapi/reference
	-$(MKDIR) -p $(includedir)/esapi/util
	-$(MKDIR) -p $(includedir)/esapi/reference/validation

install: directories
	$(CP) -r esapi/* $(includedir)/esapi
	-$(CP) lib/$(STATIC_LIB) $(libdir)/$(STATIC_LIB)
	-$(CP) lib/$(DYNAMIC_LIB) $(libdir)/$(DYNAMIC_LIB)

uninstall:
	-$(RM) -rf $(includedir)/esapi
	-$(RM) -f $(libdir)/$(STATIC_LIB)
	-$(RM) -f $(libdir)/$(DYNAMIC_LIB)

# Test compile codec sources, no final link
codec codecs: $(CODECOBJS)

# Test compile crypto sources, no final link
crypto: $(CRYPTOOBJS)

# Test compile error sources, no final link
err error: $(ERROBJS)

# Test compile reference sources, no final link
ref reference: $(REFOBJS)

# Test compile utility sources, no final link
util: $(UTILOBJS)

.cpp.o:
	$(CXX) $(CPPFLAGS) -fpic $(CXXFLAGS) -c $< -o $@

.c.o:
	$(CXX) $(CPPFLAGS) -fpic $(CFLAGS) -c $< -o $@

# Empty target to satisy its use as a dependency in `make {test|check}`
$(TEST_TARGET): ;

.PHONY: clean
clean:
	-rm -f $(LIBOBJS) lib/$(STATIC_LIB) lib/$(DYNAMIC_LIB) $(TESTOBJS) $(TEST_TARGET) $(TEST_TARGET).* *.dSYM core *.core

