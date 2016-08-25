// NativeDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NativeDll.h"
#include "..\NativeLib\Worker.h"

#include <map>

using namespace std;

map<unsigned int, Worker*> g_theWorkers;
// Note: In a real DLL, we should lock the creation of the workers,
//       the deletion of the workers and, the workers' methods calls,
//       in order to prevent some multi-threaded issues (e.g.
//       creating 2 workers but holding only one - since the same id 
//       is assigned to the both of the workers by different threads, 
//       using a worker that has been deleted by another thread, etc...).
//       We can simply achieve that goal, by using a CriticalSectionHolder 
//       global variable for holding a critical-section and, using a
//       CriticalSectionLocker variable for locking the critical-section
//       for each function.
//       But, in order to enable testing the third way (execute worker
//       tasks synchronously) by calling it parallelly (using .NET TPL)
//       we don't use a critical-section here (Since, if the function
//       will be locked by a critical-section, the tasks won't run
//       parallelly...).

NATIVEDLL_API unsigned int __cdecl CreateWorker()
{
	static unsigned int s_nextWorkerId = 1;

	unsigned int currWorkerId = s_nextWorkerId;
	g_theWorkers[currWorkerId] = new Worker();

	s_nextWorkerId++;

	return currWorkerId;
}

NATIVEDLL_API void __cdecl DeleteWorker(unsigned int workerId)
{
	auto workerItr = g_theWorkers.find(workerId);
	if (workerItr != g_theWorkers.end())
	{
		delete workerItr->second;
		g_theWorkers.erase(workerItr);
	}
}

NATIVEDLL_API void __cdecl Start(unsigned int workerId)
{
	auto workerItr = g_theWorkers.find(workerId);
	if (workerItr != g_theWorkers.end())
	{
		workerItr->second->Start();
	}
}

NATIVEDLL_API void __cdecl Stop(unsigned int workerId)
{
	auto workerItr = g_theWorkers.find(workerId);
	if (workerItr != g_theWorkers.end())
	{
		workerItr->second->Stop();
	}
}

NATIVEDLL_API void __cdecl QueueDemoWorkerTasks(unsigned int workerId)
{
	auto workerItr = g_theWorkers.find(workerId);
	if (workerItr != g_theWorkers.end())
	{
		workerItr->second->QueueDemoWorkerTasks();
	}
}

NATIVEDLL_API void __cdecl QueueWorkerTask(unsigned int workerId, unsigned int outerLoopCount, unsigned int innerLoopCount)
{
	auto workerItr = g_theWorkers.find(workerId);
	if (workerItr != g_theWorkers.end())
	{
		workerItr->second->QueueWorkerTask(outerLoopCount, innerLoopCount);
	}
}

NATIVEDLL_API void __cdecl ExecuteWorkerTask(unsigned int workerId, unsigned int outerLoopCount, unsigned int innerLoopCount)
{
	auto workerItr = g_theWorkers.find(workerId);
	if (workerItr != g_theWorkers.end())
	{
		workerItr->second->ExecuteWorkerTask(outerLoopCount, innerLoopCount);
	}
}

NATIVEDLL_API void __cdecl PrintStatistics(unsigned int workerId)
{
	auto workerItr = g_theWorkers.find(workerId);
	if (workerItr != g_theWorkers.end())
	{
		workerItr->second->PrintStatistics();
	}
}

NATIVEDLL_API double __cdecl GetWorkingSeconds(unsigned int workerId)
{
	auto workerItr = g_theWorkers.find(workerId);
	if (workerItr != g_theWorkers.end())
	{
		return workerItr->second->GetWorkingSeconds();
	}
}

