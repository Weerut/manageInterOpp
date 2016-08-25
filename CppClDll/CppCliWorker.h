#pragma once

#include "..\NativeLib\Worker.h"

namespace CppCliDll
{
	public ref class CppCliWorker
	{
	public:
		CppCliWorker();
		~CppCliWorker(); // Dispose()
		!CppCliWorker(); // Finalize()

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
