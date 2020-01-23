#This is the phoney instruction that will help us make daddy-os
all: run

run : assemble
#	qemu-system-i386 -hda disk.img
	qemu-system-i386 -drive format=raw,file=disk.img  -monitor stdio


assemble: kernel.bin stage1.bin stage2.bin disk.img
	dd if=stage1.bin of=disk.img bs=1 count=3 seek=0 skip=0 conv=notrunc
	dd if=stage1.bin of=disk.img bs=1 count=451 seek=62 skip=62 conv=notrunc
	sudo mount disk.img /mnt
	sudo cp stage2.bin kernel.bin /mnt
	sudo umount /mnt


kernel.bin : kernel/entry.o kernel/kernel.elf  #perhaps I should name kernel.o as kernel.elf?
	ld -m elf_i386 $^ -Ttext 0x100000 -e start --oformat binary -o $@
	chmod -x $@

kernel/kernel.o : kernel/kernel.c 
	gcc -m32 -ffreestanding -fno-pie $^ -c -o $@ -Wall -Werror

kernel/kernel.elf : kernel/kernel.o kernel/asm/cursor.o
	ld -m elf_i386 $^ -r -e kmain -o $@

kernel/asm/%.o:kernel/asm/%.asm
	nasm $< -o $@ -f elf32

kernel/entry.o : kernel/entry.asm
	nasm $^ -o $@ -f elf32

stage1.bin : boot/stage1/stage1.asm
	nasm $^ -f bin -o $@
stage2.bin: boot/stage2/stage2.asm
	nasm $^ -f bin -o $@

disk.img: 
	truncate $@ -s 1M
	mkfs.vfat -F12 -S512 -s1 $@
clean :
	rm *.bin *.o
