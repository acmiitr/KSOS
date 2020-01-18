#This is the phoney instruction that will help us make daddy-os
all: run

kernel.o : Kernel/kernel.c
	gcc -ffreestanding -c -fno-pie -m32 $^ -o $@

entry.o : Kernel/entry.asm
	nasm $^ -o $@ -f elf

#kernel.bin : entry.o kernel.o 
#	ld $^ -o $@ -m elf_i386 -Ttext 0x1000 --oformat binary
#	chmod -x $@	

#daddy-os : boot.bin kernel.bin
#	cat $^ > $@
#	truncate $@ -s 4K

stage1.bin : Boot/stage1/stage1.asm
	nasm $^ -f bin -o $@
stage2.bin: Boot/stage2/stage2.asm
	nasm $^ -f bin -o $@

kernel.bin : Kernel/entry.asm
	nasm $^ -f bin -o $@


run : kernel stage2 stage1 
#	qemu-system-i386 -hda disk.img
	qemu-system-i386 -drive format=raw,file=disk.img  -monitor stdio

clean :
	rm *.bin *.o

disk.img: 
	truncate $@ -s 1M
	mkfs.vfat -F12 -S512 -s1 $@
stage1: disk.img stage1.bin
	dd if=stage1.bin of=disk.img bs=1 count=3 seek=0 skip=0 conv=notrunc
	dd if=stage1.bin of=disk.img bs=1 count=451 seek=62 skip=62 conv=notrunc

stage2: stage2.bin disk.img
	sudo mount disk.img /mnt
	sudo cp stage2.bin /mnt
	sudo umount /mnt

kernel: kernel.bin disk.img
	sudo mount disk.img /mnt
	sudo cp kernel.bin /mnt
	sudo umount /mnt
