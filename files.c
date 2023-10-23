#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "files.h"


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

