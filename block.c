#include <stdlib.h>

#include "block.h"


struct _block {

	int x;
	int y;
	int num;

};

Block *blkInit(int x, int y, int num) {

	Block *blk = (Block *) malloc(sizeof(Block));

	blk->x = x;
	blk->y = y;
	blk->num = num;

	return blk;

}

int blkX(Block *blk) {

	return blk->x;

}

int blkY(Block *blk) {

	return blk->y;

}

int blkNum(Block *blk) {

	return blk->num;

}

void blkFree(Block *blk) {

	free(blk);

}

void blkChX(Block *blk, int x) {

	blk->x = x;

}

void blkChY(Block *blk, int y) {

	blk->y = y;

}

void blkChNum(Block *blk, int num) {

	blk->num = num;

}
