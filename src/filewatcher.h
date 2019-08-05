#pragma once

#include "fileevent.h"

#include <boost/filesystem.hpp>
#include <functional>
#include <map>
#include <memory>
#include <thread>

namespace foldersync
{

using FileUpdateCb = std::function<void(const FileEvent&)>;

class FileWatcher
{
public:
	FileWatcher(
		const boost::filesystem::path& watchPath,
		FileUpdateCb callback);
	
	~FileWatcher();
	
	bool start();
	
	bool stop();
	
private:
	std::thread m_threadHandler;
	bool m_threadDone;
	
	FileUpdateCb m_fileUpdateCb;
	boost::filesystem::path m_watchPath;
	int m_inotifyHandler;
	int m_inotifyFolderWatcher;
	
	std::map<int, boost::filesystem::path> m_watchedFolders;
	
	void run();
	
	void parseEvents(const int length, char* buffer);
	
	void onUpdate(const FileEvent& event);
	
	void setupInotify();
	
	boost::filesystem::path lookupWachDescriptorPath(const int wd);
};


} // namespace foldersync
