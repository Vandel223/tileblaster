#include <stdlib.h>
#include <stdio.h>

#include "prioQueue.h"
#include "grid.h"
#include "block.h"
#include "linkList.h"


struct _grid {

	int ** Gr;		/* Grid */
	int ** visited;	/* Grid of visited tiles */
	int col_num;	/* Num of columns */
	int row_num;	/* Num of rows */

};

Grid *grInit(int col_num, int row_num) {                                                          

    Grid *gr = (Grid *) malloc(sizeof(Grid));
    
    /* First allocate columns */
	gr->Gr = (int **) malloc(col_num * sizeof(int *));
	gr->visited = (int **) malloc(col_num * sizeof(int *));

    /* Then for each column allocate the rows */
    for (int i = 0; i < col_num; i++) {
		gr->Gr[i] = (int *) malloc(row_num * sizeof(int));
		gr->visited[i] = (int *) calloc(row_num, sizeof(int));	/* Note: important to initialize
																   as zero, i.e., all tiles
																   unvisited */
	}

	gr->col_num = col_num;
	gr->row_num = row_num;

    return gr;

}

void grBlocks(Grid *gr, PrioQueue *pq) {

	for (int i = 0; i < gr->col_num; i++) {

		for (int j = 0; j < gr->row_num; j++) {

			if (gr->Gr[i][j] == -1 || gr->visited[i][j] == 1) continue;

			Block *blk = grBlock(gr, i + 1, gr->row_num - j, gr->Gr[i][j]);
			if (blkNum(blk) > 1) pqEnqueue((Item) blk, pq);
			else blkFree(blk);

		}

	}

}

Block *grBlock(Grid *gr, int x, int y, int rm) {

	int cnt = 0, color = gr->Gr[x - 1][gr->row_num - y];

	if (color == -1) return blkInit(x, y, 0, -1);

	grBlock_rec(gr, x, y, color, &cnt, rm);

	if (rm == 1) return NULL;

	Block *blk = blkInit(x, y, cnt, color);

	return blk;

}

void grBlock_rec(Grid *gr, int x, int y, int color, int *cnt, int rm) {

    if (x == 0 || x > gr->col_num || y == 0 || y > gr->row_num) return;

    if (gr->visited[x - 1][gr->row_num - y] == 0 && gr->Gr[x - 1][gr->row_num - y] == color) {
        (*cnt)++;
        if (rm == 0) gr->visited[x - 1][gr->row_num - y] = 1;
		else gr->Gr[x - 1][gr->row_num - y] = -1;
    }   
    else {
        return;
    }

    grBlock_rec(gr, x+1, y, color, cnt, rm);
    grBlock_rec(gr, x, y+1, color, cnt, rm);
    grBlock_rec(gr, x-1, y, color, cnt, rm);
    grBlock_rec(gr, x, y-1, color, cnt, rm);

}


void grPrint(Grid *gr) {

	printf("\n%d x %d\n\n", gr->row_num, gr->col_num);

	for (int j = 0; j < gr->row_num; j++) {

		printf("%d:\t", gr->row_num - j);

		for (int i = 0; i < gr->col_num; i++) printf("%d ", gr->Gr[i][j]);

		printf("\n");

	}

	printf("\n\t");

	for (int i = 0; i < gr->col_num; i++) printf("%d ", i + 1);

	printf("\n\n");

	for (int j = 0; j < gr->row_num; j++) {

		printf("%d:\t", gr->row_num - j);

		for (int i = 0; i < gr->col_num; i++) printf("%d ", gr->visited[i][j]);

		printf("\n");

	}

	printf("\n\t");

	for (int i = 0; i < gr->col_num; i++) printf("%d ", i + 1);

	printf("\n\n");

}

void grRead(Grid *gr, FILE *file) {

    int total = gr->row_num * gr->col_num, cnt = 0, read = 0;
    int i = 0, j = 0;

	/* While we don't reach the end */
    while (cnt < total) {

		/* Read a number and check how many numbers were read (0 or 1) */
		read = fscanf(file, "%d", &(gr->Gr[i][j]));

		/* Increment cnt by how many numbers were read */
		cnt += read;

		/* Iterate through grid with i - columns and j - rows */
		i += read;
		if (i == gr->col_num) {
			i = 0;
			j++;
		}

	}

}

