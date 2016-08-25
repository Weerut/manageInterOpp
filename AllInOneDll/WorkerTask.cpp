#include "StdAfx.h"
#include "WorkerTask.h"

#include <time.h>
#include <sstream>

using namespace std;

WorkerTask::WorkerTask(int outerLoopCount, int innerLoopCount, bool isEndingTask)
	: m_outerLoopCount(outerLoopCount), m_innerLoopCount(innerLoopCount),
	  m_isEndingTask(isEndingTask), m_executionSeconds(0.0)
{
}

WorkerTask::WorkerTask(const WorkerTask& src)
	: m_outerLoopCount(src.m_outerLoopCount), m_innerLoopCount(src.m_innerLoopCount),
	  m_isEndingTask(src.m_isEndingTask), m_executionSeconds(src.m_executionSeconds)
{
}

WorkerTask::~WorkerTask()
{
}

void WorkerTask::Execute()
{
	clock_t beginClocks = clock();

	// Do some work.

	for (unsigned int outerCount = 0; outerCount < m_outerLoopCount; outerCount++)
	{
		int* pi = new int[m_innerLoopCount];

		for (unsigned int innerCount = 0; innerCount < m_innerLoopCount; innerCount++)
		{
			pi[innerCount] = innerCount * outerCount;			
		}

		delete[] pi;
	}

	clock_t endClocks = clock();

	m_executionSeconds = (double)(endClocks - beginClocks) / CLOCKS_PER_SEC;
}

WorkerTask& WorkerTask::operator=(const WorkerTask& src)
{
	m_outerLoopCount = src.m_outerLoopCount;
	m_innerLoopCount = src.m_innerLoopCount;
	m_isEndingTask = src. m_isEndingTask;
	m_executionSeconds = src.m_executionSeconds;

	return *this;
}

string WorkerTask::GetTaskDescription() const
{
	stringstream ss;
	ss << "(" << m_outerLoopCount << ", " << m_innerLoopCount << ") Execution seconds: " << m_executionSeconds << ".";

	return ss.str();
}
