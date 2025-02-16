#include <stdlib.h>
#include <stdio.h>

#include "header.h"


struct _header {

	int row_num;
	int col_num;
	int var;

};

Header *hdrRead(FILE *fp) {

	Header *hdr = (Header *) malloc(sizeof(Header));

	if (fscanf(fp, "%d %d %d", &hdr->row_num, &hdr->col_num, &hdr->var) == 3) return hdr;

	else {

		hdrFree(hdr);
		return NULL;

	}

}

void hdrFPrint(Header *hdr, FILE *fp) {

	fprintf(fp, "%d %d %d\n", hdrR(hdr), hdrC(hdr), hdrVar(hdr));

}

int hdrR(Header *hdr) {

	return hdr->row_num;

}

int hdrC(Header *hdr) {

	return hdr->col_num;

}

int hdrVar(Header *hdr) {

	return hdr->var;

}

void hdrFree(Header *hdr) {

	free(hdr);

}

