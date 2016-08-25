#include "StdAfx.h"
#include "CriticalSectionHolder.h"

CriticalSectionHolder::CriticalSectionHolder(void)
{
	::InitializeCriticalSection(&m_criticalSection);
}

CriticalSectionHolder::~CriticalSectionHolder(void)
{
	::DeleteCriticalSection(&m_criticalSection);
}
