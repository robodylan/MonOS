/*
*  init.c
*/
extern void write_port(unsigned short port, short data);
extern short read_port(unsigned short port);

#include "kb.h"
#include "io.h"
#include "cli.h"
#include "fs.h"
#include "hd.h"
				
//TODO: add timer/sleep function/syscall
 
//Kernel Entry
void main(void)
{
	//write();
	kprintf("INIT: Entering runlevel 3");
	handle_modifier("n");
	kprintf("Setting up USB devices");
	//kb_init();
	//dpt_init();
	//cli_init();			
}
