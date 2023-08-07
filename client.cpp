#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include "netstack.hpp"

#define PORT 8585

std::string encrypt(std::string plain,int key);
std::string decrypt(std::string cipher,int key);

int main(int argc, char* argv[]) {
    int clientfd,in_bytes,key;
    char buffer[1024],in_buffer[1024];
    std::string out_buffer,message;

    std::cout<<"[CLIENT] > Enter Key for Communications:";
    std::cin.getline(buffer,1024);

    key = atoi(buffer);

    if(argc < 2) {
        clientfd = initStreamConnect("127.0.0.1",PORT);
    } else {
        clientfd = initStreamConnect(argv[1],PORT);
    }
    
    if(clientfd == -1) {
        std::cout<<"[ERROR]: Could not establish connection"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    while(true) {
        if((in_bytes = recv(clientfd,in_buffer,1023,0)) != -1) {
            in_buffer[in_bytes] = '\0';
            message = decrypt(in_buffer,key);

            std::cout<<"[SERVER RAW]:"<<in_buffer<<std::endl;
            std::cout<<"[SERVER DECRYPTED]: "<<message<<std::endl;
        }

        std::cout<<"[CLIENT] > Enter Message:";
        std::cin.getline(buffer,1024);

        out_buffer = encrypt(buffer,key);
        
        if(send(clientfd,out_buffer.c_str(),out_buffer.length(),0) != -1) 
            if(strcmp(buffer,"EXIT") == 0) break;
    }

    close(clientfd);
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



