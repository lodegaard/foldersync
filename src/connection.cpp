#include "connection.h"
#include "fileevent.h"
#include "messages.h"

#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

#include <iostream>

namespace foldersync
{
Connection::Connection(
		boost::filesystem::path basePath,
		std::string ip,
		int port,
		bool noConnect)
	: m_basePath(basePath)
	, m_socket()
	, m_connected(false)
{
	if (not noConnect)
	{
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_socket < 0)
		{
			std::cout << "Error creating socket" << std::endl;
			return;
		}
		
		struct sockaddr_in server_adress;
		server_adress.sin_family = AF_INET;
        server_adress.sin_port = htons(port);
        
        if (inet_pton(AF_INET, ip.c_str(), &server_adress.sin_addr) <= 0)
        {
        	std::cout << "No such adress: " << ip << std::endl;
        }
        
        if (connect(m_socket, (struct sockaddr *) &server_adress,sizeof(server_adress)) < 0) 
        {
        	std::cout << "Unable to connect to host: " << ip << ":" << port << std::endl;
        	return;
        }
        
        m_connected = true;
	}
}
	
Connection::Connection(
		boost::filesystem::path basePath,
		std::string ip,
		int port)
	: Connection(basePath, ip, port, false)
{
}

Connection::~Connection()
{
	if (m_connected)
	{
		close(m_socket);
	}
}
	
bool Connection::sendFile(const boost::filesystem::path& filePath)
{
	return true;
}

bool Connection::sendDeleteFile(const boost::filesystem::path& filePath)
{
	return true;
}
	
bool Connection::sendFolder(const boost::filesystem::path& filePath)
{
	Control msg;
	msg.type = htonl(static_cast<unsigned int>(MESSAGE_TYPE::CONTROL));
//	msg.event = EVENT_TYPE::CREATED;
//	msg.dest = DESTINATION_TYPE::FOLDER;
//	msg.size = getRelativePath(filePath).string().size() + 3*sizeof(int);
//	strcpy(msg.path, getRelativePath(filePath).string().c_str());
	
	send(m_socket, &msg.type, sizeof(int), 0);
	return true;
}

bool Connection::sendDeleteFolder(const boost::filesystem::path& filePath)
{
	return true;
}

boost::filesystem::path Connection::getRelativePath(const boost::filesystem::path& fullPath)
{
	return boost::filesystem::relative(m_basePath, fullPath);
}

} // namespace foldersync