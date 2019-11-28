#!/bin/bash
./make.sh 
nasm Bootloader.asm -f bin -o Os.bin
cat kernel.bin >> Os.bin 
truncate Os.bin -s 10K
qemu-system-x86_64 Os.bin 

