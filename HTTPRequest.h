
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "DataStructures/Lists/Queue.h"
#include "DataStructures/Dictionary/Dictionary.h"
// enum HTTPMethod{
//     GET,
//     POST,
//     PUT,
//     HEAD,
//     PATCH,
//     DELETE,
//     CONNECT,
//     OPTIONS,
//     TRACE
// };

struct HTTPRequest{
    // int Method;
    // char *URI;
    // float HTTPVersion;
    // struct Dictionary header_field;

    struct Dictionary request_line;
    struct Dictionary header_fields;
    struct Dictionary body;

};

struct HTTPRequest http_request_constructor(char *request_string);
void http_request_destructor(struct HTTPRequest *request);

#endif