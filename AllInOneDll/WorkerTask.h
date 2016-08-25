#pragma once

#include <string>

class WorkerTask
{
public:
	WorkerTask(int outerLoopCount, int innerLoopCount, bool isEndingTask = false);
	WorkerTask(const WorkerTask& src);
	~WorkerTask();

	void Execute();

	bool IsEndingTask() const { return m_isEndingTask; }
	double GetExecutionSeconds() const { return m_executionSeconds; }

	WorkerTask& operator=(const WorkerTask& src);

	std::string GetTaskDescription() const;

private:
	unsigned int m_outerLoopCount;
	unsigned int m_innerLoopCount;
	bool m_isEndingTask;
	double m_executionSeconds;
};

