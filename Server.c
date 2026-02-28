#include "Server.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <winsock2.h>
#include<ws2tcpip.h>

struct Server server_constructor(int domain,
    int service,int protocol, 
    u_long net_interface,int port,int backlog,
    void(*launch)(struct Server *server)){

        struct Server s;

        s.domain = domain;
        s.service = service;
        s.protocol = protocol;
        s.net_interface = net_interface;
        s.port = port;
        s.backlog = backlog;

        /* ensure the address struct is zeroed */
        memset(&s.address, 0, sizeof(s.address));

        s.address.sin_family = (short int)domain;
        s.address.sin_port = htons((u_short)port);
        s.address.sin_addr.s_addr = htonl(net_interface);

        s.socket = socket(domain,service,protocol);
    
        if(s.socket==INVALID_SOCKET){
            fprintf(stderr, "Failed to create socket: %d\n", WSAGetLastError());
            exit(1);
          }

            /* allow quick reuse of the address/port when in TIME_WAIT */
            {
              int opt = 1;
              setsockopt(s.socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
            }

             if(bind(s.socket,(struct sockaddr *)&s.address,sizeof(s.address))==SOCKET_ERROR){
            fprintf(stderr, "Failed to bind socket: %d\n", WSAGetLastError());
            closesocket(s.socket);
            exit(1);
             }


      if(listen(s.socket,s.backlog)==SOCKET_ERROR){
        fprintf(stderr, "Failed to listen: %d\n", WSAGetLastError());
        closesocket(s.socket);
        exit(1);
      } 

      s.launch = launch;

        return s;

    }