#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/process.h"

int main(int argc, char **argv) {
    if (argc < 2) {
	printf("Usage: %s <filename> \n", argv[0]);
	return MISSING_FILE_ARGUMENT;
	}
    compress(argv[1]);
    
    return 0;
    }
