#pragma once

#include "stdafx.h"

#include <vector>
#include <queue>
#include <list>

#include <time.h>

#include "WorkerTask.h"
#include "CriticalSectionHolder.h"

class Worker
{
public:
	Worker();
	virtual ~Worker();

	void Start();
	void Stop();

	void QueueDemoWorkerTasks();
	void QueueWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount);
	void ExecuteWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount);

	void PrintStatistics();

	double GetWorkingSeconds() const;

private:		
	void QueueWorkerTask(const WorkerTask& task);
	WorkerTask GetQueuedWorkerTask();

	void AddExecutedTask(const WorkerTask& task);

	bool m_isWorking;

	clock_t m_startClocks;
	clock_t m_stopClocks;

	CriticalSectionHolder m_criticalSection;
	std::vector<HANDLE> m_workerThreadsHandles;
	std::queue<WorkerTask> m_waitingTasks;
	std::list<WorkerTask> m_executedTasks;

	static unsigned int __stdcall WorkerThreadProc(void* pParam);
};

