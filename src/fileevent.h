#pragma once

#include <boost/filesystem.hpp>
#include <string>

namespace foldersync
{

enum class EVENT_TYPE : int
{
	CREATED = 0,
	UPDATED = 1,
	DELETED = 2
};
	
struct FileEvent
{
	EVENT_TYPE type;
	bool isDir;
	boost::filesystem::path path;
};


std::string to_string(const EVENT_TYPE& type);
std::string to_string(const FileEvent& event);

} // namespace foldersync