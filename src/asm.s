bits 32

section .text
	align 4 ;4 bit aligned
	dd 0x1BADB002 ;Header
	dd 0x00 ;Set flags to zero
	dd - (0x1BADB002 + 0x00) ;Checksum

global read_port ;Define read_port function as global
global write_port ;Define write_port function as global
global read_key	;Define read_key function as global
global start ;Define start function as global
global int_h ; Define int_h function as global

extern k_main ;Define external function k_mainh
extern sys_read  ;Define external function _read
extern sys_write ;Define external function _write

read_port:
	mov edx, [esp + 4]
			;al is the lower 8 bits of eax
	in ax, dx	;dx is the lower 16 bits of edx
	ret ;Return to where function was called

write_port:
	mov   edx, [esp + 4]    ;Pass in first argument
	mov   al, [esp + 4 + 4] ;Pass in second argument  
	out   dx, ax ;Output to port
	ret ;Read from port

read_key:
	mov ah, 0x10 ;Tell CPU we want to read 
	int 0x16 ;Call input interrupt
	mov al, ah ;Write to port
	ret ;Return to where function was called

start: ;Init routine
	cli ;Clear interrupts
	call k_main ;call C main function
	hlt ;Halt CPU
int_h:
	cmp ah, 1;Check for write call
 	jne .write
	call sys_read
	jmp .done
.write
	cmp ah, 2
	jne .badcode
	call sys_write
	jmp .done
.badcode
	mov eax, 0xFFFFFFFF
.done 
	iretd
 
