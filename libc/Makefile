DEFAULT_HOST!=../configure/default-host.sh
HOST?=$(DEFAULT_HOST)
HOSTARCH!=../configure/target-triplet-to-arch.sh $(HOST)

CFLAGS?= -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk
CPPFLAGS:=$(CPPFLAGS) -D__is_libc -Iinclude

LIBK_SRCS:=\
stdio/putchar.c \
stdio/puts.c \
stdlib/abort.c \
string/memcmp.c \
string/memcpy.c \
string/memmove.c \
string/memset.c \
string/strlen.c \

LIBC_SCS:=$(wildcard */*.c)
$(info LIBK_SRCS=$(LIBK_SRCS))

FREEOBJS:=$(LIBK_SRCS:.c=.o)
HOSTEDOBJS:=$(LIBC_SRCS:.c=.o)

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

$(info FREEOBJS=$(FREEOBJS))
$(info LIBK_OBJS=$(LIBK_OBJS))
LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

#BINARIES=libc.a libk.a # Not ready for libc yet.
BINARIES=libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .asm

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)
libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

#TODO: Add stuff for assembler

.c.o:
	$(CC)  -c $< -o $@  $(CFLAGS) $(CPPFLAGS)

.c.libk.o:
	$(CC)  -c $< -o $@  $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)


clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
