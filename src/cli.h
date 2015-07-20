int handle_modifier(char modifier)
{
		int isMod = 0;
		if(modifier == '\n')//Modifier is Newline
		{
	    	//Newline
			char curcol = curpos%160; //Find out which column we are in	
			curpos = curpos +  (160 - curcol);//Find difference to edge of screen and add it
			isMod = 1;
		}
		if(modifier == '\t')//Modifier is Tab
		{
			//Tab
			curpos = curpos + 8;//Move cursor position 4 characters 
			isMod = 1;
		}
		if(modifier == '\f')
		{
			curpos = curpos + ((80*2*25)-curpos);//Clear Screen
		}
		return isMod;
}

void kprintf(char *msg)
{
	int i = 0;//Declare counter
	while(msg[i] != 0)//Loop until string termination
	{
		char *c;//Define tmp character
		if(handle_modifier(msg[i]))//Check if character is modifier and handle it
		{
			i++;	
		}
		else
		{
			c[0] = msg[i];//Set position 0 of pointer c to current character
	    		write(STDOUT_FILENO, c, 1);//Write out value of first position of c
			i++;//Increment counter
		}
	}		
}

void cli_init() 
{
	kprintf("Entering Command Line Interface...\n");
}
