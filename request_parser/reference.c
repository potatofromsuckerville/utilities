#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char key[64];
    char value[256];
} Header;

typedef struct {
    char method[16];
    char path[256];
    char version[16];
    Header headers[32];
    int header_count;
    char *body;
} HttpRequest;

HttpRequest* parse_http_request(char *raw_request) {
    HttpRequest *req = calloc(1, sizeof(HttpRequest));
    
    // Make a copy because strtok modifies the string
    char *request_copy = strdup(raw_request);
    
    // Parse first line
    char *line = strtok(request_copy, "\r\n");
    sscanf(line, "%s %s %s", req->method, req->path, req->version);
    
    printf("=== Request Line ===\n");
    printf("Method: %s\n", req->method);
    printf("Path: %s\n", req->path);
    printf("Version: %s\n\n", req->version);
    
    // Parse headers
    printf("=== Headers ===\n");
    while ((line = strtok(NULL, "\r\n")) != NULL) {
        // Empty line marks end of headers
        if (strlen(line) == 0) {
            break;
        }
        
        // Find the colon separator
        char *colon = strchr(line, ':');
        if (colon) {
            // Split into key and value
            *colon = '\0';  // Replace ':' with null terminator
            char *key = line;
            char *value = colon + 1;
            
            // Skip leading space in value
            while (*value == ' ') value++;
            
            // Store in struct
            strcpy(req->headers[req->header_count].key, key);
            strcpy(req->headers[req->header_count].value, value);
            
            printf("%s: %s\n", 
                   req->headers[req->header_count].key,
                   req->headers[req->header_count].value);
            
            req->header_count++;
        }
    }
    
    // Body comes after blank line
    // Find "\r\n\r\n" in original request
    char *body_start = strstr(raw_request, "\r\n\r\n");
    if (body_start) {
        req->body = body_start + 4;  // Skip the "\r\n\r\n"
        printf("\n=== Body ===\n%s\n", req->body);
    }
    
    free(request_copy);
    return req;
}

// Helper function to get a specific header value
const char* get_header(HttpRequest *req, const char *key) {
    for (int i = 0; i < req->header_count; i++) {
        if (strcmp(req->headers[i].key, key) == 0) {
            return req->headers[i].value;
        }
    }
    return NULL;
}

int main() {
    char *request = 
        "POST /api/users HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 27\r\n"
        "\r\n"
        "{\"name\":\"John\",\"age\":30}";
    
    HttpRequest *req = parse_http_request(request);
    
    // Use the parsed data
    printf("\n=== Using Parsed Data ===\n");
    const char *host = get_header(req, "Host");
    const char *content_type = get_header(req, "Content-Type");
    const char *content_length = get_header(req, "Content-Length");
    
    if (host) printf("Host header: %s\n", host);
    if (content_type) printf("Content-Type: %s\n", content_type);
    if (content_length) printf("Body is %s bytes\n", content_length);
    
    free(req);
    return 0;
}
