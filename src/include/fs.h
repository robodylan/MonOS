#ifndef FS_H
#define FS_H

extern unsigned int current_dir_sector;//Begin at root directory location

int fs_init();
int fs_cat_file(char *name);
int fs_open_dir(char *name);
int fs_ls_dir(void);
int fs_file_exists(char *filename);
int fs_dir_exists(char *dirname);
int isBitSet(int value, int bitNumber);
int compName(char *a, char *b);

#endif // FS_H
