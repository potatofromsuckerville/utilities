#include <stdio.h>
#include <stdlib.h>

// Read file as binary, return size
unsigned char* read_binary(const char *filename, size_t *size) {
    FILE *f = fopen(filename, "rb");  // 'b' = binary mode
    if (!f) return NULL;
    
    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    unsigned char *data = malloc(*size);
    fread(data, 1, *size, f);
    fclose(f);
    
    return data;
}

int main() {
    size_t size;
    
    // Try with a text file
    unsigned char *txt = read_binary("test.txt", &size);
    printf("Text file size: %zu bytes\n", size);
    printf("First 50 bytes: ");
    for (int i = 0; i < 50 && i < size; i++) {
        printf("%c", txt[i]);
    }
    printf("\n\n");
    free(txt);
    
    // Try with an image
    unsigned char *img = read_binary("test.png", &size);
    printf("Image file size: %zu bytes\n", size);
    printf("First 10 bytes (hex): ");
    for (int i = 0; i < 10 && i < size; i++) {
        printf("%02x ", img[i]);
    }
    printf("\n");
    free(img);
    
    return 0;
}
