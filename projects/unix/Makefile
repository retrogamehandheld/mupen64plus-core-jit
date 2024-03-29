#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# *   Mupen64plus - Makefile                                                *
# *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
# *   Copyright (C) 2008-2009 Richard Goedeken                              *
# *   Copyright (C) 2007-2008 DarkJeztr Tillin9                             *
# *                                                                         *
# *   This program is free software; you can redistribute it and/or modify  *
# *   it under the terms of the GNU General Public License as published by  *
# *   the Free Software Foundation; either version 2 of the License, or     *
# *   (at your option) any later version.                                   *
# *                                                                         *
# *   This program is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU General Public License for more details.                          *
# *                                                                         *
# *   You should have received a copy of the GNU General Public License     *
# *   along with this program; if not, write to the                         *
# *   Free Software Foundation, Inc.,                                       *
# *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
# Makefile for Mupen64Plus Core

# detect operating system
UNAME ?= $(shell uname -s)
OS := NONE
ifeq ("$(UNAME)","Linux")
  OS = LINUX
endif
ifeq ("$(UNAME)","linux")
  OS = LINUX
endif
ifneq ("$(filter GNU hurd,$(UNAME))","")
  OS = LINUX
endif
ifeq ("$(UNAME)","Darwin")
  OS = OSX
endif
ifeq ("$(UNAME)","FreeBSD")
  OS = FREEBSD
endif
ifeq ("$(UNAME)","OpenBSD")
  OS = FREEBSD
  CFLAGS += -DIOAPI_NO_64
endif
ifneq ("$(filter GNU/kFreeBSD kfreebsd,$(UNAME))","")
  OS = LINUX
endif
ifeq ("$(patsubst MINGW%,MINGW,$(UNAME))","MINGW")
  OS = MINGW
  PIC = 0
endif
ifeq ("$(OS)","NONE")
  $(error OS type "$(UNAME)" not supported.  Please file bug report at 'http://code.google.com/p/mupen64plus/issues')
endif

# detect system architecture
HOST_CPU ?= $(shell uname -m)
CPU := NONE
ifneq ("$(filter x86_64 amd64,$(HOST_CPU))","")
  CPU := X86
  ifeq ("$(BITS)", "32")
    ARCH_DETECTED := 64BITS_32
    PIC ?= 0
  else
    ARCH_DETECTED := 64BITS
    PIC ?= 1
  endif
endif
ifneq ("$(filter pentium i%86,$(HOST_CPU))","")
  CPU := X86
  ARCH_DETECTED := 32BITS
  PIC ?= 0
