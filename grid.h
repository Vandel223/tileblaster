#ifndef _GRID_H_
#define _GRID_H_

#include <stdio.h>

#include "prioQueue.h"
#include "block.h"
#include "linkList.h"


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
Node **grCountColors(Grid *);
int grTiles(Grid *);
int *grOneD(Grid *);
int grCols(Grid *);
int grRows(Grid *);
void grFree(Grid *);

#endif
