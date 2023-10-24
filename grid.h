#ifndef _GRID_H_
#define _GRID_H_

#include "prioQueue.h"
#include "block.h"


typedef struct _grid Grid;

Grid *grInit(int, int);
void grBlocks(Grid *, PrioQueue *);
Block *grBlock(Grid *, int, int, int);
void grBlock_rec(Grid *, int, int, int, int *, int);
void grPrint(Grid *);
void grRead(Grid *, FILE *);
Grid *grCopy(Grid *);
void grGravity(Grid *);
void grSlide(Grid *);
int *grOneD(Grid *);
void grFree(Grid *);

#endif
