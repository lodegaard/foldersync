#pragma once

#include "connection.h"
#include "fileevent.h"

#include <mutex>
#include <queue>

namespace foldersync
{

class FileHandler
{
public:
	FileHandler(
		boost::filesystem::path basePath,
		std::string ip,
		int port,
		bool noConnect);
		
	FileHandler(
		boost::filesystem::path basePath,
		std::string ip,
		int port);
	
	bool hasChanges() const;
	
	void handleChanges();
	
	void pushEvent(const FileEvent& event);
	
	
private:
	struct SafeEventQueue
	{
		std::queue<FileEvent> events;
		std::mutex queue_mutex;
	};
	
	mutable SafeEventQueue m_queuedEvents;
	Connection m_connection;
	
	bool transfer(const FileEvent& event);
	
};

} // namespace foldersync