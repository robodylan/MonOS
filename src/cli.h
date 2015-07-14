void kprintf(char *msg)
{
	int i = 0;
	while(msg[i] != 0)
	{
		if(msg[i] == 47 && msg[i + 1] != 47)
		{
			i++;
			char mod = (char)msg[i];
			handle_modifier(mod);	
		}
		else
		{
			char *c;
			c[0] = msg[i]; 
	    	write(STDOUT_FILENO, c, 1);
			i++;
		}
	}		
}
void cli_init()
{
	kprintf("Hello World");
}
void handle_modifier(char modifier)
{
		if(modifier == 'n')
		{
	    	//Newline
			char curcol = curpos%160; //Find out which column we are in	
			curpos = curpos +  (160 - curcol); 
		}
		if(modifier == 't')
		{
			//Tab
			curpos = curpos + 8;
		}
}
