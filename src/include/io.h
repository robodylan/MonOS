#ifndef IO_H
#define IO_H

extern char print_color;
extern const char STDOUT_FILENO;
extern const char STDIN_FILENO;
extern char *MEM_FILELOC;
extern char *vidptr;

extern int curpos;

int write(int fd,const char *buf,int nbytes);
int read(int fd,char *buf,int nbytes);
int open(const char *filename, int flags);
int close(const char fd);

#endif // IO_H
