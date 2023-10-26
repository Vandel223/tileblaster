#ifndef _DFS_H_
#define _DFS_H_

#include "stack.h"
#include "state.h"


typedef struct {

	int x;
	int y;

} Coords;

State *makePlay(State *);
Coords *backTrack(State *);
Coords *dfs(State *, int, int *, int *);

#endif

