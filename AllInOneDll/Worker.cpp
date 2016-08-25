#include "StdAfx.h"
#include "Worker.h"

#include <process.h>
#include <iostream>
#include <algorithm>

#include "CriticalSectionLocker.h"

#define WORKER_THREADS_NUM 4

using namespace std;

Worker::Worker()
	: m_workerThreadsHandles(WORKER_THREADS_NUM, 0), m_isWorking(false)
{
}

Worker::~Worker()
{
	Stop();	
}

void Worker::Start()
{
	if (m_isWorking)
	{
		// The worker has been already started...
		return;
	}

	m_startClocks = clock();

	unsigned int threadID = 0;

	//Start the worker's threads.
	for(int threadInx = 0; threadInx < WORKER_THREADS_NUM; threadInx++)
	{
		m_workerThreadsHandles[threadInx] = (HANDLE)::_beginthreadex(0, 0, WorkerThreadProc, (void*)this, 0, &threadID);
	}

	m_isWorking = true;
}

void Worker::Stop()
{
	if (!m_isWorking)
	{
		// The worker isn't working...
		return;
	}

	// Queue ending tasks.
	for(int endingTaskInx = 0; endingTaskInx < WORKER_THREADS_NUM; endingTaskInx++)
	{
		QueueWorkerTask(WorkerTask(0,0,true));
	}

	//Stop the worker's threads.
	for(int threadInx = 0; threadInx < WORKER_THREADS_NUM; threadInx++)
	{
		HANDLE currHandle = m_workerThreadsHandles[threadInx];

		if (0 == currHandle)
		{
			continue;
		}

		// Let the thread to be ended.
		::WaitForSingleObject(currHandle, INFINITE);

		// Close the thread.
		::CloseHandle(currHandle);
		m_workerThreadsHandles[threadInx] = 0;
	}

	m_stopClocks = clock();

	m_isWorking = false;
}

void Worker::QueueDemoWorkerTasks()
{
	for (unsigned int taskLoopCount = 10000; taskLoopCount < 50000; taskLoopCount += 1000)
	{
		QueueWorkerTask(taskLoopCount, taskLoopCount);
	}
}

void Worker::QueueWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount)
{
	QueueWorkerTask(WorkerTask(outerLoopCount, innerLoopCount));
}

void Worker::ExecuteWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount)
{
	WorkerTask task(outerLoopCount, innerLoopCount);
	task.Execute();

	AddExecutedTask(task);
}

void Worker::QueueWorkerTask(const WorkerTask& task)
{
	CriticalSectionLocker locker(m_criticalSection.GetCriticalSection());

	m_waitingTasks.push(task);
}

WorkerTask Worker::GetQueuedWorkerTask()
{
	bool isTaskFound = false;

	WorkerTask res(0,0);

	while (!isTaskFound)
	{
		CriticalSectionLocker locker(m_criticalSection.GetCriticalSection());

		if (!m_waitingTasks.empty())
		{
			res = m_waitingTasks.front();
			m_waitingTasks.pop();
			isTaskFound = true;
		}
	}

	return res;
}

void Worker::AddExecutedTask(const WorkerTask& task)
{
	CriticalSectionLocker locker(m_criticalSection.GetCriticalSection());

	m_executedTasks.push_back(task);
}

void Worker::PrintStatistics()
{
	CriticalSectionLocker locker(m_criticalSection.GetCriticalSection());

	cout << "Worker working seconds: " << GetWorkingSeconds() << endl;
	cout << "Tasks executions seconds:" << endl;
	for_each(m_executedTasks.begin(), m_executedTasks.end(), [](WorkerTask task) -> void
	{
		cout << "\t" << task.GetTaskDescription() << endl;
	});
}

double Worker::GetWorkingSeconds() const
{
	return (double)((m_isWorking ? clock() : m_stopClocks) - m_startClocks) / CLOCKS_PER_SEC;
}

unsigned int __stdcall Worker::WorkerThreadProc(void* pParam)
{
	Worker* theWorker = reinterpret_cast<Worker*>(pParam);

	while (true)
	{
		WorkerTask task = theWorker->GetQueuedWorkerTask();

		if (task.IsEndingTask())
		{
			break;
		}

		task.Execute();
		theWorker->AddExecutedTask(task);
	}

	return 0;
}