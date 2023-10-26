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
State *statePrev(State *);
int stateClear(State *);
void stateFree(Item);
int thereIsHope(State *, int);

#endif
