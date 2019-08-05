
add_executable(FileWatcherTest testFileWatcher.cpp ../filewatcher.cpp)

target_link_libraries(
	FileWatcherTest PUBLIC
		gtest_main
		Boost::filesystem
		${CMAKE_THREAD_LIBS_INIT})

add_test(
	NAME FileWatcherTest
	COMMAND FileWatcherTest
)


add_executable(FileHandlerTest testFileHandler.cpp ../filehandler.cpp ../connection.cpp ../fileevent.cpp)

target_link_libraries(
	FileHandlerTest PUBLIC
		gtest_main
		Boost::filesystem
		${CMAKE_THREAD_LIBS_INIT})

add_test(
	NAME FileHandlerTest
	COMMAND FileHandlerTest
)

add_executable(ConnectionTest testConnection.cpp ../connection.cpp)

target_link_libraries(
	ConnectionTest PUBLIC
		gtest_main
		Boost::filesystem
		${CMAKE_THREAD_LIBS_INIT})

add_test(
	NAME ConnectionTest
	COMMAND ConnectionTest
)