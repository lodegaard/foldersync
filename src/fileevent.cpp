#include "fileevent.h"

#include <sstream>

namespace foldersync
{


std::string to_string(const EVENT_TYPE& type)
{
	switch (type)
	{
	case EVENT_TYPE::CREATED: return std::string("CREATED");
	case EVENT_TYPE::UPDATED: return std::string("UPDATED");
	case EVENT_TYPE::DELETED: return std::string("DELETED");
	}
	return std::string("");
}

std::string to_string(const FileEvent& event)
{
	std::stringstream ss;
	ss << to_string(event.type) << " ";
	if (event.isDir)
	{
		ss << std::string("directory");
	}
	else
	{
		ss << std::string("file");
	}
	ss << " "
		<< event.path.string();
	return  ss.str();
}

} // namespace foldersync
