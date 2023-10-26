#ifndef _STATE_H_
#define _STATE_H_

#include <stdlib.h>
#include <stdio.h>

#include "grid.h"
#include "item.h"

typedef struct _state State;

State *stateInit(int, int);
void stateRead(State *, FILE *);
State *stateCopy(State *);
void stateBlocks(State *);
void stateRmvBlock(State *);
Block *statePlay(State *);
int stateScore(State *);
Grid *stateWall(State *);
ColorCnt **stateColor(State *stt);
State *statePrev(State *);
int thereIsNeed(State *);
int stateClear(State *);
Grid *stateGrid(State *);
void stateFree(Item);
int thereIsHope(State *, int, ColorCnt **);

#endif
