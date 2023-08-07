#ifndef NETSTACK_HPP_INCLUDED
#define NETSTACK_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string>
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

/*
 * @brief Initializes the TCP server with given port and backlog capacity
 * @param port Port address for the server intialization
 * @param backlog (Optional) The backlog capacity given to the server
 * @return File Descriptor for server 
 */
int initStreamServer(int port, int backlog = 10);

/*
 * @brief Initializes a socket to connect to the address and port
 * @param addr Address of the server to make connection
 * @param port Server port to connect
 * @return File Descriptor for the socket
 */
int initStreamConnect(std::string addr,int port);

#endif
