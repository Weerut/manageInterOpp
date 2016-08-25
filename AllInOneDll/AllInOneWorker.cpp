#include "AllInOneWorker.h"

namespace AllInOneDll
{

	AllInOneWorker::AllInOneWorker(void)
	{
		m_actualWorker = new Worker;
	}

	AllInOneWorker::~AllInOneWorker()
	{
		if (nullptr != m_actualWorker)
		{
			delete m_actualWorker;
			m_actualWorker = nullptr;
		}
	}

	AllInOneWorker::!AllInOneWorker()
	{
		if (nullptr != m_actualWorker)
		{
			delete m_actualWorker;
			m_actualWorker = nullptr;
		}
	}

	void AllInOneWorker::Start()
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->Start();
		}
	}

	void AllInOneWorker::Stop()
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->Stop();
		}
	}

	void AllInOneWorker::QueueDemoWorkerTasks()
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->QueueDemoWorkerTasks();
		}
	}

	void AllInOneWorker::QueueWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount)
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->QueueWorkerTask(outerLoopCount, innerLoopCount);
		}
	}

	void AllInOneWorker::ExecuteWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount)
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->ExecuteWorkerTask(outerLoopCount, innerLoopCount);
		}
	}

	void AllInOneWorker::PrintStatistics()
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->PrintStatistics();
		}
	}

	double AllInOneWorker::GetWorkingSeconds()
	{
		if (nullptr != m_actualWorker)
		{
			return m_actualWorker->GetWorkingSeconds();
		}
	}

}