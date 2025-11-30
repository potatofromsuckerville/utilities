#include <stdio.h>
#include <string.h>

int main() {
    
    int currChar, prevChar;
    char asciiCount[12], zipped[25];
    
    int count = 0, index = 0;
    prevChar = EOF;
    int i = 0;

    char *sample = "aaaaaaaaaabbbbb";
    
    while(1) {
        currChar = sample[i]; 
        
        if (i == 0) {
            prevChar = currChar;
            i++;
            count++;  
            continue;
            }
        if ((char)currChar == '\0') {
            sprintf(asciiCount, "%d", count);
            strcpy(&zipped[index], asciiCount);
            index += strlen(asciiCount);
            zipped[index++]= prevChar;
            count = 0;         
            break;
            }
        if ((char)currChar == (char)prevChar) {
            i++;
            count++;
            continue;
            }
        
            sprintf(asciiCount, "%d", count);
            strcpy(&zipped[index], asciiCount);
            index += strlen(asciiCount);
            zipped[index++]= prevChar;
            count = 0;         
        }
    zipped[index] = '\0';
    printf("%s \n", zipped);
    return 0;
    }
