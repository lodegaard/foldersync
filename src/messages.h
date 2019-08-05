#pragma once

#include "fileevent.h"

#include <cstdint>

namespace foldersync
{

enum class MESSAGE_TYPE : int 
{
	CONTROL = 0,
	DATA = 1
};

enum class DESTINATION_TYPE : int
{
	FILE = 0,
	FOLDER = 1
};

struct Control
{
	unsigned int type;
	unsigned int event;
	unsigned int dest;
	unsigned int size;
	char* path;
};

struct Data
{
	unsigned int type;
	unsigned int counter;
	char* data;
};

} // namespace foldersync