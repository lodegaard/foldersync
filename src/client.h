#pragma once

#include "filehandler.h"
#include "filewatcher.h"

#include <boost/filesystem.hpp>
#include <memory>

namespace foldersync
{
class Client
{
public:
	Client(
		boost::filesystem::path watchPath, 
		std::string ip, 
		int port);
	
	~Client();
	
	void run();
	
private:
	FileHandler m_fileHandler;
	FileWatcher m_fileWatcher;

	void startUpClient();

};


} // namespace foldersync