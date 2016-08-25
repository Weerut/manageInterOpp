#pragma once

class CriticalSectionHolder
{
public:
	CriticalSectionHolder(void);
	virtual ~CriticalSectionHolder(void);

	LPCRITICAL_SECTION GetCriticalSection() { return &m_criticalSection; }

private:
	CRITICAL_SECTION m_criticalSection;
};

