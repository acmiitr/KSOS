#!/bin/bash
set -e
export PROJECTS=${PROJECTS:-"boot libc kernel"}
export MAKE=${MAKE:-make}

for PROJECT in $PROJECTS; do
  (cd $PROJECT && $MAKE clean)
done

rm -rf sysroot
rm -rf disk.img
