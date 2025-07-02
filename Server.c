#include "Server.h"
#include <stdio.h>
#include<stdlib.h>
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

        s.address.sin_family = domain;

        s.address.sin_port = htons(port);
        s.address.sin_addr.s_addr = htonl(net_interface);

        s.socket = socket(domain,service,protocol);
    
        if(s.socket==INVALID_SOCKET){
            perror("Failed to connect socket ...\n");
            exit(1);
        }

       if(( bind(s.socket,(struct sockaddr *)&s.address,sizeof(s.address)))<0){
        perror("Failed to bind socket ...\n");
        exit(1);
       }


      if((listen(s.socket,s.backlog))<0){
        perror("Failed to listening...\n");
        exit(1);
      } 

      s.launch = launch;

        return s;

    };