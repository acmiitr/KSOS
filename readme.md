# ACM DOS

## Introduction
This OS is being built for **x86 architecture** system using **Legacy BIOS** and started from scratch since November 2019. The OS is being developed on Linux Mint, using a CPU emulator called qemu. As we write our own bootloader, we start out in 16 bit real mode. The bootloader handles the switch to 32 bit protected mode, parses the filesystem and loads the kernel before passing control to the it. The kernel has been implemented mostly using C . 

## Features
Right now, the features are

- Interrupt handler
- Timer
- Keyboard driver
- Virtual Memory
- File System
- Video driver
- Memory manager

A lot of the work from this stage can now be done mainly in C, and possible developments could include implementing more general standard input/output functions, file system (disk) driver, mini games etc

And no, the DOS does **NOT** mean it's a disk operating system, but what it does mean shall remain a secret ;)

## How to build and run the OS from source
This section will mainly explain how to build the OS on Debian-based Linux. 

### Prerequisutes
- git : `sudo apt install git`
- nasm (assembler): `sudo apt install nasm`
- qemu (cpu emulator): `sudo apt install qemu`
- make (build system): `sudo apt install make`

Firstly, clone the repository using

`git clone https://github.com/kssuraaj28/OS.git`

Then, since most systems nowadays work on 64 bit, but ACM-DOS is a 32 bit Operating System. We also do not want to use your system compiler and libraries to build this operating system. Hence, we build a cross compiler (we use the system compiler to make a custom compiler that produces 32 bit binaries. Yes, you read it right, we use a compiler to compile a compiler). If this went over your head, don't worry, a bash script comes along with the repository and you just need to run the script, the rest is handled by the script. Go to the directory where script is stored and run

`bash script.sh`

If you don't believe that you need a cross complier, read this: https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler%3F and think again. Building the cross compiler will take time! You are building a completely new compiler after all! It will also take around 2 GB of disk space.


To build the OS, we need to compile the C code, assemble the assembly code, link them, make a file system on a disk, copy the kernel to the file system, make the file system bootable, and a lot more. Did you catch all that xD? Thankfully, all of this is done using a Makefile and we just need to run a single line

`make`

And voila!, it creates a disk.img file that you need to run using the emulator that we just installed

`qemu-system-i386 disk.img`

Or even simpler

`make run`

This results in a new window that runs the OS. Enjoy the bright colours!

To actually run it directly on a PC without an emulator, you would need to have a Legacy BIOS system. Let's say you did have one lying around for 12+ years, first we would have to copy it to a USB by plugging it into your system where you have built the OS and run

`sudo dd if=disk.img of=/dev/sdx` 

where `sdx` is `sda/sdb/sdc` depending on the output of `lsblk`

Then just plug in your USB into the system and the OS boots up!

### Resources
 * The OsDev wiki and forums : https://wiki.osdev.org/Main_Page , https://forum.osdev.org/
 * BrokenThorn : http://www.brokenthorn.com/Resources/OSDevIndex.html
 * Dr. Nick Blundell's book: https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
 * StackOverflow (Obviously)
 * #osdev on Freenode IRC (Try it! They're the best!)