void colorsUpdate(ColorCnt **colors, Block *blk, Grid *gr) {

	int hash = blkColor(blk) % (gr->row_num * gr->col_num);

	while (colors[hash] != NULL && colors[hash]->color != blkColor(blk)) hash++;

	if (colors[hash] == NULL) return;

	colors[hash]->cnt -= blkNum(blk);

}

Grid *grCopy(Grid *gr) {

	Grid *cpy = grInit(gr->col_num, gr->row_num);

	for (int i = 0; i < gr->col_num; i++)

		for (int j = 0; j < gr->row_num; j++)

			cpy->Gr[i][j] = gr->Gr[i][j];

	return cpy;

}

ColorCnt **colorsCopy(ColorCnt **colors, Grid *gr) {

	ColorCnt **copy = (ColorCnt **) calloc(gr->row_num * gr->col_num, sizeof(ColorCnt *));

	for (int i = 0; i < gr->row_num * gr->col_num; i++) {

		if (colors[i] != NULL) {

			copy[i] = (ColorCnt *) malloc(sizeof(ColorCnt));

			copy[i]->cnt = colors[i]->cnt;
			copy[i]->color = colors[i]->color;

		}

	}

	return copy;

}

void grGravity(Grid *gr) {

    int fallHeight = 0;
    int aux;
	int row_num = gr->row_num, col_num = gr->col_num;

    for (int i = 0; i < col_num; i++, fallHeight = 0) {
        for (int j = 0; j < row_num; j++) {
            if (gr->Gr[i][row_num - j - 1] == -1) {
                fallHeight++;
                continue;
            }   
            if (fallHeight > 0) {
                aux = gr->Gr[i][row_num - j - 1 + fallHeight];
                gr->Gr[i][row_num - j - 1 + fallHeight] = gr->Gr[i][row_num - j - 1]; 
                gr->Gr[i][row_num - j - 1] = aux;
            }   
        }   
    }   
}

void grSlide(Grid *gr) {

    int slideLen = 0;
    int *aux;
	int row_num = gr->row_num, col_num = gr->col_num;

    for (int i = col_num-1; i >= 0; i--) {
        if (gr->Gr[i][row_num - 1] == -1) { /* slide is always used after gravity */
            slideLen++;
            continue;
        }
        if (slideLen > 0) {
            aux = gr->Gr[i + slideLen];
            gr->Gr[i + slideLen] = gr->Gr[i];
            gr->Gr[i] = aux;
        }
    }
}

void grColorsFree(Grid *gr, ColorCnt **colors) {

	for (int i = 0; i < gr->row_num * gr->col_num; i++) if (colors[i] != NULL) free(colors[i]);

	free(colors);

}

ColorCnt **grCountColors(Grid *gr) {

	int size = gr->col_num * gr->row_num;

	ColorCnt **colors = (ColorCnt **) calloc(size, sizeof(ColorCnt *));

	int hash;

	for (int i = 0; i < gr->col_num; i++)

		for (int j = 0; j < gr->row_num; j++)  {

			int tile = gr->Gr[i][j];
			hash = (tile % (size));


			while (colors[hash] != NULL && colors[hash]->color != tile) hash++;

			if (colors[hash] == NULL) {

				ColorCnt *aux = (ColorCnt *) malloc(sizeof(ColorCnt));

				aux->color = tile;
				aux->cnt = 0;
				colors[hash] = aux;

			}

			(colors[hash]->cnt)++;

		}

	return colors;

}

int grCols(Grid *gr) {

	return gr->col_num;

}

int grRows(Grid *gr) {

	return gr->row_num;

}

void grFree(Grid *gr) {

	for (int i = 0; i < gr->col_num; i++) {
		free(gr->Gr[i]);
		free(gr->visited[i]);
	}

	free(gr->Gr);
	free(gr->visited);
	free(gr);

}
