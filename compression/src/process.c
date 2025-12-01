#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    
    FILE *fileIn = fopen("file.txt", "r");
    
    if (fileIn == NULL) {
        perror("Could not open file.");
        return 1;
        }
    
    size_t fileSize;
        
    if (fseek(fileIn, 0, SEEK_END) != 0) {
        perror("fseek failed.");
        return 1;
        }
    if ((fileSize = ftell(fileIn)) == -1L) {
        perror("ftell failed");
        }
        
    fseek(fileIn, 0, SEEK_SET);
    
    int currChar, prevChar;
    char asciiCount[12];
    
    char *zipped = malloc(fileSize);

    prevChar = fgetc(fileIn);
    int count = 1;
    int i = 0;

    if (zipped == NULL) {
        perror("Memory allocation failed.");
        fclose(fileIn);
        return 1;
        }
    
    while(1) {
        currChar = fgetc(fileIn);
        if (currChar == prevChar) {
            prevChar = currChar;
            count++;
            continue;
            }
        if (currChar != prevChar && currChar != EOF) {
            sprintf(asciiCount, "%d", count);
            strcpy(&zipped[i], asciiCount);
            i += strlen(asciiCount);
            zipped[i++] = prevChar;
            prevChar = currChar;
            count = 1;
            continue;
            }
            
        if (currChar == EOF) {
            
            break;
            }
        }
        
    zipped[i] = '\0';
    FILE *fileOut = fopen("zipped.txt", "w");
    if (fileOut == NULL) {
        perror("Unable to create zipped file");
        free(zipped);
        fclose(fileIn);
        return 1;
        }
        
    fputs(zipped, fileOut);
    
    size_t zippedSize;
    
    if (fseek(fileOut, 0, SEEK_END) != 0) {
        perror("fseek failed");
        free(zipped);
        fclose(fileOut);
        fclose(fileIn);
        return 1;
        }
        
    if ((zippedSize = ftell(fileOut)) == -1L) {
        perror("ftell failed");
        free(zipped);
        fclose(fileOut);
        fclose(fileIn);        
        return 1;
        }
    
    fseek(fileOut, 0, SEEK_SET);

    rewind(fileIn);
    printf("Original: ");
    char *original = malloc(fileSize);
    if (original == NULL) {
        perror("Memory allocation failed.");
        free(zipped);
        fclose(fileIn);
        fclose(fileOut);
        return 1;
        }
    while(fgets(original, sizeof(original), fileIn) != NULL){
        printf("%s", original);
        }
    printf(" (%zu bytes)", fileSize);
    printf("\n");
    printf("Compressed: %s (%zu bytes)\n", zipped, zippedSize);
    
    
    free(original);
    free(zipped);
    fclose(fileOut);
    fclose(fileIn);
    
    return 0;
    }