endif
ifneq ("$(filter ppc macppc socppc powerpc,$(HOST_CPU))","")
  CPU := PPC
  ARCH_DETECTED := 32BITS
  BIG_ENDIAN := 1
  PIC ?= 1
  NO_ASM := 1
  $(warning Architecture "$(HOST_CPU)" not officially supported.')
endif
ifneq ("$(filter ppc64 powerpc64,$(HOST_CPU))","")
  CPU := PPC
  ARCH_DETECTED := 64BITS
  BIG_ENDIAN := 1
  PIC ?= 1
  NO_ASM := 1
  $(warning Architecture "$(HOST_CPU)" not officially supported.')
endif
ifneq ("$(filter arm%,$(HOST_CPU))","")
  ifeq ("$(filter arm%b,$(HOST_CPU))","")
    CPU := ARM
    ARCH_DETECTED := 32BITS
    PIC ?= 1
    NEW_DYNAREC := 1
    CFLAGS += -marm
    ifneq ("$(filter armv5%,$(HOST_CPU))","")
    	CFLAGS += -DARMv5_ONLY
    	$(warning Using ARMv5_ONLY)
    endif
    ifneq ("$(filter armv6%,$(HOST_CPU))","")
    	CFLAGS += -DARMv5_ONLY
    	$(warning Using ARMv5_ONLY)
    endif
    ifeq ($(NEON), 1)
        CFLAGS += -mfpu=neon -mfloat-abi=hard
    else
      ifeq ($(VFP_HARD), 1)
        CFLAGS += -mfpu=vfp -mfloat-abi=hard
      else
        CFLAGS += -mfpu=vfp -mfloat-abi=softfp
      endif
    endif
    $(warning Architecture "$(HOST_CPU)" not officially supported.')
  endif
endif
ifneq ("$(filter mips,$(HOST_CPU))","")
  CPU := MIPS
  ARCH_DETECTED := 32BITS
  PIC ?= 1
  NO_ASM := 1
  $(warning Architecture "$(HOST_CPU)" not officially supported.')
endif
ifeq ("$(CPU)","NONE")
  $(error CPU type "$(HOST_CPU)" not supported.  Please file bug report at 'http://code.google.com/p/mupen64plus/issues')
endif

# base CFLAGS, LDLIBS, and LDFLAGS
OPTFLAGS ?= -O3 -flto
WARNFLAGS ?= -Wall -Wno-unused-function
CFLAGS += $(OPTFLAGS) $(WARNFLAGS) -ffast-math -fno-strict-aliasing -fvisibility=hidden -I../../src -DM64P_PARALLEL
CXXFLAGS += -fvisibility-inlines-hidden
LDLIBS +=  -lm

# Since we are building a shared library, we must compile with -fPIC on some architectures
# On 32-bit x86 systems we do not want to use -fPIC because we don't have to and it has a big performance penalty on this arch
ifeq ($(PIC), 1)
  CFLAGS += -fPIC
else
  CFLAGS += -fno-PIC
endif

ifeq ($(BIG_ENDIAN), 1)
  CFLAGS += -DM64P_BIG_ENDIAN
endif

# tweak flags for 32-bit build on 64-bit system
ifeq ($(ARCH_DETECTED), 64BITS_32)
  ifeq ($(OS), FREEBSD)
    $(error Do not use the BITS=32 option with FreeBSD, use -m32 and -m elf_i386)
  endif
  CFLAGS += -m32
  LDFLAGS += -Wl,-m,elf_i386
endif

# set special flags per-system
ifeq ($(OS), FREEBSD)
  TARGET = libmupen64plus$(POSTFIX).so.2.0.0
  SONAME = libmupen64plus$(POSTFIX).so.2
  LDFLAGS += -Wl,-Bsymbolic -shared -Wl,-export-dynamic -Wl,-soname,$(SONAME)
  LDLIBS += -L${LOCALBASE}/lib -lc
  ASFLAGS = -f elf -d ELF_TYPE
endif
ifeq ($(OS), LINUX)
  TARGET = libmupen64plus$(POSTFIX).so.2.0.0
  SONAME = libmupen64plus$(POSTFIX).so.2
  LDFLAGS += -Wl,-Bsymbolic -shared -Wl,-export-dynamic -Wl,-soname,$(SONAME)
  LDLIBS += -ldl
  # only export api symbols
  LDFLAGS += -Wl,-version-script,$(SRCDIR)/api/api_export.ver
  ASFLAGS = -f elf -d ELF_TYPE
endif
ifeq ($(OS), OSX)
  #xcode-select has been around since XCode 3.0, i.e. OS X 10.5
  OSX_SDK_ROOT = $(shell xcode-select -print-path)/Platforms/MacOSX.platform/Developer/SDKs
  OSX_SDK_PATH = $(OSX_SDK_ROOT)/$(shell ls $(OSX_SDK_ROOT) | tail -1)

  TARGET = libmupen64plus$(POSTFIX).dylib
  LDFLAGS += -framework CoreFoundation -bundle -read_only_relocs suppress
  LDLIBS += -ldl
  ASFLAGS = -f macho
  ifeq ($(CPU), X86)
    ifeq ($(ARCH_DETECTED), 64BITS)
      CFLAGS += -pipe -arch x86_64 -mmacosx-version-min=10.5 -isysroot $(OSX_SDK_PATH)
    else
      CFLAGS += -pipe -mmmx -msse -arch i686 -mmacosx-version-min=10.5 -isysroot $(OSX_SDK_PATH)
      ifneq ($(PROFILE), 1)
        CFLAGS += -fomit-frame-pointer
      endif
    endif
  endif
endif
ifeq ($(OS), MINGW)
  TARGET = mupen64plus$(POSTFIX).dll
  LDFLAGS += -Wl,-Bsymbolic -shared -Wl,-export-all-symbols
  # only export api symbols
  LDFLAGS += -Wl,-version-script,$(SRCDIR)/api/api_export.ver
  LDLIBS += -lpthread
  ASFLAGS = -f win32
endif

ifeq ($(CPU_ENDIANNESS), BIG)
  CFLAGS += -DM64P_BIG_ENDIAN
endif

# disable verbose output
ifneq ($(findstring $(MAKEFLAGS),s),s)
ifndef V
	Q_CC  = @echo '    CC  '$@;
	Q_CXX = @echo '    CXX '$@;
	Q_AS  = @echo '    AS  '$@;
	Q_LD  = @echo '    LD  '$@;
endif
endif

# test for essential build dependencies
ifeq ($(origin PKG_CONFIG), undefined)
  PKG_CONFIG = $(CROSS_COMPILE)pkg-config
  ifeq ($(shell which $(PKG_CONFIG) 2>/dev/null),)
    $(error $(PKG_CONFIG) not found)
  endif
endif

ifeq ($(OS), OSX) # use system zlib on OSX
  ZLIB_LDLIBS += -lz
endif

ifeq ($(origin ZLIB_CFLAGS) $(origin ZLIB_LDLIBS), undefined undefined)
  ifeq ($(shell $(PKG_CONFIG) --modversion zlib 2>/dev/null),)
    $(error No zlib development libraries found!)
  endif
  ZLIB_CFLAGS += $(shell $(PKG_CONFIG) --cflags zlib)
  ZLIB_LDLIBS +=  $(shell $(PKG_CONFIG) --libs zlib)
endif
CFLAGS += $(ZLIB_CFLAGS)
LDLIBS += $(ZLIB_LDLIBS)

ifeq ($(origin LIBPNG_CFLAGS) $(origin LIBPNG_LDLIBS), undefined undefined)
  ifeq ($(shell $(PKG_CONFIG) --modversion libpng 2>/dev/null),)
    $(error No libpng development libraries found!)
  endif
  LIBPNG_CFLAGS += $(shell $(PKG_CONFIG) --cflags libpng)
  LIBPNG_LDLIBS +=  $(shell $(PKG_CONFIG) --libs libpng)
endif
CFLAGS += $(LIBPNG_CFLAGS)
LDLIBS += $(LIBPNG_LDLIBS)

# test for presence of SDL
ifeq ($(origin SDL_CFLAGS) $(origin SDL_LDLIBS), undefined undefined)
  SDL_CONFIG = $(CROSS_COMPILE)sdl2-config
  ifeq ($(shell which $(SDL_CONFIG) 2>/dev/null),)
    SDL_CONFIG = $(CROSS_COMPILE)sdl-config
    ifeq ($(shell which $(SDL_CONFIG) 2>/dev/null),)
      $(error No SDL development libraries found!)
    else
      $(warning Using SDL 1.2 libraries)
    endif
  endif
  SDL_CFLAGS  += $(shell $(SDL_CONFIG) --cflags)
  SDL_LDLIBS += $(shell $(SDL_CONFIG) --libs)
endif
CFLAGS += $(SDL_CFLAGS)
LDLIBS += $(SDL_LDLIBS)

ifeq ($(VC), 1)
  CFLAGS += -DUSE_GLES -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/vmcs_host/linux
  LDLIBS += -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lvcos -lvchiq_arm
  # OSD uses non-ES code and breaks attribs of video plugins
  OSD=0
endif

ifeq ($(USE_GLES), 1)
  CFLAGS += -DUSE_GLES
  LDLIBS += -lGLESv2
  # OSD uses non-ES code and breaks attribs of video plugins
  OSD=0
endif

OSD ?= 1
ifeq ($(OSD), 1)
  CFLAGS += -DM64P_OSD

  ifeq ($(origin FREETYPE2_CFLAGS) $(origin FREETYPE2_LDLIBS), undefined undefined)
    ifeq ($(shell $(PKG_CONFIG) --modversion freetype2 2>/dev/null),)
      $(error No freetype2 development libraries found!)
    endif
    FREETYPE2_CFLAGS += $(shell $(PKG_CONFIG) --cflags freetype2)
    FREETYPE2_LDLIBS +=  $(shell $(PKG_CONFIG) --libs freetype2)
  endif
  CFLAGS += $(FREETYPE2_CFLAGS)
  LDLIBS += $(FREETYPE2_LDLIBS)

  # search for OpenGL libraries
  ifeq ($(OS), OSX)
    GL_LDLIBS = -framework OpenGL
    GLU_LDLIBS = -framework OpenGL
  endif
  ifeq ($(OS), MINGW)
    GL_LDLIBS = -lopengl32
    GLU_LDLIBS = -lglu32
  endif

  ifeq ($(origin GL_CFLAGS) $(origin GL_LDLIBS), undefined undefined)
    ifeq ($(shell $(PKG_CONFIG) --modversion gl 2>/dev/null),)
      $(error No OpenGL development libraries found!)
    endif
    GL_CFLAGS += $(shell $(PKG_CONFIG) --cflags gl)
    GL_LDLIBS +=  $(shell $(PKG_CONFIG) --libs gl)
  endif
  CFLAGS += $(GL_CFLAGS)
  LDLIBS += $(GL_LDLIBS)

  ifeq ($(origin GLU_CFLAGS) $(origin GLU_LDLIBS), undefined undefined)
    ifeq ($(shell $(PKG_CONFIG) --modversion glu 2>/dev/null),)
      $(error No OpenGL utility development libraries found!)
    endif
    GLU_CFLAGS += $(shell $(PKG_CONFIG) --cflags glu)
    GLU_LDLIBS +=  $(shell $(PKG_CONFIG) --libs glu)
  endif
  CFLAGS += $(GLU_CFLAGS)
  LDLIBS += $(GLU_LDLIBS)
endif

# set base program pointers and flags
CC        = $(CROSS_COMPILE)gcc
CXX       = $(CROSS_COMPILE)g++
AS        = nasm
RM       ?= rm -f
INSTALL  ?= install
MKDIR ?= mkdir -p
COMPILE.c = $(Q_CC)$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cc = $(Q_CXX)$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.as = $(Q_AS)$(AS) $(ASFLAGS)
LINK.o = $(Q_LD)$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TARGET_ARCH)

ifeq ($(OS),OSX)
  LDCONFIG ?= true  # no 'ldconfig' under OSX
else
  ifeq ($(OS),LINUX)
    LDCONFIG ?= PATH="$$PATH:/sbin" ldconfig -n
  endif
  ifeq ($(OS),FREEBSD)
    LDCONFIG ?= PATH="$$PATH:/sbin" ldconfig -m
  endif
endif

# compiler/linker flags for various compile-time options.
# 1. macro for no assembly language
ifeq ($(NO_ASM), 1)
  CFLAGS += -DNO_ASM
endif
# 2. variables for profiling and adding debugging symbols
ifeq ($(PROFILE), 1)
  CFLAGS += -pg -g
  INSTALL_STRIP_FLAG ?= 
else
  ifeq ($(DEBUG), 1)
    CFLAGS += -g
    INSTALL_STRIP_FLAG ?= 
  else
    ifneq ($(OS),OSX)
      INSTALL_STRIP_FLAG ?= -s
	endif
  endif
endif
# 3. other options given to the makefile on the command line
ifeq ($(LIRC), 1)
  CFLAGS += -DWITH_LIRC
endif
ifeq ($(DEBUGGER), 1)
  CFLAGS += -DDBG
endif
ifeq ($(DBG_COMPARE), 1)
  CFLAGS += -DCOMPARE_CORE
endif
ifeq ($(DBG_CORE), 1)
  CFLAGS += -DCORE_DBG
endif
ifeq ($(DBG_COUNT), 1)
  CFLAGS += -DCOUNT_INSTR
endif
ifeq ($(DBG_TIMING), 1)
  CFLAGS += -DPROFILE
  LDFLAGS += -lrt
endif
ifeq ($(DBG_PROFILE), 1)
  CFLAGS += -DPROFILE_R4300
endif
# 4. compile-time directory paths for building into the library
ifneq ($(SHAREDIR),)
  CFLAGS += -DSHAREDIR="$(SHAREDIR)"
endif

# set installation options
ifeq ($(PREFIX),)
  PREFIX := /usr/local
endif
ifeq ($(SHAREDIR),)
  SHAREDIR := $(PREFIX)/share/mupen64plus
endif
ifeq ($(LIBDIR),)
  LIBDIR := $(PREFIX)/lib
endif
ifeq ($(INCDIR),)
  INCDIR := $(PREFIX)/include/mupen64plus
endif

SRCDIR = ../../src
OBJDIR = _obj$(POSTFIX)

# list of required source files for compilation
SOURCE = \
	$(SRCDIR)/ai/ai_controller.c \
	$(SRCDIR)/api/callbacks.c \
	$(SRCDIR)/api/common.c \
	$(SRCDIR)/api/config.c \
	$(SRCDIR)/api/debugger.c \
	$(SRCDIR)/api/frontend.c \
	$(SRCDIR)/api/vidext.c \
	$(SRCDIR)/main/main.c \
	$(SRCDIR)/main/util.c \
	$(SRCDIR)/main/cheat.c \
	$(SRCDIR)/main/eep_file.c \
	$(SRCDIR)/main/eventloop.c \
	$(SRCDIR)/main/fla_file.c \
	$(SRCDIR)/main/md5.c \
	$(SRCDIR)/main/mpk_file.c \
	$(SRCDIR)/main/profile.c \
	$(SRCDIR)/main/rom.c \
	$(SRCDIR)/main/savestates.c \
	$(SRCDIR)/main/sdl_key_converter.c \
	$(SRCDIR)/main/sra_file.c \
	$(SRCDIR)/main/workqueue.c \
	$(SRCDIR)/memory/memory.c \
	$(SRCDIR)/pi/cart_rom.c \
	$(SRCDIR)/pi/flashram.c \
	$(SRCDIR)/pi/pi_controller.c \
	$(SRCDIR)/pi/sram.c \
	$(SRCDIR)/plugin/emulate_game_controller_via_input_plugin.c \
	$(SRCDIR)/plugin/emulate_speaker_via_audio_plugin.c \
	$(SRCDIR)/plugin/get_time_using_C_localtime.c \
	$(SRCDIR)/plugin/rumble_via_input_plugin.c \
	$(SRCDIR)/plugin/plugin.c \
	$(SRCDIR)/plugin/dummy_video.c \
	$(SRCDIR)/plugin/dummy_audio.c \
	$(SRCDIR)/plugin/dummy_input.c \
	$(SRCDIR)/plugin/dummy_rsp.c \
	$(SRCDIR)/r4300/r4300.c \
	$(SRCDIR)/r4300/cached_interp.c \
	$(SRCDIR)/r4300/cp0.c \
	$(SRCDIR)/r4300/cp1.c \
	$(SRCDIR)/r4300/exception.c \
	$(SRCDIR)/r4300/instr_counters.c \
	$(SRCDIR)/r4300/interupt.c \
	$(SRCDIR)/r4300/mi_controller.c \
	$(SRCDIR)/r4300/pure_interp.c \
	$(SRCDIR)/r4300/r4300_core.c \
	$(SRCDIR)/r4300/recomp.c \
	$(SRCDIR)/r4300/reset.c \
	$(SRCDIR)/r4300/tlb.c \
	$(SRCDIR)/rdp/fb.c \
	$(SRCDIR)/rdp/rdp_core.c \
	$(SRCDIR)/ri/rdram.c \
	$(SRCDIR)/ri/rdram_detection_hack.c \
	$(SRCDIR)/ri/ri_controller.c \
	$(SRCDIR)/rsp/rsp_core.c \
	$(SRCDIR)/si/af_rtc.c \
	$(SRCDIR)/si/cic.c \
	$(SRCDIR)/si/eeprom.c \
	$(SRCDIR)/si/game_controller.c \
	$(SRCDIR)/si/mempak.c \
	$(SRCDIR)/si/n64_cic_nus_6105.c \
	$(SRCDIR)/si/pif.c \
	$(SRCDIR)/si/rumblepak.c \
	$(SRCDIR)/si/si_controller.c \
	$(SRCDIR)/vi/vi_controller.c \
	$(SRCDIR)/osd/screenshot.cpp \
	$(SRCDIR)/r4300/trace_jit/mips-analysis.c \
	$(SRCDIR)/r4300/trace_jit/mips-interp.c \
	$(SRCDIR)/r4300/trace_jit/mips-jit.c \
	$(SRCDIR)/r4300/trace_jit/mips-simplify.c \
	$(SRCDIR)/r4300/trace_jit/mips-tracebounds.c \
	$(SRCDIR)/r4300/trace_jit/native-tracecache.c \
	$(SRCDIR)/r4300/trace_jit/dummy/functions.c \
	$(SRCDIR)/r4300/trace_jit/x86-64/functions.c \
	$(SRCDIR)/r4300/trace_jit/mips32/functions.c \
	$(SRCDIR)/r4300/trace_jit/mips32/mips-alu.c \
	$(SRCDIR)/r4300/trace_jit/mips32/mips-branch.c \
	$(SRCDIR)/r4300/trace_jit/mips32/mips-common.c \
	$(SRCDIR)/r4300/trace_jit/mips32/mips-cp0.c \
	$(SRCDIR)/r4300/trace_jit/mips32/mips-cp1.c \
	$(SRCDIR)/r4300/trace_jit/mips32/mips-emit.c \
	$(SRCDIR)/r4300/trace_jit/mips32/mips-except.c \
	$(SRCDIR)/r4300/trace_jit/mips32/mips-mdu.c \
	$(SRCDIR)/r4300/trace_jit/mips32/mips-memory.c \
	$(SRCDIR)/r4300/trace_jit/mips32/native-ops.c \
	$(SRCDIR)/r4300/trace_jit/mips32/native-regcache.c \
	$(SRCDIR)/r4300/trace_jit/mips32/native-utils.c
ifeq ("$(OS)","MINGW")
SOURCE += \
	$(SRCDIR)/osal/dynamiclib_win32.c \
	$(SRCDIR)/osal/files_win32.c
else
SOURCE += \
	$(SRCDIR)/osal/dynamiclib_unix.c \
	$(SRCDIR)/osal/files_unix.c
endif

ifeq ($(OSD), 1)
SOURCE += \
	$(SRCDIR)/osd/OGLFT.cpp \
	$(SRCDIR)/osd/osd.cpp
endif

# source files for optional features
ifneq ($(NO_ASM), 1)
  ifeq ($(CPU), X86)
    ifeq ($(ARCH_DETECTED), 64BITS)
      DYNAREC = x86_64
    else
      DYNAREC = x86
    endif
  endif
  ifeq ($(CPU), ARM)
    ifeq ($(ARCH_DETECTED), 32BITS)
      DYNAREC = arm
    endif
  endif
endif
ifneq ($(DYNAREC), )
  CFLAGS += -DDYNAREC

  ifeq ($(NEW_DYNAREC), 1)
    ifeq ($(DYNAREC), x86)
      CFLAGS += -DNEW_DYNAREC=1
      SOURCE += \
	    $(SRCDIR)/r4300/new_dynarec/x86/linkage_x86.asm
    else
      ifeq ($(DYNAREC), arm)
        CFLAGS += -DNEW_DYNAREC=3
        SOURCE += \
         $(SRCDIR)/r4300/new_dynarec/arm/linkage_arm.S \
         $(SRCDIR)/r4300/new_dynarec/arm/arm_cpu_features.c
      else
        $(error NEW_DYNAREC is only supported on 32 bit x86 and 32 bit armel)
      endif
    endif

    SOURCE += \
      $(SRCDIR)/r4300/empty_dynarec.c \
      $(SRCDIR)/r4300/new_dynarec/new_dynarec.c
  else
    SOURCE += \
      $(SRCDIR)/r4300/$(DYNAREC)/assemble.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gbc.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gcop0.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gcop1.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gcop1_d.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gcop1_l.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gcop1_s.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gcop1_w.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gr4300.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gregimm.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gspecial.c \
      $(SRCDIR)/r4300/$(DYNAREC)/gtlb.c \
      $(SRCDIR)/r4300/$(DYNAREC)/regcache.c \
      $(SRCDIR)/r4300/$(DYNAREC)/rjump.c
  endif
else
  SOURCE += $(SRCDIR)/r4300/empty_dynarec.c
endif

ifeq ($(LIRC), 1)
  SOURCE += $(SRCDIR)/main/lirc.c
  LDLIBS += -llirc_client
endif

ifeq ($(shell $(PKG_CONFIG) --modversion minizip 2>/dev/null),)
  SOURCE += \
	$(SRCDIR)/main/zip/ioapi.c \
	$(SRCDIR)/main/zip/zip.c \
	$(SRCDIR)/main/zip/unzip.c

  CFLAGS += -DNOCRYPT -DNOUNCRYPT
else
  CFLAGS += $(shell $(PKG_CONFIG) --cflags minizip) -DLIBMINIZIP
  LDLIBS +=  $(shell $(PKG_CONFIG) --libs minizip)
endif


ifeq ($(DEBUGGER), 1)
  SOURCE += \
	$(SRCDIR)/debugger/dbg_debugger.c \
	$(SRCDIR)/debugger/dbg_decoder.c \
	$(SRCDIR)/debugger/dbg_memory.c \
	$(SRCDIR)/debugger/dbg_breakpoints.c
  LDLIBS += -lopcodes -lbfd
endif

# generate a list of object files to build, make a temporary directory for them
OBJECTS := $(patsubst $(SRCDIR)/%.c,   $(OBJDIR)/%.o, $(filter %.c,   $(SOURCE)))
OBJECTS += $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter %.cpp, $(SOURCE)))
OBJECTS += $(patsubst $(SRCDIR)/%.S, $(OBJDIR)/%.o, $(filter %.S, $(SOURCE)))
OBJECTS += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%.o, $(filter %.asm, $(SOURCE)))
OBJDIRS = $(dir $(OBJECTS))
$(shell $(MKDIR) $(OBJDIRS))

