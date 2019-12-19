#This is the phoney instruction that will help us make daddy-os
all: run

kernel.o : Kernel/kernel.c
	gcc -ffreestanding -c -fno-pie -m32 $^ -o $@

entry.o : Kernel/entry.asm
	nasm $^ -o $@ -f elf

kernel.bin : entry.o kernel.o 
	ld $^ -o $@ -m elf_i386 -Ttext 0x1000 --oformat binary
	chmod -x $@	

boot.bin : Boot/bootloader.asm
	nasm $^ -f bin -o $@
stage2.bin: Boot/stage2/stage2.asm
	nasm $^ -f bin -o $@

daddy-os : boot.bin kernel.bin
	cat $^ > $@
	truncate $@ -s 4K

run : daddy-os
	qemu-system-x86_64 -hda  $^

clean :
	rm *.bin *.o

emul:
	alias emul="qemu-system-x86_64"

bootsector: boot.bin stage2.bin
	dd if=boot.bin of=test bs=1 count=3 seek=0 skip=0 conv=notrunc
	dd if=boot.bin of=test bs=1 count=451 seek=62 skip=62 conv=notrunc
	dd if=stage2.bin of=test bs=512 count=2 seek=1 skip=0 conv=notrunc

