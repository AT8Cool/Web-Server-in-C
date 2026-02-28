#include<stdio.h>
#include <string.h>
#include "Server.h"
#include <ws2tcpip.h>
#include<winsock2.h>

#pragma comment(lib, "ws2_32.lib") // for MSVC, optional for MinGW

void launch(struct Server *server) {
    char buffer[30000];

    printf("====== WAITING FOR CONNECTION ======\n");


    int count = 0;
    while (1) {
         int address_length = sizeof(server->address);
         SOCKET new_socket = accept(server->socket, (struct sockaddr*)&(server->address), &address_length);
       
           if (new_socket == INVALID_SOCKET) {
            printf(" Accept failed with error code: %d\n", WSAGetLastError());
            continue; // Try next connection instead of exiting
        }
         printf("Connection established with client.\n");

        int bytes_received = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0'; // Null-terminate
            printf(" Received:\n%s\n", buffer);

            const char *hello =
                "HTTP/1.1 200 OK\r\n"
                "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
                "Server: AtharvaServer/1.0\r\n"
                "Content-Length: 46\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n"
                "\r\n"
                "<html><body><h1>Hello, Atharva</h1></body></html>";

            send(new_socket, hello, (int)strlen(hello), 0);
        } else {
            printf("  recv failed or connection closed by client.\n");
        }
        
        closesocket(new_socket);
        printf("%d Connection closed.\n\n",count);
        count = count +1;
    }
}


int main(){

     WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }
  

    struct Server server = server_constructor(AF_INET,
        SOCK_STREAM,0,INADDR_ANY,8080,10,launch);

    server.launch(&server);
    WSACleanup();
    return 0;
}