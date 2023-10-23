#include <stdlib.h>
#include <stdio.h>

#include "files.h"
#include "header.h"
#include "block.h"
#include "prioQueue.h"
#include "grid.h"
#include "item.h"


int less(Item a, Item b) {

	int nA = blkNum((Block *) a);
	int nB = blkNum((Block *) b);

	return nA < nB;

}

int main() {

	char filename[] = "Ficheiros_testes/Manywalls50.tilewalls";

	if (fileCheckExt(filename) == 0) exit(1);

	FILE *fp = fileOpen(filename, "r");

	Header *hdr = hdrRead(fp);

	Grid *gr = grInit(hdrC(hdr), hdrR(hdr));
	PrioQueue *pq = pqInit(hdrC(hdr) * hdrR(hdr) / 2, less);

	grRead(gr, fp);
	grBlocks(gr, pq);
	Grid *cpy = grCopy(gr);
	grPrint(gr);
	grPrint(cpy);

	while (!pqIsEmpty(pq)) {
		Block *blk = (Block *) pqDequeue(pq);
		printf("%d - %d: val = %d\n", blkX(blk), blkY(blk), blkNum(blk));
	}

	grFree(gr);
	grFree(cpy);
	pqFree(pq);
	hdrFree(hdr);

	exit(0);

}
