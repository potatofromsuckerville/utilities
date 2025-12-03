#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("Usage: %s <file_name> \n", argv[0]);
        return 1;
        }
    FILE *file_in = fopen(argv[1], "rb");
    
    if (file_in == NULL) {
        perror("Could not open file.");
         return 1;
        }
    if (fseek(file_in, 0, SEEK_END) != 0) {
        perror("fseek failed.");
        fclose(file_in);
        return 1;
        }
    size_t fileSize = ftell(file_in);
    if (fileSize == -1L) {
        perror("ftell failed.");
        fclose(file_in);
        return 1;
        }
    fseek(file_in, 0, SEEK_SET);
    
    int i = 0;
    
    char *content = malloc(fileSize);
    if (content == NULL) {
        perror("Memory allocation failed.");
        fclose(file_in);
        return 1;
        }
    int ch;
    while((ch = fgetc(file_in)) != EOF) {
        content[i] = (char)ch;
        i++;
        }
    content[i] = '\0';
    char *extracted = malloc(fileSize * 3);
    if (extracted == NULL) {
        perror("Memory allocation failed");
        free(content);
        fclose(file_in);
        return 1;
        }

    int count, index;
    count = 0;
    i = 0;
    index = 0;
    char characters;
    while (1) {
        characters = content[i];
        if (characters != '\0') {
            if (characters >= '0' && characters <= '9') {
                count *= 10;
                count += (int)characters;
                i++;
                continue;
                }
            
            if ((characters >= 'a' && characters <= 'z') ||
                (characters >= 'A' && characters <= 'Z')) {
                for (int j = 0; j < count; j++) {
                    extracted[index] = characters;
                    index++;
                    }
                count = 0;
                continue;                    
                }            
            }
        break;
        }
        
    FILE *file_out = fopen("extracted.txt", "wb");
    if (file_out == NULL) {
        perror("Could not create file.");
        fclose(file_in);
        free(content);
        free(extracted);
        return 1;
        }
    
    printf("Compressed file content: %s \n", content);
    printf("Extracted file content: %s \n", extracted);
    
    fclose(file_in);
    free(content);
    fclose(file_out);    
    free(extracted);
    
    return 0;
    }
