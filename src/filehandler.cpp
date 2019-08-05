#include "filehandler.h"
#include "fileevent.h"

#include <iostream>

namespace foldersync
{

FileHandler::FileHandler(
		boost::filesystem::path basePath,
		std::string ip,
		int port,
		bool noConnect)
	: m_queuedEvents(FileHandler::SafeEventQueue{std::queue<FileEvent>(), std::mutex()})
	, m_connection(basePath, ip, port, noConnect)
{

}

FileHandler::FileHandler(
		boost::filesystem::path basePath,
		std::string ip,
		int port)
	: FileHandler(basePath, ip, port, false)
{

}

bool FileHandler::hasChanges() const
{
	std::lock_guard<std::mutex> lock(m_queuedEvents.queue_mutex);
	std::cout << m_queuedEvents.events.size() << " unhandled events" << std::endl;
	return not m_queuedEvents.events.empty();
}

void FileHandler::handleChanges()
{
	while (hasChanges())
	{
		FileEvent frontCopy;
		{
			std::lock_guard<std::mutex> lock(m_queuedEvents.queue_mutex);
			frontCopy = m_queuedEvents.events.front();
		}
		if (transfer(frontCopy))
		{
			std::lock_guard<std::mutex> lock(m_queuedEvents.queue_mutex);
			m_queuedEvents.events.pop();
		}
	}
}

bool FileHandler::transfer(const FileEvent& event)
{
	if (event.isDir)
	{
		if (event.type == EVENT_TYPE::CREATED or
			event.type == EVENT_TYPE::UPDATED)
		{
			return m_connection.sendFile(event.path);
		}
		else if (event.type == EVENT_TYPE::DELETED)
		{
			return m_connection.sendDeleteFile(event.path);
		}
	}
	else
	{
		if (event.type == EVENT_TYPE::CREATED or
			event.type == EVENT_TYPE::UPDATED)
		{
			return m_connection.sendFolder(event.path);
		}
		else if (event.type == EVENT_TYPE::DELETED)
		{
			return m_connection.sendDeleteFolder(event.path);
		}
	}
	return false;
}

void FileHandler::pushEvent(const FileEvent& event)
{
	std::cout << to_string(event) << std::endl;
	std::lock_guard<std::mutex> lock(m_queuedEvents.queue_mutex);
	m_queuedEvents.events.push(event);
}

} // namespace foldersync