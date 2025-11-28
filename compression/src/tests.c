#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "file.txt"
#define MAX_FILE_SIZE 1024

char* readFile(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }
    
    char *content = malloc(MAX_FILE_SIZE + 1);
    if (content == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        return NULL;
    }
    
    int ch, i = 0;
    while ((ch = fgetc(fp)) != EOF && i < MAX_FILE_SIZE) {
        content[i++] = ch;
    }
    content[i] = '\0';
    
    fclose(fp);
    return content;
}

int processContent(void) {
    char *content = readFile(FILE_NAME);
    if (content == NULL) {
        return 0;
    }
    
    size_t len = strlen(content);
    char *alphabets = malloc(len + 1);
    char *integers = malloc(len + 1);
    
    if (alphabets == NULL || integers == NULL) {
        perror("Memory allocation failed");
        free(content);
        free(alphabets);  // Safe even if NULL
        free(integers);
        return 0;
    }
    
    int k = 0, l = 0;
    for (size_t j = 0; j < len; j++) {
        if (content[j] >= '0' && content[j] <= '9') {
            integers[k++] = content[j];
        }
        else if (content[j] >= 'A' && content[j] <= 'Z') {
            alphabets[l++] = content[j];
        }
    }
    integers[k] = '\0';
    alphabets[l] = '\0';
    
    printf("Initial content: %s\n", content);
    printf("Separated alphabets: %s\n", alphabets);
    printf("Separated integers: %s\n", integers);
    
    free(content);
    free(alphabets);
    free(integers);
    return 1;
}

int main(void) {
    processContent();
    return 0;
}
