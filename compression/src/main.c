#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "file.txt"
#define FILE_SIZE 1024

char* readFile(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    printf("Opening %s...\n", fileName);
    if (fp == NULL) {
	perror("Unable to open file.");
	return NULL;
	}
    int ch;
    char *content;
    content = malloc(FILE_SIZE);
    if (content == NULL) {
	fprintf(stderr, "Memory allocation failed.\n");
	fclose(fp);
	return NULL;
	}
    int i = 0;
    while ((ch = fgetc(fp)) != EOF && i < FILE_SIZE - 1) {
	content[i] = (char)ch;
	i++;
	}	
    content[i] = '\0';
    fclose(fp);
    return content;  
    }

int processContent(void) {
    char *content = readFile(FILE_NAME);
    if (content == NULL) return 0;
    int arrSize = strlen(content) + 1;
    printf("Initial content: %s\n", content);
    char* alphabets = malloc(arrSize);
    char* integers = malloc(arrSize);
    if (alphabets == NULL || integers == NULL) {
	fprintf(stderr, "Memory allocation failed.\n");
	free(content);
	free(alphabets);
	free(integers);
	return 0;
	}
    int k = 0, l = 0, j = 0;
    for (; j < arrSize - 1; j++) {
	if(content[j] >= '0' && content[j] <= '9') {
	    integers[k++] = content[j];
	    }
	else if (content[j] >= 'A' && content[j] <= 'Z') {
	    alphabets[l++] = content[j];
	    }
	}
    integers[k] = '\0';
    alphabets[l] = '\0';
    printf("separated alphabets: %s\n\n", alphabets);
    printf("separated integers: %s\n", integers);
    free(content);
    free(alphabets);
    free(integers);
    return 1;
    }
    
int main() {
    printf("File content manipulation test run... \n");
    processContent();
    return 0;
    }
