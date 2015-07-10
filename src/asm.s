bits 32

section .text
	align 4 ;4 bit aligned
	dd 0x1BADB002 ;Header
	dd 0x00 ;Set flags to zero
	dd - (0x1BADB002 + 0x00) ;Checksum

global read_port
global write_port
global read_key	
global start

extern main ;Define external function main

read_port:
	mov edx, [esp + 4]
			;al is the lower 8 bits of eax
	in ax, dx	;dx is the lower 16 bits of edx
	ret

write_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, ax 
	ret

read_key:
	mov ah, 0x10
	int 0x16
	mov al, ah
	ret

start: ;Init routine
	cli ;Clear interrupts
	call main ;call C main function
	hlt ;Halt CPU
