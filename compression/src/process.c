#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_IN "file.txt"
#define FILE_OUT "zipped.txt"

int main() {
    FILE *fileIn = fopen(FILE_IN, "r");
    FILE *fileOut = fopen(FILE_OUT, "w");
    
    if (fileIn == NULL || fileOut == NULL ) {
        perror("Could not open file.");
        return 1;
        }
        
    fseek(fileIn, 0, SEEK_END);
    size_t fileSize = ftell(fileIn);
    fseek(fileIn, 0, SEEK_SET);
    
    int count = 0, index = 0;
    char currChar, prevChar;
    prevChar = '\0';
    char *zippedChars;
    zippedChars = malloc(fileSize);
    
    if (zippedChars == NULL) {
        perror("Memory allocation failed.");
        fclose(fileIn);
        }
    
    for (int i = 0; i < fileSize - 1; i++) {
        currChar = fgetc(fileIn);
        if ((int)currChar == EOF) {
            break;
            }
        if(currChar == prevChar) {
            prevChar = currChar;
            count++;
            continue;
            }
        if (currChar != prevChar && prevChar != '\0') {
            zippedChars[index] = count;
            index++;
            zippedChars[index] = currChar;
            index++;
            count = 0;
            prevChar = currChar;
            count++;
            }            
        }
    printf("%d, %d \n", count, index);
    printf("%s \n", zippedChars);
    fputs(zippedChars, fileOut);
    fclose(fileIn);
    fclose(fileOut);
    return 0;
    }
