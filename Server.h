#ifndef SERVER_H
typedef unsigned long u_long;
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
// #pragma comment(lib, "ws2_32.lib") // For MSVC only

struct Server {
    int domain;             //  here AF_INET
    int service;            // here SOCK_STREAM
    int protocol;           // sually 0
    u_long net_interface;       // usually INADDR_ANY
    int port;               // here, 8080
    int backlog;            // max pending connections

    struct sockaddr_in address;
    SOCKET socket;

    void (*launch)(struct Server *server);
};


struct Server server_constructor(int domain,
    int service,
    int protocol, 
    u_long net_interface,
    int port,int backlog,

    void(*launch)(struct Server *server));

#endif