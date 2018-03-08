/*
*    init.c
*/

//Include kernel modules
#include "include/hd.h"
#include "include/io.h"
#include "include/fs.h"
#include "include/cli.h"
#include "sys.h"
#include "include/kb.h"
#include "include/drivers.h"

//TODO: add timer/sleep function/syscall
//CURRENT: syscall
//Kernel Entry
void k_main(void)
{
	kprintf("INIT: Entering runlevel 3\n");
	kb_init();//Init Keyboard
	fs_init();//Init filesystem
	cli_init();//Init command line
	fs_open_dir("TEST       ");
	fs_ls_dir();
	fs_cat_file("123     TXT");//Show contents of test file
	fs_ls_dir();
	while(1==1);//Prevent overflow
}
