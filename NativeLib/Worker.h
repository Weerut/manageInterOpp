#pragma once

#include "stdafx.h"

#include <vector>
#include <queue>
#include <list>

#include <time.h>

#include "WorkerTask.h"
#include "CriticalSectionHolder.h"
#include "CriticalSectionLocker.h"


class Worker
{
public:
	// constructor & destructor
	Worker();
	~Worker();

	void Start();
	void Stop();

	double GetWorkingSeconds() const;
	void PrintStatistics();

	void QueueWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount);
	void QueueDemoWorkerTasks();
	void ExecuteWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount);
private:
	// private fields
	std::queue<WorkerTask> m_waitingTasks;
	std::vector<HANDLE> m_workerThreadsHandles;
	std::list<WorkerTask> m_executedTasks;
	CriticalSectionHolder m_criticalSection;
	
	clock_t m_startClocks;
	clock_t m_stopClocks;
	
	bool m_isWorking;

	// private methods
	void QueueWorkerTask(const WorkerTask& task);
	WorkerTask GetQueuedWorkerTask();
	void AddExecutedTask(const WorkerTask& task);

	static unsigned int __stdcall WorkerThreadProc(void* pParam);
};

