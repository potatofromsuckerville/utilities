#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char key[64];
    char value[256];
    } Header;

typedef struct {
    char method[16];
    char path[32];
    char version[16];
    Header headers[32];
    int header_count;
    char *body;
    } HttpRequest;

HttpRequest* parse_request(char *request) {
    HttpRequest *req = calloc(1, sizeof(HttpRequest));
    if (!req) {
	perror("calloc() failed.");
	exit(EXIT_FAILURE);
	}
    
    char *body = strstr(request, "\r\n\r\n");
    req->body = body + 4;
    int header_portion = body - request;
    
    char *header_copy = malloc(header_portion + 1);
    if (!header_copy) {
	perror("malloc() failed.");
	free(req);
	exit(EXIT_FAILURE);
	}
	
    strncpy(header_copy, request, header_portion);
    header_copy[header_portion] = '\0';
    
    char *line = strtok(header_copy, "\r\n"); 
    sscanf(line, "%15s %31s %15s", req->method, req->path, req->version);
    
    printf("==== Request Line ====\n");
    printf("Method: %s \n", req->method);
    printf("Path: %s \n", req->path);
    printf("Version: %s \n", req->version);
    printf("\n");
    
    printf("==== Headers ====\n");
    while ((line = strtok(NULL, "\r\n")) != NULL) {
	printf("%s \n", line);
	char *colon = strchr(line, ':');
	if (colon) {
	    *colon = '\0';
	    char *key = line;
	    char *value = colon + 1;
	    
	    while (*value == ' ') value++;
	    
	    snprintf(req->headers[req->header_count].key, 
		     sizeof(req->headers[req->header_count].key),
		     "%s", key);
		     
	    snprintf(req->headers[req->header_count].value, 
		     sizeof(req->headers[req->header_count].value),
		     "%s", value);
		     
	    req->header_count++;
	    }
	}
    printf("\n");
    
    printf("==== Body ====\n");
    printf("%s \n", req->body);
    
    free(header_copy);
    return req;
    }

const char* get_header(HttpRequest *req, const char *key) {
    for (int i = 0; i < req->header_count; i++){
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
        "Content-Type: application/json\r\n"
        "Content-Length: 27\r\n"
        "\r\n"
	"{\"name\":\"John\",\"age\":30}";
	
    HttpRequest *req = parse_request(request);
    
    const char *content_type = get_header(req, "Content-Type");
    printf("%s \n", content_type);
    free(req);
    return 0;
    }
