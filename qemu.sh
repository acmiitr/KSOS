#!/bin/bash
set -e
export HOST=${HOST:-"$(configure/default-host.sh)"}
qemu-system-$(configure/target-triplet-to-arch.sh $HOST) -drive format=raw,file=disk.img  -monitor stdio
