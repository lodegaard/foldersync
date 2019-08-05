#include <gtest/gtest.h>

#include "../fileevent.h"
#include "../filewatcher.h"

#include <boost/filesystem.hpp>
#include <functional>
#include <iostream>

using namespace foldersync;

void callBackImpl(const FileEvent& event)
{
	std::cout << "Received callback for " << event.path << std::endl;
}

TEST(FileWatcher, setup)
{
	FileWatcher fw(boost::filesystem::current_path(), std::bind(callBackImpl, std::placeholders::_1));
	
	EXPECT_TRUE(fw.start());
	
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}