#include <stdio.h>
#include <string.h>
#define FILE_IN "file.txt"
#define FILE_OUT "zipped.txt"
#define MAX_FILE_SIZE 1024 // 1kb max file  

int main() {
    FILE *fileIn = fopen(FILE_IN, "r");
    FILE *fileOut = fopen(FILE_OUT, "a");
    if (fileIn == NULL || fileOut == NULL ) {
        perror("Could not open file.");
        return 1;
        }
    int ch; 
    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        ch = fgetc(fileIn);
        if (ch == EOF) {
            break;
            }
        fputc((char)ch, fileOut);
        }
    fclose(fileIn);
    fclose(fileOut);
    return 0;
    }
