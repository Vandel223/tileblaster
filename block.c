#include <stdlib.h>

#include "block.h"


struct _block {                                                                                      

    int x;
    int y;
    int num;
	int color;

};

Block *blkInit(int x, int y, int num, int color) {

	Block *blk = (Block *) malloc(sizeof(Block));

	blk->x = x;
	blk->y = y;
	blk->num = num;
	blk->color = color;

	return blk;

}

Block *blkCopy(Block *blk) {

	Block *cpy = (Block *) malloc(sizeof(Block));

	cpy->x = blk->x;
	cpy->y = blk->y;
	cpy->num = blk->num;
	cpy->color = blk->color;

	return cpy;

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

int blkColor(Block *blk) {

	return blk->color;

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
