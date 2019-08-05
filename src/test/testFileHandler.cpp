#include <gtest/gtest.h>

#include "../fileevent.h"
#include "../filehandler.h"

#include <boost/filesystem.hpp>
#include <functional>
#include <iostream>

using namespace foldersync;


TEST(FileHandler, CreateFile)
{
	FileHandler fh(boost::filesystem::current_path(), "0.0.0.0", 8080, false);
	FileEvent event{EVENT_TYPE::CREATED, false, boost::filesystem::current_path()};
	
	fh.pushEvent(event);
	
	EXPECT_TRUE(fh.hasChanges());
	fh.handleChanges();
	EXPECT_FALSE(fh.hasChanges());
}

TEST(FileHandler, UpdateFile)
{
	FileHandler fh(boost::filesystem::current_path(), "0.0.0.0", 8080, false);
	FileEvent event{EVENT_TYPE::UPDATED, false, boost::filesystem::current_path()};
	
	fh.pushEvent(event);
	
	EXPECT_TRUE(fh.hasChanges());
	fh.handleChanges();
	EXPECT_FALSE(fh.hasChanges());
}

TEST(FileHandler, DeleteFile)
{
	FileHandler fh(boost::filesystem::current_path(), "0.0.0.0", 8080, false);
	FileEvent event{EVENT_TYPE::DELETED, false, boost::filesystem::current_path()};
	
	fh.pushEvent(event);
	
	EXPECT_TRUE(fh.hasChanges());
	fh.handleChanges();
	EXPECT_FALSE(fh.hasChanges());
}

TEST(FileHandler, CreateFolder)
{
	FileHandler fh(boost::filesystem::current_path(), "0.0.0.0", 8080, false);
	FileEvent event{EVENT_TYPE::CREATED, true, boost::filesystem::current_path()};
	
	fh.pushEvent(event);
	
	EXPECT_TRUE(fh.hasChanges());
	fh.handleChanges();
	EXPECT_FALSE(fh.hasChanges());
}

TEST(FileHandler, UpdateFolder)
{
	FileHandler fh(boost::filesystem::current_path(), "0.0.0.0", 8080, false);
	FileEvent event{EVENT_TYPE::UPDATED, true, boost::filesystem::current_path()};
	
	fh.pushEvent(event);
	
	EXPECT_TRUE(fh.hasChanges());
	fh.handleChanges();
	EXPECT_FALSE(fh.hasChanges());
}

TEST(FileHandler, DeleteFolder)
{
	FileHandler fh(boost::filesystem::current_path(), "0.0.0.0", 8080, false);
	FileEvent event{EVENT_TYPE::DELETED, true, boost::filesystem::current_path()};
	
	fh.pushEvent(event);
	
	EXPECT_TRUE(fh.hasChanges());
	fh.handleChanges();
	EXPECT_FALSE(fh.hasChanges());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}