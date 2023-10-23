#ifndef _PRIOQUEUE_H_
#define _PRIOQUEUE_H_

#include "item.h"

typedef struct _prioQueue PrioQueue;

PrioQueue *pqInit(int, int (*less)(Item, Item));
int pqEnqueue(Item, PrioQueue *);
Item pqDequeue(PrioQueue *);
int pqIsEmpty(PrioQueue *);
int pqIsFull(PrioQueue *);
void pqFree(PrioQueue *);
void pqFreeItems(PrioQueue *);

#endif
