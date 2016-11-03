SHELL := /bin/bash
RM := rm -Rf

BUILDDIR = ./build/
BINDIR = ./bin
LIBDIR = ./lib
INSTALLDIR = .
INSTALLDIR_BIN = ./bin
INSTALLDIR_LIB = ./lib

CMAKEOPTS =
ifeq ($(arch), gcc5)
	CMAKEOPTS += -DCMAKE_TOOLCHAIN_FILE=../tools/share/cmake/Toolchain-gcc5.cmake
endif

ifeq ($(debug), 1)
	CMAKEOPTS += -DCMAKE_BUILD_TYPE=Debug
endif

.EXPORT_ALL_VARIABLES:

.PHONY: all distclean

all: $(BUILDDIR)Makefile
	@ $(MAKE) -C $(BUILDDIR)

distclean:
	@- $(RM) -R $(BUILDDIR) $(BINDIR) $(LIBDIR)

$(BUILDDIR)Makefile:
	@ mkdir -p $(dir $@)
	(cd $(dir $@) &> /dev/null && cmake $(CMAKEOPTS) ..)

ifneq ($(MAKECMDGOALS),all)
ifneq ($(MAKECMDGOALS),distclean)
$(MAKECMDGOALS): $(BUILDDIR)Makefile
	@ $(MAKE) -C $(BUILDDIR) $(MAKECMDGOALS)
endif
endif

