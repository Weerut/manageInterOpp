#pragma once

#include "Worker.h"

namespace AllInOneDll
{

	public ref class AllInOneWorker
	{
	public:
		AllInOneWorker(void);

		~AllInOneWorker(); // Dispose()
		!AllInOneWorker(); // Finalize()

		void Start();
		void Stop();
		void QueueDemoWorkerTasks();
		void QueueWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount);
		void ExecuteWorkerTask(unsigned int outerLoopCount, unsigned int innerLoopCount);
		void PrintStatistics();
		double GetWorkingSeconds();

	private:
		Worker* m_actualWorker;
	};

}