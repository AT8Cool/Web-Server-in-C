#include "HTTPRequest.h"
#include<stdlib.h>
#include <string.h>

int method_select(char *method){

    if(strcmp(method,"GET")==0){
        return GET;
      }
      else if(strcmp(method,"POST")==0){
        return POST;
      }
      else if(strcmp(method,"PUT")==0){
        return PUT;
      }

       else if(strcmp(method,"HEAD")==0){
        return HEAD;
      }

       else if(strcmp(method,"PATCH")==0){
        return PATCH;
      }

       else if(strcmp(method,"DELETE")==0){
        return DELETE;
      }

       else if(strcmp(method,"CONNECT")==0){
        return CONNECT;
      }

       else if(strcmp(method,"OPTIONS")==0){
        return OPTIONS;
      }

       else if(strcmp(method,"TRACE")==0){
        return TRACE;
      }


}

struct HTTPRequest http_request_constructor(char *request_string){

    struct HTTPRequest request;
    char requested[strlen(request_string)];
    strcpy(requested,request_string);

    for(int i =0; i<= strlen(request_string)-1;i++){
        if(request_string[i] =='\n' && request_string[i+1]=='\n'){
            printf("a\n");
            requested[i+1] = '|';
        }
    }
      char *request_line = strtok(request_string,"\n");
      char *header_fields = strtok(NULL,"|");

      char *body = strtok(NULL,"|");
   
      char *method = strtok(request_line," ");

        char *uri = strtok(NULL," ");
      request.Method = method_select(method);
        request.URI = uri;

    char *HTTPVersion = strtok(NULL," ");
    HTTPVersion = strtok(HTTPVersion,"/");
    HTTPVersion = strtok(NULL,"/");
    request.HTTPVersion = (float)atof(HTTPVersion);
      return request;
};


// POST / HTTP/1.1
// Host: 127.0.0.1:8080
// User-Agent: python-requests/2.32.4
// Accept-Encoding: gzip, deflate
// Accept: */*
// Connection: keep-alive
// Content-Length: 19
// Content-Type: application/x-www-form-urlencoded

// message=HelloServer
// 0 Connection closed.