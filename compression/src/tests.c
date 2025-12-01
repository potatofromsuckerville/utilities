#include <stdio.h>
#include <string.h>

int main() {
    char *sample = "aaaaaaaaaabbbbcdde";
    char strCount[20], zipped[30];
    
    int prevChar, currChar;
    int i = 0;
    int count = 0;
    int index = 0;
    
    if (i == 0) {
        currChar = sample[i++];
        prevChar = currChar;
        count++;
        }
        
    while(1) {
        currChar = sample[i++];
        if ((char)currChar == (char)prevChar) {
            prevChar = currChar;
            count++;
            continue;
            }
        if ((char)currChar != (char)prevChar && (char)currChar != '\0') {
            sprintf(strCount, "%d", count);
            strcpy(&zipped[index], strCount);
            index += strlen(strCount);
            zipped[index++] = prevChar;
            prevChar = currChar;
            count = 1;
            continue;
            }
        if ((char)currChar == '\0') {
            sprintf(strCount, "%d", count);
            strcpy(&zipped[index], strCount);
            index += strlen(strCount);
            zipped[index++] = prevChar;
            prevChar = currChar;
            count = 1;
            break;
            }
        }
        
    zipped[index] = '\0';
    printf("Original string: %s\n", sample);
    printf("Compressed string: %s\n", zipped);
    
    return 0;
    }
