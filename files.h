#ifndef _FILES_H_
#define _FILES_H_

#include <stdlib.h>

#include "header.h"
#include "dfs.h"


FILE *fileOpen(char *, char *);
void fileClose(FILE *);
int fileCheckExt(char *);
void fileChangeExt(char *);
void fileSep(FILE *);
void fileWriteCoords(FILE *, Coords *, Header *);

#endif

