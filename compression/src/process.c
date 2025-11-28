#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "file.txt"
#define FILE_OUT "zipped.txt"

int main() {
    FILE *fileIn = fopen(FILE_IN, "r");

    fseek(fileIn, 0, SEEK_END);
    size_t fileSize = ftell(fileIn);
    fseek(fileIn, 0, SEEK_SET);
    
    char *zipped; 
    zipped = malloc(fileSize);

    int ch, i = 0;
    while ((ch = fgetc(fileIn)) != EOF) {
        zipped[i++] = (char)ch;
        }
    //~ zipped[i] = '\0';
    fclose(fileIn);
    printf("%s \n", zipped);
    return 0;
    }
