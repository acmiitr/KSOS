> "If you want to travel around the world and be invited to speak at a lot 
of different places, just write a Unix operating system."      ~ Linus Torvalds, creator of Linux

# KSOS

This repository contains the code for the operating system, **KSOS**, developed by the members of [ IIT Roorkee ACM Student Chapter](http://iitr.acm.org). To know more about the development journey from the beginning, read our [blog](https://kssuraaj28.github.io) written by Suraaj! 

In the future, we will be releasing blogs highlighting the different aspects of KSOS, so the best is yet to come. Stay tuned!

![You asked for it!](https://i.imgur.com/K23dkge.gif)

## Contents
* [Introduction](#Introduction)
* [Build and Run from Source](#Build-and-Run-from-Source)
    * [Dependencies](#Dependencies)
    * [Setup](#Setup)
    * [Detailed Explanation of Setup](#Detailed-Explanation-of-Setup)
    * [Running on a Real Machine](#Running-on-a-Real-Machine)
* [Changelog](#Changelog)
    * [Unreleased](#Unreleased)
    * [v1.0.0 - 2020-04-30](#v1.0.0---2020-04-30)
* [Getting Started](#Getting-Started)
* [Contribution Guidelines](#Contribution-Guidelines)
* [Potential Features](#Potential-Features)
* [Resources](#Resources)
* [License](#Licence)

## Introduction
This OS is being built for an **x86 architecture** system using **Legacy BIOS** and was started from scratch in November 2019. It has been developed on a Debian-based Linux distribution. We emulate using **qemu**, a general-purpose CPU emulator. 

We also write our very own Bootloader for Legacy BIOS. The bootloader handles the initial 16-bit CPU mode, preparing the switch to 32-bit protected mode. It also parses the filesystem and loads the kernel before passing control to it. The kernel has been implemented mostly in C. 

> Btw, what KSOS means shall remain a secret. :wink:


## Build and Run from Source

This section will mainly explain how to build KSOS on a Debian-based Linux. 

### Dependencies

Make sure the following are installed before proceeding further:

- git : `sudo apt install git`
- nasm (assembler): `sudo apt install nasm`
- qemu (cpu emulator): `sudo apt install qemu`
- make (build system): `sudo apt install make`

### Setup

If you are here to just try and test the OS, carry out these commands in Bash to get started:

1. Clone this repository: 

```bash 
git clone https://github.com/kssuraaj28/OS.git
```

2. Switch to the main directory of the repository: 
 
```bash
cd OS
```

3. If you already have a cross compiler installed, please skip this step. Run the script file for the same (only once, it takes time and around 2 gigs of memory!): 
 
```bash
bash script.sh
```

4. Restart the terminal.
5. Do a fresh make of the OS:
```bash
make
```

### Detailed Explanation of Setup

A detailed explanation of each of the above-mentioned instructions are given below:

1. Firstly, clone the repository.
2. Switch to the main directory of the repository.
3. 
    1. If you already have a cross compiler installed, please skip this step!
    2. Ours is a 32-bit Operating System. We do not want to use your system compiler (which probably produces 64-bit binaries) and libraries to build this operating system. Hence, we build a cross compiler (we use the system compiler to make a custom compiler that produces 32-bit binaries. Yes, you read it right, we use a compiler to compile a compiler). If this went over your head, don't worry, a bash script comes along with the repository, and you just need to run the script. The script handles the rest!
    3. To build our cross compiler using the script, go to the directory where the script is stored and run `bash script.sh`. After this, you will have to restart the terminal.
    4. If you don't believe that you need a cross compiler, read [this](https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler%3F) and think again. Building the cross compiler will take time and around 2 GB of memory! After all, you are building an entirely new compiler.
4. 
    1. To build the OS, we need to compile the C code, assemble the assembly code, link them, make a file system on a disk, copy the kernel to the file system, make the file system bootable, and a lot more. Did you catch all that? xD
    2. Thankfully, all of this is done using a Makefile, which we can run using a single line: `make`.
    3. And voila! It creates a `disk.img` file, which is the operating system. Pretty neat (it's only 1MB so far)!
5. 
    1. You can emulate KSOS using: `qemu-system-i386 disk.img` or even simpler`make run`.
    2. This results in a new window that runs KSOS. Enjoy the bright colors!

### Running on a Real Machine
1. To run it directly on a PC without an emulator, you would need to have a Legacy BIOS system. Let's say you did have one lying around for 12+ years, follow the next instructions!
2. First, we would have to copy it to a USB by plugging it into your system where you have built the OS and run:`sudo dd if=disk.img of=/dev/sdx` where `sdx` is `sda/sdb/sdc` depending on the output of `lsblk`. 
3. However, this would not work with UEFI systems (almost all of the systems nowadays). Porting to UEFI is something you could contribute to (see [potential features](#Potential-Features)).
4. Then plug in your USB into the system, turn it on, and the OS boots up!

## Changelog

### Unreleased

#### Added
 - Mini Standard Library
 - User Mode
 - FAT Filesystem Driver
 - ATA Disk Driver

#### Changed
 - Build System

#### Removed

### v1.0.0 - 2020-04-30

#### Added

- Interrupt Handler
- Timer
- Keyboard Driver
- Virtual Memory
- File System
- Video Driver
- Memory Manager
- Basic U/I: A Kernel Level Shell

## Getting Started
Getting started with operating systems development is a bit tricky. [Dr. Nick Blundell's book](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf) is a great resource to begin with, especially for bare-metal and bootloader programming. 

[BrokenThorn's OS Development series](http://www.brokenthorn.com/Resources/OSDevIndex.html), although old, is really helpful. Most of the overall structure of the project was built from this resource.

Feel free to have discussions with the people at #osdev on [freenode IRC](https://webchat.freenode.net/), as well as the [OsDev forums](https://forum.osdev.org/), if you have any issue.

To get started with simple bare-metal programming, you can read [Suraaj's blog](https://kssuraaj28.github.io/2020-01-09-Introduction/). 

## Contribution Guidelines

Operating system development is debatably the most onerous task in programming, notably because of the complete absence of any "backend" that you can work upon. You are the complete backend. However, there is no need to be discouraged. If you want to contribute, you can look at some of the more straightforward problems that we have in the [issues](https://github.com/acmiitr/KSOS/issues) section.

To get started, you NEED to know how to build the OS from source. After that, it's just up to your imagination. The thing with operating systems is, you can do whatever you want. Feel free to discuss any ideas that you may have with us by opening an issue. :smiley:

Do not shy away from asking questions about KSOS, possible features to implement or operating systems in general on our [Facebook Page](https://www.facebook.com/acmiitr/).

Once you do find an issue or feature to contribute, please:

1. Fork the repository.
2. Create a new feature/bug branch.
3. Follow the following commit guidelines: [1](https://chris.beams.io/posts/git-commit/), [2](https://www.conventionalcommits.org/en/v1.0.0/).
4. Submit a PR!



## Potential Features

A lot of the work after v.1.0.0 release can now be done in C. Possible developments could include implementing: 

* more general standard input/output functions
* file system (disk) driver
* graphics
* multitasking
* user-mode

Other major work to be done:

* Porting to UEFI OR using an existing Bootloader like GRUB


## Resources

 * [Dr. Nick Blundell's book](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
 * [BrokenThorn's OS Development series](http://www.brokenthorn.com/Resources/OSDevIndex.html)
 * [The OSDev wiki](https://wiki.osdev.org/Main_Page)
 * [The OSDev forums](https://forum.osdev.org/)
 * [Official Intel Software Developer's Manual](https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf)
 * [StackOverflow](https://stackoverflow.com/) (obviously :P)
 * #osdev on [freenode IRC](https://webchat.freenode.net/) (try it, they're the best!)

## Licence
This repository is licenced under `MIT Licence`, see [LICENCE.md](https://github.com/kssuraaj28/OS/blob/master/LICENSE.md).
