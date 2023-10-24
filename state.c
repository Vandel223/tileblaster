#include <stdlib.h>

#include "grid.h"
#include "prioQueue.h"


struct _state {

	Grid *wall;
	PrioQueue *legMovs;
	int currScore;
	_state *prev;

}

int less(Item a, Item b) {

	return blkNum((Block *) a) < blkNum((Block *) b);

}

int compare(Item a, Item b) {

	return *((int *) b) - *((int *) a);

}

State *stateInit(int col_num, int row_num, State *prev) {

	State *stt = (State *) malloc(sizeof(State));

	stt->wall = grInit(col_num, row_num);
	stt->legMovs = pqInit(col_num * row_num / 2, less);
	stt->currScore = 0;
	stt->prev = prev;

	return stt;

}

void stateRead(State *stt, FILE *fp) {

	grRead(stt->wall, fp);

}

State *stateCopy(State *stt) {

	State *cpy = (State *) malloc(sizeof(State));

	cpy->wall = grCopy(stt->wall);
	cpy->legMovs = pqCopy(stt->legMovs);
	cpy->currScore = stt->currScore;
	stt->prev = NULL;

}

void stateRead(State *stt) {

	grBlocks(stt->wall, stt->legMovs);

}

void stateRmvBlock(State *stt) {

	Block *blk = pqDequeue(stt->legMovs);

	grBlock(stt->wall, blkX(blk), blkY(blk), 1);

	int n = blkNum(blk);
	stt->currScore += n * (n - 1);

	grGravity(stt->wall);
	grSlide(stt->wall);

}

int stateClear(State *stt) {

	return isEmpty(stt->legMovs);

}

int thereIsHope(State *stt, int max) {

	int *oneD = grOneD(stt->wall);

	qsort(oneD + 1, oneD[0], sizeof(int), compare);

	int curr = -1, sm = 0, ttl = 0;

	for (int i = 1; i < oneD[0]; i++) {

		if (oneD[i] == -1) break;

		if (curr == oneD[i]) sm++;

		else {

			ttl += sm * (sm - 1);
			curr = oneD[i];

		}

	}

	free(oneD);

	return ttl >= max;

}

