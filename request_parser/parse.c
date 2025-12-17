#include <stdio.h>
#include <string.h>

#define GET 0
#define POST 1
#define PUT 2

#include <stdio.h>
#include <string.h>

#define GET 0
#define POST 1
#define PUT 2

void parse_path(char *path, int index) {
    char *ext; 
    
    const char *http_method[] = {"GET", "POST", "PUT"};
    
    if ((ext = strrchr(path, '.')) != NULL) {
        printf("Extension of the file in path %s: %s\n", path, ext);
        if (!strcmp(ext, ".jpg") || !strcmp(ext, ".png")) {
            printf("The file is an image file. Method: %s. \n", http_method[index]);
            }
        else if (!strcmp(ext, ".html")){
            printf("The file is an html file. \n");
            }
        else if (!strcmp(ext, ".css")) {
            printf("The file is a css file. \n");
            }
        return;
        }
    if ((ext = strrchr(path, '?')) != NULL) {
        printf("Method: %s \nParameter: %s\n", http_method[index], ext);
        }
    return;
    }
int parse_method(const char *method_buffer) {    
    if (strcmp(method_buffer,"PUT") == 0) return PUT;
    if (strcmp(method_buffer,"GET") == 0) return GET;
    if (strcmp(method_buffer,"POST") == 0) return POST;
        
    printf("Unrecognised method. \n");
    return -1;
    }
    
int main() {
    
    char *request = "POST api/users?id=123 HTTP/1.1";
    // POST api/users?id=123 HTTP/1.1
    char method[16];
    char path[32];
    char version[16];
    
    sscanf(request, "%s %s %s", method, path, version);
    int index = parse_method(method);
    parse_path(path, index);
    
    return 0;
    }


