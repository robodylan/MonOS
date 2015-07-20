#!/bin/bash
cd src
gcc -m32 -c init.c -o ../obj/kc.o
nasm -f elf32 asm.s -o ../obj/kasm.o
cd ../obj
ld -m elf_i386 -T link.ld -o ../iso/boot/Kernel.BIN kasm.o kc.o
cd ..
dd if=/dev/zero of=out/bootable.img count=20 bs=1048576
sudo parted --script out/bootable.img mklabel msdos mkpart p ext2 1 20 set 1 boot on
sudo kpartx -a out/bootable.img
sleep 1
sudo mkfs.msdos -n MONOS  -F 16 /dev/mapper/loop0p1
sudo mkdir -p build/tmp/p1
sudo mount /dev/mapper/loop0p1 build/tmp/p1
sudo cp -r iso/*  build/tmp/p1
sudo grub-install --boot-directory=build/tmp/p1/boot --target=i386-pc --no-floppy --modules="biosdisk part_msdos fat ext2 configfile normal multiboot" --root-directory=build/tmp/p1 /dev/loop0 
sudo umount build/tmp/p1
sudo kpartx -d out/bootable.img
qemu-system-i386 -hda out/bootable.img
