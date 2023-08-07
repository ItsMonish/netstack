#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <ostream>
#include <sys/socket.h>
#include <string>
#include <netinet/in.h>
#include <sys/types.h>
#include "netstack.hpp"

#define PORT 8585
#define BACKLOG 10

std::string encrypt(std::string plain,int key);
std::string decrypt(std::string cipher,int key);

int main() {
    int serverfd, clientfd;
    struct sockaddr_in client_addr;  
    socklen_t sin_size;
    char clientAddress[INET6_ADDRSTRLEN];
    std::string out_buffer,message;
    char buffer[1024],in_buffer[1024];
    int in_bytes, key;
    int flag = 1;
    
    std::cout<<"[SERVER] > Enter Key for communications:";
    std::cin.getline(buffer,1024);

    key = atoi(buffer);

    serverfd = initStreamServer(PORT,BACKLOG);

    if(serverfd == -1) {
        std::cout<<"[ERROR]: Problems in initializing the server"<<std::endl;
        exit(EXIT_FAILURE);
    }
    if(listen(serverfd,BACKLOG) == -1) {
        std::cout<<"[ERROR]: Cannot listen"<<std::endl;
        exit(EXIT_FAILURE);
    }

    while(flag) {
        sin_size = sizeof(struct sockaddr_in);
        std::cout<<"[INFO]: Waiting for connections"<<std::endl;

        clientfd = accept(serverfd,(struct sockaddr *)&client_addr,(socklen_t*)&sin_size);
        if(clientfd == -1) {
            std::cout<<"[ERROR]: Cannot accept connections"<<std::endl;
            exit(EXIT_FAILURE);
        }

        inet_ntop(AF_INET,&(client_addr.sin_addr),clientAddress,sizeof(clientAddress));
        
        std::cout<<"[INFO]: Connection established from "<<clientAddress<<std::endl;
        
        while(true) {
            std::cout<<"[SERVER] > Enter message:";
            std::cin.getline(buffer,1024);

            out_buffer = encrypt(buffer,key);

            if(send(clientfd,out_buffer.c_str(),out_buffer.length(),0) == -1) 
                std::cout<<"[ERROR]: Could not send the message"<<std::endl;
            if((in_bytes = recv(clientfd,in_buffer,1023,0)) != -1) {

                in_buffer[in_bytes] = '\0';
                message = decrypt(in_buffer,key);
                std::cout<<"[CLIENT RAW]:"<<in_buffer<<std::endl;
                std::cout<<"[CLIENT DECRYPTED]: "<<message<<std::endl;
                if(message.compare("EXIT") == 0) {
                    flag = 0;
                    break;
                }
            }
        }
        close(clientfd);
    }
    return EXIT_SUCCESS;
}

std::string encrypt(std::string plain,int key) {
    // Add code here
    return plain;
}

std::string decrypt(std::string cipher,int key) {
    // Add code here
    return cipher;
}

