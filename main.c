#include <stdlib.h>
#include <stdio.h>

#include "files.h"
#include "header.h"
#include "state.h"
#include "dfs.h"


int main(int argc, char **argv) {

	/* Check if the program is being correctly called,
     * else go to help menu and exit */
    if (argc != 2) {                                                                                  
        exit(1);
    }

	char *filename = argv[1];                                                                         

    //if (fileCheckExt(filename) == 0) exit(1);

    /* Open the files */
    FILE *fileIn = fileOpen(filename, "r");
    //FILE *fileOut = fileOpen(filename, "w");

	Header *hd;
	int *numPlays, *score;
	numPlays = (int *) calloc(1, sizeof(int));
	score = (int *) calloc(1, sizeof(int));
	Coords *coords;

	while ((hd = hdrRead(fileIn)) != NULL) {

		hdrFPrint(hd, stdout);

		State *stt_i = stateInit(hdrC(hd), hdrR(hd));

		stateRead(stt_i, fileIn);
		stateBlocks(stt_i);

		if (hdrVar(hd) == -1) {

			coords = dfs(stt_i, 0, numPlays, score);
			for (int i = 0; i < hdrC(hd) * hdrR(hd) / 2; i++) {

				if (coords[i].x == 0) break;

				fprintf(stdout, "%d - %d\n", coords[i].x, coords[i].y);

			}

			free(coords);

			fprintf(stdout, "\n\n%d %d\n\n\n", *numPlays, *score);

		}

		else if (hdrVar(hd) >= 0) {

			coords = dfs(stt_i, hdrVar(hd), numPlays, score);

			if (coords == NULL) {printf("KA TENI\n"); continue;}

			for (int i = 0; i < hdrC(hd) * hdrR(hd) / 2; i++) {

				if (coords[i].x == 0) break;

				fprintf(stdout, "%d - %d\n", coords[i].x, coords[i].y);

			}

			free(coords);

			fprintf(stdout, "\n\n%d %d\n\n\n", *numPlays, *score);

		}

		else if (hdrVar(hd) == -3) {

			//dfs(var 3)

		}

		hdrFree(hd);

	}

	free(numPlays);
	free(score);
	fclose(fileIn);

	exit(0);

}
