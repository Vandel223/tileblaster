#ifndef _BLOCK_H_
#define _BLOCK_H_

typedef struct _block Block;

Block *blkInit(int, int, int);
Block *blkCopy(Block *);
int blkX(Block *);
int blkY(Block *);
int blkNum(Block *);
void blkFree(Block *);
void blkChX(Block *, int);
void blkChY(Block *, int);
void blkChNum(Block *, int);

#endif
