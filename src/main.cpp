#include <iostream>

#include <boost/filesystem.hpp>

#include "client.h"

namespace fs = boost::filesystem;
using namespace foldersync;

int main(int argc, char* argv[])
{
	fs::path full_path(fs::current_path());
	std::cout << "Current path is : " << full_path << std::endl;
	
	Client client(full_path, "0.0.0.0", 8080);

	client.run();
	
	return 0;
}