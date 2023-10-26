#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "files.h"
#include "header.h"
#include "dfs.h"


/* fileOpen
 * Description: Opens the file and checks if it was successful
 * Arguments:   filename - name of the file
 * 				mode - mode in which to open file
 * Return:      Pointer to file
 */
FILE *fileOpen(char *filename, char *mode) {

    FILE *file;

    file = fopen(filename, mode);
 
    /* Check if file opened correctly,
     * else exit */
    if (file == NULL) {
        exit(1);
    }   

    return file;

}

void fileClose(FILE *file) {

    if (fclose(file) == EOF) {
        exit(1);
    }

}

int fileCheckExt(char *filename) {

    char *ext = strrchr(filename, '.');

    if (ext == NULL || strcmp(ext, ".tilewalls")) {
        return 0;
    }

	return 1;

}

void fileChangeExt(char *filename) {
	char *ext = strrchr(filename, '.');
    memcpy(ext, ".tileblasts\0", 12);
}

void fileWriteCoords(FILE *fp, Coords *coords, Header *hd) {

    for (int i = 0; i < hdrC(hd) * hdrR(hd) / 2; i++) {
        if (coords[i].x == 0) break;
        fprintf(fp, "%d %d\n", coords[i].y, coords[i].x);
    }
}

void fileSep(FILE *fp) {

	fprintf(fp, "\n");

}

