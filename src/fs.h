void fs_init()
{
	kprintf("Initializing filesystem...\n");
	char *info;
	unsigned int current_sector = 2129;
	hd_rw(current_sector, HD_READ, 512, info);
	int i  = 0;
	kprintf("FAT32 loaded...\n\nRoot Directory ->\n");
	while(i < 256)
	{
		write(STDOUT_FILENO, info, 32);
		kprintf("\n");
		i += 64;
		info += 64;
	}
	kprintf("\n");		
}
