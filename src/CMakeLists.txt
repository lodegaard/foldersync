find_package(Threads)

add_executable(Client main.cpp client.cpp filewatcher.cpp fileevent.cpp filehandler.cpp connection.cpp)

target_link_libraries(
	Client
		PUBLIC
			Boost::filesystem
			Boost::serialization
			${CMAKE_THREAD_LIBS_INIT}
)

add_subdirectory(test)