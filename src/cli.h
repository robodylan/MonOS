void kprintf(char *msg)
{
    //int slash = 0;
	int i = 0;
	while(msg[i] != 0x00)
	{
	    /*if(slash)
		{
			handle_modifier(msg[i]);
		}
		if(msg[i] == 0x2F)
		{ 
			slash = 1;
		}
		else
		{
			slash = 0;
		}*/
		i++; //TODO: handle modifiers or put them somewhere else
	}
 	write(STDOUT_FILENO, msg, i);		
}
void cli_init()
{
	kprintf("Hello World");
}
void handle_modifier(char *modifier)
{
		if(modifier == "n")
		{
	    	//Newline
			char curcol = curpos%160; //Find out which column we are in	
			curpos = curpos +  (160 - curcol); 
		}
		if(modifier == "t")
		{
			//Tab
			curpos = curpos + 8;
		}
}
