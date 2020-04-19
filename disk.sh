#!/bin/bash
set -e

export PREFIX=${PREFIX:-"/usr"}
export EXEC_PREFIX=${EXEC_PREFIX:-"$PREFIX"}
export BOOTDIR=${BOOTDIR:-"/boot"}
export LIBDIR=${LIBDIR:-"$EXEC_PREFIX/lib"}
export INCLUDEDIR=${INCLUDEDIR:-"$PREFIX/include"}

export SYSROOT=${SYSROOT:-"$(pwd)/sysroot"}

truncate disk.img -s 1M
mkfs.vfat -F12 -S512 -s1 disk.img
dd if=$SYSROOT$BOOTDIR/stage1.bin of=disk.img bs=1 count=3 seek=0 skip=0 conv=notrunc
dd if=$SYSROOT$BOOTDIR/stage1.bin of=disk.img bs=1 count=451 seek=62 skip=62 conv=notrunc
mcopy -i disk.img $SYSROOT$BOOTDIR/stage2.bin $SYSROOT$BOOTDIR/kernel.bin ::  -D o
