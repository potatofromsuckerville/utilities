#include <stdio.h>

int main() {
    
    char *sample = "aaaahhuuukkkffkkgfgg";
    int count, currChar, prevChar, index;
    char asciiCount, zipped[25];
    prevChar = EOF;
    count = index = 0;
    int i = 0;

    while(1) {
        currChar = sample[i]; 
        
        if (i == 0) {
            prevChar = currChar;
            i++;
            count++;
            continue;
            }
        if ((char)currChar == '\0') {
            asciiCount = '0' + count;
            zipped[index++] = asciiCount;
            zipped[index++] = prevChar;
            prevChar = currChar;
            count = 0;         
            break;
            }
        if ((char)currChar == (char)prevChar) {
            i++;
            count++;
            continue;
            }
        
        asciiCount = '0' + count;
        zipped[index++] = asciiCount;
        zipped[index++] = prevChar;
        prevChar = currChar;
        count = 0;
        }
    zipped[index] = '\0';
    printf("%s \n", zipped);
    return 0;
    }
