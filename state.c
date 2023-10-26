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
	cpy->prev = stt;
	cpy->play = NULL;

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

int thereIsHope(State *stt, int max) {

	Node **colors = grCountColors(stt->wall);

	int ttl = 0, curr;

	for (int i = 0; i < grCols(stt->wall) * grRows(stt->wall); i++) {

		Node *aux = colors[i];
		Node *f;

		while (aux != NULL) {

			curr = aux->cCnt.cnt;

			if (curr < 2) continue;
			ttl += curr * (curr - 1);

			f = aux;
			aux = aux->next;
			free(f);

		}
	}

	free(colors);

	return stt->currScore + ttl >= max;

}

/*int thereIsHope(State *stt, int max) {

	int *oneD = grOneD(stt->wall);

	qsort(oneD + 1, oneD[0], sizeof(int), compare);

	int size = oneD[0];
	int curr = -1;
	int sm = 0, ttl = 0;

	for (int i = 1; i < size + 1; i++) {

		if (oneD[i] == -1) {

			ttl += sm * (sm - 1);
			break;

		}

		if (oneD[i] == curr) {

			sm++;

		}

		else {

			ttl += sm * (sm - 1);
			sm = 1;
			curr = oneD[i];

		}

	}

	free(oneD);

	return stt->currScore + (ttl * (ttl - 1)) >= max;

}*/