# build targets
targets:
	@echo "Mupen64Plus-core makefile. "
	@echo "  Targets:"
	@echo "    all           == Build Mupen64Plus core library"
	@echo "    clean         == remove object files"
	@echo "    install       == Install Mupen64Plus core library"
	@echo "    uninstall     == Uninstall Mupen64Plus core library"
	@echo "  Build Options:"
	@echo "    BITS=32       == build 32-bit binaries on 64-bit machine"
	@echo "    LIRC=1        == enable LIRC support"
	@echo "    NO_ASM=1      == build without assembly (no dynamic recompiler or MMX/SSE code)"
	@echo "    USE_GLES=1    == build against GLESv2 instead of OpenGL"
	@echo "    VC=1 	 == build against Broadcom Videocore GLESv2"
	@echo "    NEON=1        == (ARM only) build for hard floating point environments"
	@echo "    VFP_HARD=1 	 == (ARM only) full hardware floating point ABI"
	@echo "    SHAREDIR=path == extra path to search for shared data files"
	@echo "    OPTFLAGS=flag == compiler optimization (default: -O3 -flto)"
	@echo "    WARNFLAGS=flag == compiler warning levels (default: -Wall)"
	@echo "    PIC=(1|0)     == Force enable/disable of position independent code"
	@echo "    OSD=(1|0)     == Enable/disable build of OpenGL On-screen display"
	@echo "    NEW_DYNAREC=1 == Replace dynamic recompiler with Ari64's experimental dynarec"
	@echo "    POSTFIX=name  == String added to the name of the the build (default: '')"
	@echo "  Install Options:"
	@echo "    PREFIX=path   == install/uninstall prefix (default: /usr/local/)"
	@echo "    SHAREDIR=path == path to install shared data files (default: PREFIX/share/mupen64plus)"
	@echo "    LIBDIR=path   == path to install core library (default: PREFIX/lib)"
	@echo "    INCDIR=path   == path to install core header files (default: PREFIX/include/mupen64plus)"
	@echo "    DESTDIR=path  == path to prepend to all installation paths (only for packagers)"
	@echo "  Debugging Options:"
	@echo "    PROFILE=1     == build gprof instrumentation into binaries for profiling"
	@echo "    DEBUG=1       == add debugging symbols to binaries"
	@echo "    DEBUGGER=1    == build debugger API into core for front-ends.  runs slower."
	@echo "    DBG_CORE=1    == print debugging info in r4300 core"
	@echo "    DBG_COUNT=1   == print R4300 instruction count totals (64-bit dynarec only)"
	@echo "    DBG_COMPARE=1 == enable core-synchronized r4300 debugging"
	@echo "    DBG_TIMING=1  == print timing data"
	@echo "    DBG_PROFILE=1 == dump profiling data for r4300 dynarec to data file"
	@echo "    V=1           == show verbose compiler output"

