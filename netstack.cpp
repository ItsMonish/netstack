#include "netstack.hpp"
#include <asm-generic/socket.h>
#include <csignal>
#include <iterator>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


int initStreamServer(int port,int backlog) {
    int serverfd;
    int yes = 1;
    char address[INET6_ADDRSTRLEN];
    char err_buffer[256];
    struct sockaddr_in serverInfo;

    if(( serverfd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
        std::cout<<"[ERROR]: Cannot create socket"<<std::endl;
        return -1;
    }

    if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &yes, sizeof(int))) {
        strerror_r(errno,err_buffer,256);
        std::cout<<"[ERROR]: "<<err_buffer;
        return -1;
    }

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(port);

    if(bind(serverfd,(struct sockaddr*)&serverInfo,sizeof(struct sockaddr_in)) < 0) {
        std::cout<<"[ERROR]: Cannot bind the socket"<<std::endl;
        return -1;
    }

    inet_ntop(AF_INET,&(serverInfo.sin_addr),address,sizeof(address));
    std::cout<<"[INFO]: Server started at "<<address<<std::endl;

    return serverfd;
    
}

int initStreamConnect(std::string addr,int port) {
    int clientfd;
    struct sockaddr_in serverInfo;

    if((clientfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        std::cout<<"[ERROR]: Cannot create socket"<<std::endl;
        return -1;
    }

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);
    
    if(inet_pton(AF_INET,addr.c_str(),&serverInfo.sin_addr) <= 0) {
        std::cout<<"[ERROR]: Invalid IP address for server"<<std::endl;
        return -1;
    }

    if(connect(clientfd,(struct sockaddr*)&serverInfo,sizeof(serverInfo)) == -1) {
        std::cout<<"[ERROR]: Connection to server refused"<<std::endl;
        std::cout<<errno<<" "<<strerror(errno)<<std::endl;
        return -1;
    }

    std::cout<<"[INFO]: Connection to "<<addr<<" established successfully"<<std::endl;

    return clientfd;

}
