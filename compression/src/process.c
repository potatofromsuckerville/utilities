#include <stdio.h>
#include <string.h>

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
    int count = 0;
    
    prevChar = fgetc(fileIn);
    count++;
    while(1) {
        currChar = fgetc(fileIn);
        break;
        }
    printf("%c %c \n", prevChar, currChar);
    fclose(fileIn);
    
    return 0;
    }
