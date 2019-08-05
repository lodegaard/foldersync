#pragma once

#include <memory>
#include <thread>

class ThreadWrapper
{
public:
	ThreadWrapper();
	
	virtual void run() = 0;
	
	bool start()
	{
		m_done = false;
		
		m_thread = make_unique()
	}
	
	bool stop();

private:
	std::unique_ptr<std::thread> m_thread;
	bool m_done;
	
	void runThread()
	{
		while (!m_done)
		{
			run();
		}
	}
}