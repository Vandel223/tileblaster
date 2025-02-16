#ifndef _PRIOQUEUE_H_
#define _PRIOQUEUE_H_

#include "item.h"

typedef struct _prioQueue PrioQueue;

PrioQueue *pqInit(int, int (*less)(Item, Item));
PrioQueue *pqCopy(PrioQueue *);
int pqEnqueue(Item, PrioQueue *);
Item pqDequeue(PrioQueue *);
int pqIsEmpty(PrioQueue *);
int pqIsFull(PrioQueue *);
int pqSize(PrioQueue *);
void pqFree(PrioQueue *);
void pqFreeItems(PrioQueue *);

#endif
