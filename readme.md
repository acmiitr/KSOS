#ACM DOS
I started building the OS for x86 architecture from scratch since November 2019, and was lucky to have an old laptop operating on Legacy BIOS. The OS is being developed on Linux Mint, using a CPU emulator called qemu. It starts out in 16 bit real mode, and switches to 32 bit protected mode implemented using C. Right now, the features are
- Kernel
- Interrupt handler
- Timer
- Keyboard driver
- Virtual Memory
- File System
- Video driver
- Memory manager

A lot of the work from this stage can now be done mainly in C, and possible developments could include implementing more general standard input/output functions, file system driver, mini games etc

And no, the DOS doesn't mean it's a disk operating system, but what the D does stand for shall remain a secret ;)

#How to run the OS using qemu
This section will mainly explain how to run the OS using Debian Linux

Firstly, clone the repository using
'git clone https://github.com/kssuraaj28/OS.git'

You would need to install qemu using
'sudo apt-get install qemu'

Then, since most systems nowadays work on 64 bit, but this OS is 32 bit, we need to build a cross compiler using gcc for 32 bit binaries. If this went over your head, don't worry, a bash script comes along with the repository and you just need to run the script, the rest is handled by the script. Go to the directory where script is stored and run
'bash script.sh'

To build the OS, we need to compile the C code, assemble the assembly code, link them, make a file system, copy the kernel to the file system and make the file system bootable. Did you catch all that xD? Thankfully, all of this is done using Makefile and we just need to run a single line
'make'

And voila!, it creates a disk.img file that you need to run using the emulator that we just installed
'qemu-system-i386 disk.img'

This results in a new window that runs the OS. Enjoy the bright colours!

To actually run it directly on a PC without an emulator, you would need to have a Legacy BIOS system. Let's say you did have one lying around for 10+ years, first we would have to copy it to a USB
'sudo dd if=disk.img of=/dev/sdx' 
where 'sdx' is 'sda/sdb/sdc' depending on the output of 'lsblk'

Then just plug in your USB into the system and the OS boots up!
