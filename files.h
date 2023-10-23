#ifndef _FILES_H_
#define _FILES_H_

#include <stdlib.h>

FILE *fileOpen(char *, char *);
void fileClose(FILE *);
int fileCheckExt(char *);

#endif

