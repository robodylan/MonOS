unsigned int current_dir_sector = 2129;//Begin at root directory location
int fs_init()
{
	kprintf("Debug: Checking to see if BOOT Directory exists\n");
	if(fs_dir_exists("TEST    TXT"))
	{
		kprintf("BOOT EXISTS!!!\n");	
	}
	fs_ls_dir();		
}

int fs_open_dir(char *name)
{
	char *dirData;//Init buffer for data
	hd_rw(current_dir_sector, HD_READ, 512, dirData);//Read data into buffer
	int i = 0;//Init counter
	while(i < 512)//Loop through entries in sector
	{
		if(compName(dirData, name))//See if file exists TODO: Check atrib byte to see if it is a directory
		{
			current_dir_sector = dirData[26];//TODO: This is temporary and it needs to be fixed 
		}
		i += 64;
		dirData += 64;
	}	
}

int fs_close_dir()
{
	
}

int fs_ls_dir(void)//List contents of current directory, mainly for debug purposes
{
	kprintf("\nCurrent Directory ->\n");
	char *dirData;//Init data for data
	hd_rw(current_dir_sector, HD_READ, 512, dirData);//Read data into buffer
	int i = 0;//Init counter
	while (i < 512)//Loop through entries in sector
	{
		write(STDOUT_FILENO, dirData, 32);//Write content of entry
		kprintf("\n");//New line
		i += 64;//Increment counter to next directory entry
		dirData += 64;//Increment pointer to next directory entry
	}
	kprintf("\n");
}

int fs_file_exists(char *filename)//Check if a file exists
{
	char fileExists = 0;//Init exists variable
	char *fileData;//Init buffer for data
	hd_rw(current_dir_sector, HD_READ, 512, fileData);//Read data into buffer
	int i = 0;//Init counter
	while(i < 512)//Loop through entries in sector
	{
		if(compName(fileData, filename))//See if file exists TODO: Check atrib byte to see if it is a file
		{
			fileExists = 1;//Set exists variable to true
		}
		i += 64;//Increment counter to next directory entry
		fileData += 64;//Increment pointer to next directory entry
	}
	return fileExists;
}

int fs_dir_exists(char *dirname)//Check if a directory exists
{
	char dirExists = 0;//Init exists variable
	char *dirData;//Init buffer for data
	hd_rw(current_dir_sector, HD_READ, 512, dirData);//Read data into buffer
	int i = 0;//Init counter
	while(i < 512)//Loop through entries in sector
	{
		if(compName(dirData, dirname))//See if directory exists TODO: Check atrib byte to see if it is a directory
		{
			dirExists = 1;//Set exists variable to true
		}
		i += 64;//Increment counter to next directory
		dirData += 64;//Increment pointer to next directory entry
	}
	return dirExists;
}

//Credit to Keith S. for following function
int isBitSet(int value, int bitNumber)//Check to see if a specific bit is set
{
	int bit = (value & (1 << bitNumber-1)) != 0;
	return bit;
}

int compName(char *a, char *b)//Check if name matches a string TODO: Rename this function
{
	char isSame = 1;//Init boolean variable
	int i = 0;//Init counter variable
	while(i < 11)//Loop through 11 byte filename
	{
		if(a[i] < 63) a[i] = ' ';//If null set to space
		if(b[i] < 63) b[i] = ' ';//If null set to space
		if(a[i] != b[i])
		{ 
			isSame = 0;
		}
		i++;
	}
	return isSame;
}
