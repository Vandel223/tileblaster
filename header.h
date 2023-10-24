#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdlib.h>


typedef struct _header Header;

Header *hdrRead(FILE *);
void hdrFPrint(Header *, FILE *);
int hdrR(Header *);
int hdrC(Header *);
int hdrVar(Header *);
void hdrFree(Header *);

#endif

