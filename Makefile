C_SOURCES = $(wildcard kernel/src/c/*.c)
ASM_SOURCES = $(wildcard kernel/src/asm/*.asm)
C_OBJECTS = ${C_SOURCES:.c=.o}
ASM_OBJECTS = ${ASM_SOURCES:.asm=.o}


.PHONY : all assemble run

all: assemble

run : 
#	qemu-system-i386 -hda disk.img
	qemu-system-i386 -drive format=raw,file=disk.img  -monitor stdio


assemble: disk.img kernel.bin stage1.bin stage2.bin 
	dd if=stage1.bin of=disk.img bs=1 count=3 seek=0 skip=0 conv=notrunc
	dd if=stage1.bin of=disk.img bs=1 count=451 seek=62 skip=62 conv=notrunc
	mcopy -i disk.img stage2.bin kernel.bin ::  -D o
#	sudo mount disk.img /mnt
#	sudo cp stage2.bin kernel.bin /mnt
#	sudo umount /mnt


kernel.bin : kernel/kernel.elf  #perhaps I should name kernel.o as kernel.elf?
	objcopy -O binary $^ $@
	chmod -x $@


kernel/kernel.elf : kernel/entry.o $(C_OBJECTS) $(ASM_OBJECTS)
	i686-elf-ld  $^ -Ttext 0x100000 -e kmain -o $@

%.o : %.c
	i686-elf-gcc -ffreestanding $< -c -o $@ -Wall -Werror
%.o : %.asm
	nasm $< -o $@ -f elf32

stage1.bin : boot/stage1/stage1.asm
	nasm $^ -f bin -o $@
stage2.bin: boot/stage2/stage2.asm
	nasm $^ -f bin -o $@

disk.img: 
	truncate $@ -s 1M
	mkfs.vfat -F12 -S512 -s1 $@
clean :
	rm $(C_OBJECTS) $(ASM_OBJECTS)
