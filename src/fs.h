void fs_init()
{
	char info;
	hd_rw(2048, HD_READ, 1, &info);
	write(STDOUT_FILENO, &info, 512);	
}
