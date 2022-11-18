#!/bin/bash

if [ ! -f sd.bin ]
then
    dd if=/dev/zero of=sd.bin bs=1024 count=65536
fi

if [ ! -d mnt_tmp ]
then
    mkdir mnt_tmp
fi

mount sd.bin mnt_tmp
rm -rf mnt_tmp/*
cp -r root/* mnt_tmp

umount mnt_tmp

if [ ! -z $1 ]
then
    cp sd.bin ../rt-thread-src/bsp/$1/sd.bin
fi