#include "filewatcher.h"

#include <errno.h>
#include <limits.h>
#include <sys/inotify.h>
#include <sys/types.h>

#include <chrono>
#include <iostream>

namespace foldersync
{

static constexpr int MAX_LEN = 1024; /*Path length for a directory*/
static constexpr int MAX_EVENTS = 1024; /*Max. number of events to process at one go*/
static constexpr int LEN_NAME = 16; /*Assuming that the length of the filename won't exceed 16 bytes*/
static constexpr int EVENT_SIZE = ( sizeof (struct inotify_event) ); /*size of one event*/
static constexpr int BUF_LEN = ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )); /*buffer to store the data of events*/

FileWatcher::FileWatcher(
	const boost::filesystem::path& watchPath,
	FileUpdateCb callback)
	: m_threadHandler()
	, m_threadDone(true)
	, m_watchPath(watchPath)
	, m_fileUpdateCb(callback)
	, m_inotifyHandler()
	, m_inotifyFolderWatcher()
	, m_watchedFolders()
{
	setupInotify();
}
	
FileWatcher::~FileWatcher()
{
	stop();
	inotify_rm_watch(m_inotifyHandler, m_inotifyFolderWatcher);
	close(m_inotifyHandler);
}

bool FileWatcher::start()
{
	m_threadDone = false;
	m_threadHandler = std::thread(&FileWatcher::run, this);
	return true;
}

bool FileWatcher::stop()
{
	m_threadDone = true;
	if (m_threadHandler.joinable())
	{
		m_threadHandler.join();
		return true;
	}
	return false;
	
	
}
	
void FileWatcher::run()
{
	char buffer[BUF_LEN];
	while(not m_threadDone)
	{
		int length = read(m_inotifyHandler, buffer, BUF_LEN);
		if (length < 0)
		{
			std::cout << "Error reading notification" << std::endl;
		}
		else
		{
			parseEvents(length, buffer);
		}
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void FileWatcher::parseEvents(const int length, char* buffer)
{
	int eventCount = 0;
	while (eventCount < length)
	{
		struct inotify_event *event = ( struct inotify_event * ) &buffer[eventCount];
		
		if (event->len > 0)
		{
			boost::filesystem::path path = lookupWachDescriptorPath(event->wd);
			std::string fileName(event->name);
			path /= fileName;
			
			FileEvent fileEvent;
			EVENT_TYPE type;
			if ( event->mask & IN_CREATE)
			{
            	if (event->mask & IN_ISDIR)
            	{
            		onUpdate(FileEvent{EVENT_TYPE::CREATED, true, path});
            		std::cout << "Created directory " << event->name << std::endl;
            	}
            	else
            	{
            		onUpdate(FileEvent{EVENT_TYPE::CREATED, false, path});
            		std::cout << "Created file " << event->name << std::endl;
            	}
          	}
           
          	if ( event->mask & IN_MODIFY)
          	{
            	if (event->mask & IN_ISDIR)
            	{
            		onUpdate(FileEvent{EVENT_TYPE::UPDATED, true, path});
            		std::cout << "Modified directory " << event->name << std::endl;
            	}
            	else
            	{
            		onUpdate(FileEvent{EVENT_TYPE::UPDATED, false, path});
              		std::cout << "Modified file " << event->name << std::endl;
              	}
          	}
           
          	if ( event->mask & IN_DELETE)
          	{
            	if (event->mask & IN_ISDIR)
            	{
            		onUpdate(FileEvent{EVENT_TYPE::DELETED, true, path});
            		std::cout << "Deleted directory " << event->name << std::endl;    
            	}
            	else
            	{
            		onUpdate(FileEvent{EVENT_TYPE::DELETED, false, path});
              		std::cout << "Deleted file " << event->name << std::endl;  
              	}
          	}  
		}
		
		
		eventCount += EVENT_SIZE + event->len;
	}
}

void FileWatcher::onUpdate(const FileEvent& event)
{
	m_fileUpdateCb(event);
}

void FileWatcher::setupInotify()
{
	m_inotifyHandler = inotify_init();
	if (m_inotifyHandler < 0)
	{
		std::cout << "Could not initialize inotify" << std::endl;
	}
	else
	{
		int wd = inotify_add_watch(
				m_inotifyHandler,
				boost::filesystem::canonical(m_watchPath).string().c_str(), 
				IN_CREATE | IN_MODIFY | IN_DELETE); 
				
		if (wd == -1)
		{
			std::cout << "Unable to watch folder : " << boost::filesystem::canonical(m_watchPath).string() << std::endl;
		}
		else
		{
			m_watchedFolders.insert(std::pair<int, boost::filesystem::path>(wd, m_watchPath));
			std::cout << "Watching folder : " << boost::filesystem::canonical(m_watchPath).string() << std::endl;
		}
	}
}

boost::filesystem::path FileWatcher::lookupWachDescriptorPath(const int wd)
{
	if (m_watchedFolders.count(wd) > 0)
	{
		return m_watchedFolders.at(wd);	
	}
	
	return boost::filesystem::path();
}

} // namespace foldersync