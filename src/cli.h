void kprintf(char *msg)
{
	int i = 0;
	while(msg[i] != 0x00) {i++;}
 	write(STDOUT_FILENO, msg, i);	
}
void cli_init()
{
	kprintf("Hello World");
}

