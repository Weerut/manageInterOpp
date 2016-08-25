#include "CppCliWorker.h"

namespace CppCliDll
{
	CppCliWorker::CppCliWorker()
	{
		m_actualWorker = new Worker;
	}
	CppCliWorker::~CppCliWorker()
	{
		if (nullptr != m_actualWorker)
		{
			delete m_actualWorker;
			m_actualWorker = nullptr;
		}
	}
	CppCliWorker::!CppCliWorker()
	{
		if (nullptr != m_actualWorker)
		{
			delete m_actualWorker;
			m_actualWorker = nullptr;
		}
	}
	void CppCliWorker::Start()
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->Start();
		}
	}

	void CppCliWorker::Stop()
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->Stop();
		}
	}

	void CppCliWorker::QueueDemoWorkerTasks()
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->QueueDemoWorkerTasks();
		}
	}

	void CppCliWorker::QueueWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount)
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->QueueWorkerTask(outerLoopCount, innerLoopCount);
		}
	}

	void CppCliWorker::ExecuteWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount)
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->ExecuteWorkerTask(outerLoopCount, innerLoopCount);
		}
	}

	void CppCliWorker::PrintStatistics()
	{
		if (nullptr != m_actualWorker)
		{
			m_actualWorker->PrintStatistics();
		}
	}

	double CppCliWorker::GetWorkingSeconds()
	{
		if (nullptr != m_actualWorker)
		{
			return m_actualWorker->GetWorkingSeconds();
		}
	}
}
