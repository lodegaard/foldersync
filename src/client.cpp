#include "client.h"

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

namespace foldersync
{

Client::Client(
	boost::filesystem::path watchPath,
	std::string ip, 
	int port)
	: m_fileHandler(watchPath, ip, port, true)
	, m_fileWatcher(watchPath, std::bind(&FileHandler::pushEvent, &m_fileHandler, std::placeholders::_1))
{
}

Client::~Client()
{

}
	
void Client::run()
{
	m_fileWatcher.start();
	std::cout << "Client::run" << std::endl;
	while (true)
	{
		if (m_fileHandler.hasChanges())
		{
			m_fileHandler.handleChanges();
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
	
void Client::startUpClient()
{

}


} // namespace foldersync