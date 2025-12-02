#include <stdio.h>

int main(int argc, char* argv[]) {
    int i;
    char array[12] = {'\0'};
    
    for (i = 0; i < 10; i++) {
        array[i] = '0' + i;
        }
    printf("%s \n", array);
    printf("%c %d %d \n", array[9], array[10], array[11]);
    i = 0;
    printf("%c \n", array[i++]);
    i = 0;
    printf("%c \n", array[++i]);
    printf("%c %d \n", EOF, EOF);
    
    if (argc < 2) {
        printf("Usage %s <filename> \n", argv[0]);
        return 1;
        }
        
    printf("Processing file %s \n", argv[1]); 
    return 0;
    }
