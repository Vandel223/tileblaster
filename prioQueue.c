#include <stdlib.h>
#include <stdio.h>

#include "item.h" 
#include "prioQueue.h"


struct _prioQueue {

	Item * Heap;				/* Heap */
	int free;					/* First free index in Heap */
	int hsize;					/* Size of Heap */
	int (*less)(Item, Item);	/* Prio function in Heap */

};

/* Heap implementation is done here */

void fixUp(Item *Heap, int id, int (*less)(Item, Item)) {

	/* While we don't reach the top and heap codition is not met,
	   i.e., while every child isn't less than its parent... */
	while (id > 0 && less(Heap[(id - 1)/2], Heap[id])) {

		/* ... we switch parent and child */
		exch(Heap[(id - 1)/2], Heap[id]);
		id = (id - 1) / 2;

	}

}

void fixDown(Item *Heap, int id, int curSize, int (*less)(Item, Item)) {

	int child;

	/* While we don't reach any leaf... */
	while ((child = id*2 + 1) < curSize) {

		/* ... check if there isn't only one child, i.e., check if
		   child + 1 exists, and choose the one with most priority... */
		if (child + 1 < curSize && less(Heap[child], Heap[child + 1])) child++; 

		/* ... also check if heap condition is already met... */
		if (less(Heap[child], Heap[id])) break;

		/* ... and finally switch child and parent */
		exch(Heap[child], Heap[id]);
		id = child;

	}

}

/* End of Heap implementation */

/* PQueue implementation */

PrioQueue *pqInit(int size, int (*less)(Item, Item)) {

	/* Initialize PrioQueue pointer to return */
	PrioQueue *pq = (PrioQueue *) malloc(sizeof(PrioQueue));

	if (pq != NULL) {

		pq->Heap = (Item *) calloc(size, sizeof(Item));	/* Alloc space for Heap(size) */
		pq->free = 0;										/* Initialize empty Heap */
		pq->hsize = size;									/* Store size of Heap for later */
		pq->less = less;									/* Store prio function in this Heap */

	}

	return pq;											/* Note: In case of fail, returns NULL */

}

int pqEnqueue(Item it, PrioQueue *pq) {

	/* If PrioQueue isn't full yet ... */
	if (!pqIsFull(pq)) {

		/* ... store Item in last position and fix Heap upwards from Item */
		pq->Heap[(pq->free)++] = it;
		fixUp(pq->Heap, pq->free - 1, pq->less);

		/* Return success */
		return 1;

	}

	/* Return fail, i.e., PrioQueue is full */
	return 0;

}

Item pqDequeue(PrioQueue *pq) {

	/* If PrioQueue isn't empty ... */
	if (!pqIsEmpty(pq)) {

		exch(pq->Heap[0], pq->Heap[pq->free - 1])		/* ... switch top with last ... */
		fixDown(pq->Heap, 0, pq->free - 1, pq->less);	/* ... fix downwards Heap from top ... */
		return pq->Heap[--(pq->free)];					/* ... and return the most prio Item
														   that is now on the last position */

	}

	/* Return fail, i.e., PrioQueue is empty */
	return NULL;

}

int pqIsEmpty(PrioQueue *pq) {

	return pq->free == 0;

}

int pqIsFull(PrioQueue *pq) {

	return pq->free == pq->hsize;

}

void pqFree(PrioQueue *pq) {

	pqFreeItems(pq);	/* Free everything inside PrioQueue */
	free(pq->Heap);		/* Free Heap */
	free(pq);			/* Free the PrioQueue struct */

}

void pqFreeItems(PrioQueue *pq) {

	/* Iterate through everything inside Heap, even if not considered anymore,
	   i.e., even if free <= index */
	for (int i = 0; i < pq->hsize; i++) {

		if (pq->Heap[i] != NULL) free(pq->Heap[i]);

	}

}

