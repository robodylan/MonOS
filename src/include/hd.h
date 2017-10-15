#ifndef HD_H
#define HD_H

extern int HD_WRITE;
extern int HD_READ;

void hd_rw(unsigned int LBA, unsigned int com, unsigned int sectors_to_access, char *buf);

#endif // HD_H
