// file copying program.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    
    if (argc < 3) {
	printf("Program usage: %s <input_filename> <output_filename>", argv[0]);
	return 1;
	}
    FILE *f_in = fopen(argv[1], "rb");
    
    if (!f_in) {
	perror("Error opening file.");
	exit(EXIT_FAILURE);
	}
    if (fseek(f_in, 0, SEEK_END) != 0) {
	perror("fseek() failed.");
	fclose(f_in);
	exit(EXIT_FAILURE);
	}
    size_t size = ftell(f_in);
    if (size == -1L) {
	perror("ftell() failed.");
	fclose(f_in);
	exit(EXIT_FAILURE);
	}
    fseek(f_in, 0, SEEK_SET);
    
    unsigned char *content = malloc(size + 1);
    if (!content) {
	perror("malloc() failed.");
	fclose(f_in);
	exit(EXIT_FAILURE);
	}
    
    fread(content, 1, size, f_in);
    FILE *f_out = fopen(argv[2], "wb");
    if (!f_out) {
	perror("Error opening file.");
	exit(EXIT_FAILURE);
	}
    fwrite(content, 1, size, f_out);
    
    free(content);
    fclose(f_in);
    fclose(f_out);
    return 0;
    }
