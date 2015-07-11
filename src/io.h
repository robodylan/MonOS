/*
*  io.h
*/

const char STDOUT_FILENO = 1;//File descriptor for std out
const char STDIN_FILENO = 0;//File descriptor for std ini
char *MEM_FILELOC = (char *)0x100000;//Location of file in memory;
char *vidptr = (char*)0xB8000;

int curpos = 0; //Location of cursor
void write(int fd,const char *buf,int nbytes) //Write nbytes of *buf to fd
{
	if(fd == STDOUT_FILENO)//print to video memory
	{
		int i = 0;//Declare counter 
		while(i < nbytes)//Write number of bytes specified
		{
			if(curpos > (80 * 25 * 2))//Check to see if we need to wrap around
			{
				curpos = 0;//Reset cursor
			}
			vidptr[curpos] = buf[i];//Set location in video memory to buffer
			vidptr[curpos + 1] = 0x07;//Set style to white over black
			curpos = curpos + 2;//Increment cursor by two;
			i++;//Increment counter 	
		}
	}
	else//!stdio so we write to file in memory
	{
		int i = 0;//Declare counter
		while(i < nbytes)//Write number of bytes specified
		{
			MEM_FILELOC[i] = buf[i];//Copy current buffer bytes to file 
			i++;//Increment memory location
		}
	}	

}
//Read 
void read(int fd,char *buf,int nbytes)
{
	if(fd == STDIN_FILENO)//Are we reading from standard input
	{
		int i = 0;//Declare counter
		while(i < nbytes)//Read number of bytes specified
		{
			write_port(0x21, 0xFD); //Request keyboard
			char status = read_port(0x64); //Get status of keyboard
			if(status & 0x01)//Make sure kb is ready to be read
			{
				char keycode = read_port(0x60); //Get keycode	
				buf[i] = keyboard_map[keycode]; //Map keycode to ASCII and put it into buffer
				i++;//Increment memory location
			}
		}					
	}
	else//!stdio so we read from file in memory
	{
		int i = 0;//Declare counter
		while(i < nbytes)//Read number of bytes specified
		{
			buf[i] = MEM_FILELOC[i]; //Copy current file byte to buffer
			i++;//Increment memory location
		}	
	}
}	
//Open system call
void open(const char *filename, int flags)
{
//TODO: Read disk and put file in MEM_FILELOC memory location 	
}
//Close system call
void close(const char fd)
{
//TODO: Clear MEM_FILELOC
}
