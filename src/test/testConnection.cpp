#include <gtest/gtest.h>

#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

#include <iostream>

void runServer()
{
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	int sockOpts = 1;
	if (server_socket == 0)
	{
		std::cout << "Error creating server socket" << std::endl;
		exit(-1);
	}
	
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &sockOpts, sizeof(sockOpts)))
	{
		std::cout << "Error setting server socket options" << std::endl;
		exit(-1);
	}
	
}