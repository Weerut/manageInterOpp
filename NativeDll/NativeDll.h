#pragma once
#ifdef NATIVEDLL_EXPORTS
#define NATIVEDLL_API __declspec(dllexport)
#else
#define NATIVEDLL_API __declspec(dllimport)
#endif

extern "C" NATIVEDLL_API unsigned int __cdecl CreateWorker();
extern "C" NATIVEDLL_API void __cdecl DeleteWorker(unsigned int workerId);
extern "C" NATIVEDLL_API void __cdecl Start(unsigned int workerId);
extern "C" NATIVEDLL_API void __cdecl Stop(unsigned int workerId);
extern "C" NATIVEDLL_API void __cdecl QueueDemoWorkerTasks(unsigned int workerId);
extern "C" NATIVEDLL_API void __cdecl QueueWorkerTask(unsigned int workerId, unsigned int outerLoopCount, unsigned int innerLoopCount);
extern "C" NATIVEDLL_API void __cdecl ExecuteWorkerTask(unsigned int workerId, unsigned int outerLoopCount, unsigned int innerLoopCount);
extern "C" NATIVEDLL_API void __cdecl PrintStatistics(unsigned int workerId);
extern "C" NATIVEDLL_API double __cdecl GetWorkingSeconds(unsigned int workerId);

