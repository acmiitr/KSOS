# HOST is i686-elf for us. It is the target triplet for the machine that is going to running the executables
# TODO: Perhaps replace all the kernel.elf with myos.kernel -- That's more beautiful. Also we might want to have an elf loader in the bootloader.
DEFAULT_HOST!=../configure/default-host.sh
HOST?=$(DEFAULT_HOST)
HOSTARCH!=../configure/target-triplet-to-arch.sh $(HOST)

CFLAGS?=-g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude/kernel
LDFLAGS:=$(LDFLAGS) -Tlinker.ld
LIBS:=$(LIBS) -nostdlib  -lgcc -lk


C_SOURCES := $(wildcard */*.c)  #TODO: Expand all this
ASM_SOURCES:= $(wildcard */*.asm)
C_OBJS:= ${C_SOURCES:.c=.o}
ASM_OBJS:= ${ASM_SOURCES:.asm=.o}

KERNEL_OBJS:= \
$(C_OBJS)\
$(ASM_OBJS)\


#OBJS=\
#$(wildcard startup/*.o)\
#$(KERNEL_OBJS) \

LINK_LIST:=\
$(LDFLAGS) \
$(KERNEL_OBJS) \
$(LIBS) \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .asm   

all: kernel.elf

kernel.elf: $(KERNEL_OBJS) linker.ld
	$(CC) -o $@ $(CFLAGS) $(LINK_LIST)
	chmod -x $@

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)  #Our C compiler should hopefully be i686-elf-gcc --sysroot=?? -isystem=??

.asm.o:
	nasm -felf32 $< -o $@ 


install: install-headers install-kernel

install-headers:  
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: kernel.elf
	objcopy -O binary $^ kernel.bin
	chmod -x kernel.bin
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp kernel.bin $(DESTDIR)$(BOOTDIR)
clean:
	rm -f kernel.elf kernel.bin
	rm -f $(KERNEL_OBJS) *.o */*.o */*/*.o
