#!/bin/bash
cd /home/robodylan/Desktop/LearnOS/
cd src
gcc -m32 -c kernel.c -o ../obj/kc.o
nasm -f elf32 kernel.asm -o ../obj/kasm.o
cd ../obj
ld -m elf_i386 -T link.ld -o ../iso/boot/Kernel.BIN kasm.o kc.o
cd ..
grub2-mkrescue -o out/bootable.iso iso
qemu-system-i386 -hda  out/bootable.iso
