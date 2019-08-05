#pragma once

#include <boost/filesystem.hpp>

namespace foldersync
{

class Connection
{
public:
	Connection(
		boost::filesystem::path basePath,
		std::string ip,
		int port,
		bool noConnect);
	
	Connection(
		boost::filesystem::path basePath,
		std::string ip,
		int port);
		
	~Connection();
	
	bool sendFile(const boost::filesystem::path& filePath);
	
	bool sendDeleteFile(const boost::filesystem::path& filePath);
	
	bool sendFolder(const boost::filesystem::path& filePath);
	
	bool sendDeleteFolder(const boost::filesystem::path& filePath);
	
private:
	boost::filesystem::path m_basePath;
	
	int m_socket;
	bool m_connected;
	
	boost::filesystem::path getRelativePath(const boost::filesystem::path& fullPath);
};

} // namespace foldersync