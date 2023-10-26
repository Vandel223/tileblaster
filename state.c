#include <stdlib.h>
#include <stdio.h>

#include "grid.h"
#include "prioQueue.h"
#include "state.h"
#include "block.h"
#include "item.h"
#include "linkList.h"


struct _state {

	Grid *wall;
	PrioQueue *legMovs;
	int currScore;
	struct _state *prev;
	Block *play;
	ColorCnt **colors;

};

int less(Item a, Item b) {

	return blkNum((Block *) a) < blkNum((Block *) b);

}

int compare(const Item a, const Item b) {

	return *((int *) b) - *((int *) a);

}

State *stateInit(int col_num, int row_num) {

	State *stt = (State *) malloc(sizeof(State));

	stt->wall = grInit(col_num, row_num);
	stt->legMovs = pqInit(col_num * row_num / 2, less);
	stt->currScore = 0;
	stt->prev = NULL;
	stt->play = NULL;
	stt->colors = NULL;

	return stt;

}

void stateRead(State *stt, FILE *fp) {

	grRead(stt->wall, fp);
	stt->colors = grCountColors(stt->wall);

}

State *stateCopy(State *stt) {

	State *cpy = (State *) malloc(sizeof(State));

	cpy->wall = grCopy(stt->wall);
	cpy->legMovs = pqCopy(stt->legMovs);
	cpy->currScore = stt->currScore;
	cpy->prev = stt;
	cpy->play = NULL;
	cpy->colors = colorsCopy(stt->colors, stt->wall);

	return cpy;

}

void stateBlocks(State *stt) {

	grBlocks(stt->wall, stt->legMovs);

}

void stateRmvBlock(State *stt) {

	Block *blk = (Block *) pqDequeue(stt->prev->legMovs);

	grBlock(stt->wall, blkX(blk), blkY(blk), 1);

	stt->play = blkCopy(blk);

	int n = blkNum(blk);
	stt->currScore += n * (n - 1);

	colorsUpdate(stt->colors, blk, stt->wall);

	blkFree(blk);

	grGravity(stt->wall);
	grSlide(stt->wall);

}

Block *statePlay(State *stt) {

	return stt->play;

}

int stateScore(State *stt) {

	return stt->currScore;

}

Grid *stateWall(State *stt) {

	return stt->wall;

}

State *statePrev(State *stt) {

	return stt->prev;

}

int stateClear(State *stt) {

	return pqIsEmpty(stt->legMovs);

}

void stateFree(Item stt) {

	grFree(((State *) stt)->wall);
	pqFree(((State *) stt)->legMovs);
	if (((State *)stt)->play != NULL) free(((State *) stt)->play);
	free(stt);

}

Grid *stateGr(State *stt) {

	return stt->wall;

}

ColorCnt **stateColor(State *stt) {

	return stt->colors;

}

int thereIsHope(State *stt, int max, ColorCnt **colors) {

	int ttl = stt->currScore, val;

	for (int i = 0; i < grCols(stt->wall) * grRows(stt->wall); i++) {

		if (colors[i] == NULL) continue;

		val = colors[i]->cnt;

		ttl += val * (val - 1);

	}

	return ttl >= max;

}