all: $(TARGET)

install: $(TARGET)
	$(INSTALL) -d "$(DESTDIR)$(LIBDIR)"
	$(INSTALL) -m 0644 $(INSTALL_STRIP_FLAG) $(TARGET) "$(DESTDIR)$(LIBDIR)"
	$(INSTALL) -d "$(DESTDIR)$(SHAREDIR)"
	$(INSTALL) -m 0644 ../../data/* "$(DESTDIR)$(SHAREDIR)"
	$(INSTALL) -d "$(DESTDIR)$(INCDIR)"
	$(INSTALL) -m 0644 ../../src/api/m64p_*.h "$(DESTDIR)$(INCDIR)"
	-$(LDCONFIG) "$(DESTDIR)$(LIBDIR)"
	if [ ! -e "$(DESTDIR)$(LIBDIR)/$(SONAME)" ]; then ln -sf "$(TARGET)" "$(DESTDIR)$(LIBDIR)/$(SONAME)"; fi

uninstall:
	$(RM) "$(DESTDIR)$(LIBDIR)/$(TARGET)"
	if [ "$(SONAME)" != "" ]; then $(RM) "$(DESTDIR)$(LIBDIR)/$(SONAME)"; fi
	$(RM) $(DESTDIR)$(INCDIR)/m64p_*.h
	$(RM) "$(DESTDIR)$(SHAREDIR)/mupen64plus.ini"
	$(RM) "$(DESTDIR)$(SHAREDIR)/font.ttf"
	$(RM) "$(DESTDIR)$(SHAREDIR)/mupencheat.txt"

clean:
	$(RM) -r $(TARGET) $(SONAME) $(OBJDIR)

# build dependency files
CFLAGS += -MD -MP
-include $(OBJECTS:.o=.d)

CXXFLAGS += $(CFLAGS)

# standard build rules
$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	$(COMPILE.as) -o $@ $<
	
$(OBJDIR)/%.o: $(SRCDIR)/%.S
	$(COMPILE.c) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(COMPILE.c) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(COMPILE.cc) -o $@ $<

$(TARGET): $(OBJECTS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
	if [ "$(SONAME)" != "" ]; then ln -sf $@ $(SONAME); fi

.PHONY: all clean install uninstall targets
