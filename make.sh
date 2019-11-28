#!/bin/bash

gcc kernel.c -m32 -o kernel.o -c -ffreestanding -fno-pie 
ld kernel.o -o kernel.bin -m elf_i386 -Ttext 0x7e00 --oformat binary
