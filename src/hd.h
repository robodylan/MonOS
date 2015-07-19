int HD_WRITE = 0x30;
int HD_READ = 0x20;

void hd_rw(unsigned int LBA, unsigned int com, unsigned int sectors_to_access, char *buf) 
{
	unsigned int tmpword;//Temporary storage of data
	while((read_port(0x1F7)&0xC0) != 0x40);//Wait until disk is ready
	write_port(0x1F1, 0x00);//Send null byte
	write_port(0x1F2, sectors_to_access);
	write_port(0x1F3, LBA);//Lowest 8-bits of LBA
	write_port(0x1F4, LBA >> 8);//Next 8-bits of LBA
	write_port(0x1F5, LBA >> 16);//Next 8-bits of LBA
	write_port(0x1F6, (0xE0 | ((0) << 4) | ((LBA >> 24) & 0x0F)));//Last 8-bits of LBA plus drive
	write_port(0x1F7, (unsigned char)com);//Send operation
	while(!(read_port(0x1F7) & 0x08));
	if(com == HD_READ)
	{
		int i = 0;
		while(i < (256 * sectors_to_access))
		{
			tmpword = read_port(0x1F0);
			buf[i * 2]=(unsigned char)tmpword;
			buf[i * 2 + 1] =(unsigned char)(tmpword >> 8);
			i++;
		} 
	}
	if(com == HD_WRITE)
	{
		int i = 0;
		while(i < (256 * sectors_to_access))
		{
			tmpword = buf[8 + i * 2] | buf[8 + i * 2 + 1] << 8;
			write_port(0x1F0, tmpword);
		}
	}
}
