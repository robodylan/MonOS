/*
* fs.h
*/
unsigned int current_dir_sector;//Begin at root directory location
int fs_init()
{
	current_dir_sector = 2201;//Location of root directory TODO: Actually find this from the BPB
	if(fs_dir_exists("BOOT       "))//Check to see if a known directory exists
	{
		kprintf("INIT: Filesystem found and DPT looks ok\n");//We found it so the filesystem should be ok
	}
	else
	{
		kprintf("INIT: Filesystem is corrupt, not FAT16, or misconfigured\n");//We didn't find it so the filesystem might be corrupt
	}
}

int fs_cat_file(char *name)//Print contents of file, mainly for debug purposes
{
	char *fileData;//Init buffer for data
	hd_rw(current_dir_sector, HD_READ, 512, fileData);//Read data into buffer
	int i = 0;//Init counter
	while(i < 512)//Loop through entries in sector
	{
		if(compName(fileData, name))//See if file exists TODO: Check atrib byte to see if it is a directory
		{
			int first_file_sector = current_dir_sector+(((512 * 32) + ((((fileData[26])-2) * 2) * 512)) / 512);//Find first address of file
			return 0;//Return no errors
			hd_rw(first_file_sector, HD_READ, 512, fileData);//Read file data at start cluster
			kprintf("/n Contents of ");//Tell user what file the data is from
			kprintf(name);//Append file name
			write(STDOUT_FILENO, fileData, 512);//Write out file's contents	
		}
		i += 32;//Increment counter to next file entry
		fileData += 32;//Increment pointer to next file entry
	}
	return 1;//Return error
}

int fs_open_dir(char *name)//Set location of current sector to given directory
{
	char *dirData;//Init buffer for data
	hd_rw(current_dir_sector, HD_READ, 512, dirData);//Read data into buffer
	int i = 0;//Init counter
	while(i < 512)//Loop through entries in sector
	{
		if(compName(dirData, name))//See if file exists TODO: Check atrib byte to see if it is a directory
		{	
			current_dir_sector += ((512 * 32) + ((((dirData[26])-2) * 2) * 512)) / 512;//Find first address of directory
			return 0;//Return no errors
		}
		i += 32;//Increment counter to next directory entry
		dirData += 32;//Increment pointer to next directory entry	
	}	
	return 1;//Return error
}

int fs_ls_dir(void)//List contents of current directory, mainly for debug purposes
{
	kprintf("\nCurrent Directory ->\n");
	char *dirData;//Init buffer for data
	hd_rw(current_dir_sector, HD_READ, 512, dirData);//Read data into buffer
	int i = 0;//Init counter
	while (i < 512)//Loop through entries in sector
	{
		int a = 0;//Init counter
		while(dirData[a] != ' ' &&  dirData[a] != 0x00)//See how long the filename is
		{
			a++;//Increment counter
		}
		if(dirData[2] != 0x00)//Make sure its a proper entry
		{
			write(STDOUT_FILENO, dirData, a);//Write content of entry
		}
		if(dirData[8] != ' ' && dirData[8] != 0x00 && dirData[2] != 0x00)//Check to see if there is a file extension
	 	{
			kprintf(".");
			write(STDOUT_FILENO, &dirData[8], 3);	
		}
		if(dirData[2] != 0x00)//Make sure its a proper entry
		{
			kprintf("\n");//Newline
		}
		i += 32;//Increment counter to next directory entry
		dirData += 32;//Increment pointer to next directory entry
	}
	kprintf("\n");//Padding
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
	return fileExists;//Return boolean of whether file exists
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
	return dirExists;//Return boolean of whether directory exists
}

//Credit to Keith S. for following function
int isBitSet(int value, int bitNumber)//Check to see if a specific bit is set
{
	int bit = (value & (1 << bitNumber-1)) != 0;//Check if bit is set
	return bit;//Return boolean of whether bit was set
}

int compName(char *a, char *b)//Check if name matches a string TODO: Rename this function
{
	char isSame = 1;//Init boolean variable
	int i = 0;//Init counter variable
	while(i < 11)//Loop through 11 byte filename
	{
		if(a[i] < 63) a[i] = ' ';//If null set to space
		if(b[i] < 63) b[i] = ' ';//If null set to space
		if(a[i] != b[i])//Check to see if they are different
		{ 
			isSame = 0;//They are different so the filenames are the not the sane
		}
		i++;//Increment counter
	}
	return isSame;//Return boolean
}
