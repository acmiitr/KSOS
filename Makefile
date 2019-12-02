#This is the phoney instruction that will help us make daddy-os
all: run

kernel.o : Kernel/kernel.c
	gcc -ffreestanding -c -fno-pie -m32 $^ -o $@

kernel.bin : kernel.o #This needs to be updated
	ld $^ -o $@ -m elf_i386 -Ttext 0x7e00 --oformat binary
	chmod -x $@	

boot.bin : Boot/Bootloader.asm
	nasm $^ -f bin -o $@

daddy-os : boot.bin kernel.bin
	cat $^ > $@
	truncate $@ -s 4K

run : daddy-os
	qemu-system-x86_64 $^

clean :
	rm *.bin *.o
