> "If you want to travel around the world and be invited to speak at a lot 
of different places, just write a Unix operating system."      ~ Linus Torvalds

# KSOS

This repository contains the code for the operating system, **KSOS**, developed by the members of [ACM Student Chapter IIT Roorkee](iitr.acm.org).

![You asked for it!](https://i.imgur.com/K23dkge.gif)

## Contents
* [Introduction](#Introduction)
* [Getting started](#Getting-started)
* [Build and Run from Source](#Build-and-Run-from-Source)
    * [Dependencies](#Dependencies)
    * [Setup](#Setup)
    * [Detailed Explanation of Setup](#Detailed-Explanation-of-Setup)
    * [Running on a Real Machine](#Running-on-a-Real-Machine)
* [Changelog](#Changelog)
    * [Unreleased](#Unreleased)
    * [v1.0.0 - 2020-04-24](#v1.0.0---2020-04-24)
* [Contribution Guidelines](#Contribution-Guidelines)
* [Potential Features](#Potential-Features)
* [Resources](#Resources)
* [License](#Licence)

## Introduction
This OS is being built for an **x86 architecture** system using **Legacy BIOS** and was started from scratch in November 2019. It has been developed on a Debian-based Linux distribution. We emulate using **qemu**, a general-purpose CPU emulator. 

We also write our own Bootloader for Legacy BIOS. The bootloader handles the initial 16-bit CPU mode, preparing the switch to 32-bit protected mode. It also parses the filesystem and loads the kernel before passing control to it. The kernel has been implemented mostly in C. 

> Btw, what KSOS means shall remain a secret. :wink:
> 

## Getting started
Getting started with Operating systems development is often not very easy. For me, [Dr. Nick Blundell's book](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf) was a great resource to begin with, especially for bare-metal and bootloader programming. 

[BrokenThorn's series](http://www.brokenthorn.com/Resources/OSDevIndex.html), although old, was really helpful for providing an overall structure to the project.

Feel free to have discussions with the people at #osdev on [Freenode IRC](https://webchat.freenode.net/), as well as the [OsDev forums](https://webchat.freenode.net/) if you have any issue.

To get started with simple baremetal programming you can read my blog [here](https://kssuraaj28.github.io/2020-01-09-Introduction/). You can also read my journey from the start [here](https://kssuraaj28.github.io). 

In the future, ACM IITR would be releasing weekly/bi-weekly blogs highlighting the different aspects of the Operating system, so the best is yet to come! :smirk:

## Build and Run from Source

This section will mainly explain how to build the OS on a Debian-based Linux. 

### Dependencies

Make sure the following are installed before proceeding with the setup of the OS:

- git : `sudo apt install git`
- nasm (assembler): `sudo apt install nasm`
- qemu (cpu emulator): `sudo apt install qemu`
- make (build system): `sudo apt install make`

### Setup

If you are here to just try and test the OS, just carry out these instructions in command line to get started:

1. Clone this repository: 

```bash 
git clone https://github.com/kssuraaj28/OS.git
```

2. Switch to the main directory of repository: 
 
```bash
cd OS
```

3. If you already have a cross compiler installed, please skip this step. Run the script file for the same (once only, takes time!): 
 
```bash
bash script.sh
```

4. Restart the terminal!
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
    2. Ours is a 32-bit Operating System. We do not want to use your system compiler (which probably produces 64 bit binaries) and libraries to build this operating system. Hence, we build a cross compiler (we use the system compiler to make a custom compiler that produces 32-bit binaries. Yes, you read it right, we use a compiler to compile a compiler). If this went over your head, don't worry, a bash script comes along with the repository, and you just need to run the script, the rest is handled by the script.
    3. In order to build our cross compiler using the script, go to the directory where the script is stored and run `bash script.sh`. After this, you will have to restart the terminal.
    4. If you don't believe that you need a cross compiler, read [this](https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler%3F) and think again. Building the cross compiler will take time and around 2 GB of memory! You are building a completely new compiler, after all.
4. 
    1. To build the OS, we need to compile the C code, assemble the assembly code, link them, make a file system on a disk, copy the kernel to the file system, make the file system bootable, and a lot more. Did you catch all that? xD
    2. Thankfully, all of this is done using a Makefile, and we just need to run a single line: `make`.
    3. And voila! It creates a `disk.img` file, which is the operating system! Pretty neat (it's only 1MB so far).
5. 
    1. You can emulate the OS using: `qemu-system-i386 disk.img` or even simpler`make run`.
    2. This results in a new window that runs the OS. Enjoy the bright colors!

### Running on a Real Machine
1. To run it directly on a PC without an emulator, you would need to have a Legacy BIOS system. Let's say you did have one lying around for 12+ years, follow the next instructions!
2. First we would have to copy it to a USB by plugging it into your system where you have built the OS and run:`sudo dd if=disk.img of=/dev/sdx` where `sdx` is `sda/sdb/sdc` depending on the output of `lsblk`. 
3. However, this would not work with UEFI systems (almost all of the systems nowadays). Porting to UEFI is something you could contribute to (see [potential features](#Potential-Features)).
4. Then just plug in your USB into the system and the OS boots up!

## Changelog

### Unreleased

#### Added
 - Mini standard library
 - User mode
 - FAT filesystem driver
 - ATA disk driver

#### Changed
 - Build system

#### Removed

### v1.0.0 - 2020-04-24

#### Added

- Interrupt Handler
- Timer
- Keyboard Driver
- Virtual Memory
- File System
- Video Driver
- Memory Manager
- Basic U/I: A Kernel Level Shell

## Contribution Guidelines

Operating system development is debatably the most onerous task in programming, notably because of the complete absence of any "backend" that you can work upon. You are the complete backend. However, there is no need to be discouraged. If you want to contribute, you can look at some of the more straightforward problems that we have in the [issues](https://github.com/kssuraaj28/OS/issues) section.

To get started, you NEED to know how to build the OS from source. After that, it's just up to your imagination. The thing with operating systems is, you can do whatever you want. Feel free to discuss any ideas that you may have with us by opening an issue. :smiley:

Do not shy away from asking questions about the OS, possible features or operating systems in general on our [Facebook Page](https://www.facebook.com/acmiitr/).

Once you do find an issue or feature to contribute, please:

1. Fork the repository.
2. Create a new feature/bug branch.
3. Follow the following commit guidelines: [1](https://chris.beams.io/posts/git-commit/), [2](https://www.conventionalcommits.org/en/v1.0.0/)
4. Submit a PR!



## Potential Features

A lot of the work from v.1.0.0 stage can now be done mainly in C. Possible developments could include implementing: 

* more general standard input/output functions
* file system (disk) driver
* graphics
* multitasking
* user-mode

Other major work to be done:

* Porting to UEFI / Using an existing Bootloader like GRUB


## Resources
 * [The OSDev wiki](https://wiki.osdev.org/Main_Page)
 * [The OSDev forums](https://forum.osdev.org/)
 * [BrokenThorn](http://www.brokenthorn.com/Resources/OSDevIndex.html)
 * [Dr. Nick Blundell's book](www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
 * Official Intel Software Developers' Manuals
 * StackOverflow (obviously :P)
 * #osdev on Freenode IRC (try it, they're the best!)

## Licence
This repository is licenced under `MIT Licence`, see [LICENCE.md](https://github.com/kssuraaj28/OS/blob/master/LICENSE.md).
