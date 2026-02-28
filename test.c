#include<stdio.h>
#include <string.h>
#include <time.h>
#include "Server.h"
#include "HTTPHandler.h"
#include <ws2tcpip.h>
#include<winsock2.h>

#pragma comment(lib, "ws2_32.lib") // for MSVC, optional for MinGW

void launch(struct Server *server) {
    char buffer[30000];
    printf("====== SERVER RUNNING ON http://localhost:8080 ======\n");
    printf("====== INTERACTIVE DASHBOARD READY ======\n");
    
    if (g_stats.start_time == 0) {
        g_stats.start_time = time(NULL);
    }
    
    int count = 0;
    while (1) {
        int address_length = sizeof(server->address);
        SOCKET new_socket = accept(server->socket, (struct sockaddr*)&(server->address), &address_length);
        
        if (new_socket == INVALID_SOCKET) {
            fprintf(stderr, "Accept failed: %d\n", WSAGetLastError());
            continue;
        }
        
        printf("[%d] Connection established\n", count);
        g_stats.request_count++;
        
        int bytes_received = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            
            // Parse HTTP request
            char method[16] = {0};
            char path[256] = {0};
            char query[512] = {0};
            char *first_line_end = strchr(buffer, '\r');
            if (first_line_end) {
                char first_line[512] = {0};
                strncpy(first_line, buffer, first_line_end - buffer);
                parse_request_line(first_line, method, path, query);
                
                printf("  Method: %s, Path: %s\n", method, path);
                
                // Route requests
                if (strcmp(path, "/") == 0) {
                    handle_dashboard(new_socket);
                }
                else if (strcmp(path, "/api/status") == 0) {
                    handle_api_status(new_socket);
                }
                else if (strcmp(path, "/api/time") == 0) {
                    handle_api_time(new_socket);
                }
                else if (strcmp(path, "/api/stats") == 0) {
                    handle_api_stats(new_socket);
                }
                else if (strcmp(path, "/api/bst-structure") == 0) {
                    handle_api_bst(new_socket);
                }
                else if (strncmp(path, "/api/store", 10) == 0) {
                    handle_api_store(new_socket, query);
                }
                else if (strncmp(path, "/api/retrieve", 13) == 0) {
                    char key[256] = {0};
                    if (strlen(query) > 0) {
                        sscanf(query, "key=%255s", key);
                    }
                    handle_api_retrieve(new_socket, key);
                }
                else {
                    handle_not_found(new_socket);
                }
            } else {
                handle_not_found(new_socket);
            }
        } else {
            printf("  recv failed or connection closed\n");
        }
        
        closesocket(new_socket);
        printf("  [%d] Connection closed\n\n", count);
        count++;
    }
}

int main(){
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }
    
    printf("Initializing C Web Server with Interactive API...\n");
    struct Server server = server_constructor(AF_INET,
        SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);

    server.launch(&server);
    WSACleanup();
    return 0;
}
