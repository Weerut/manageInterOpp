#include "StdAfx.h"
#include "CriticalSectionLocker.h"

CriticalSectionLocker::CriticalSectionLocker(LPCRITICAL_SECTION pCriticalSection)
	: m_pCriticalSection(pCriticalSection)
{
	::EnterCriticalSection(m_pCriticalSection);
}

CriticalSectionLocker::~CriticalSectionLocker()
{
	::LeaveCriticalSection(m_pCriticalSection);
}
