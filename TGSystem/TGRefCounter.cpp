#include "TGRefCounter.h"

TGReferenceCounter::TGReferenceCounter()
: ReferenceCount(0)
, UseMonitor(false)
#ifdef _DEBUG
, CanBeDestructed(false)
#endif
{
#ifdef MONITOR_ALL_OBJECTS
	PushDestroyMonitor();
#endif
}
//-----------------------------------------------------------------------------

TGReferenceCounter::~TGReferenceCounter()
{
#ifdef CHECK_DESTRUCTORS
	SN_ASSERT_MSG(CanBeDestructed || !ReferenceCount, "Попытка прямого уничтожения объекта, имеющего указатели с подсчетом ссылок");
#endif
	//if (UseMonitor)
	//	SNReferenceCounterMonitor::PopObjectDestroy(this);
	//SN_ASSERT(!ReferenceCount);
}

//-----------------------------------------------------------------------------

void TGReferenceCounter::AddRef()
{
#ifdef WIN32
	LONG value = InterlockedIncrement(&ReferenceCount);
#else
	SNCSLocker locker(CS);
	LONG value = ++ReferenceCount;
#endif
}
//-----------------------------------------------------------------------------

void TGReferenceCounter::DelRef()
{
#ifdef WIN32
	LONG value = InterlockedDecrement(&ReferenceCount);
#else
	SNCSLocker locker(CS);
	LONG value = --ReferenceCount;
#endif
	if (!value)
	{
#ifdef _DEBUG
		CanBeDestructed = true;
#endif
		delete this;
	}
}
//-----------------------------------------------------------------------------
void TGReferenceCounter::PushDestroyMonitor()
{
	//SNReferenceCounterMonitor::PushObjectDestroy(this);
	UseMonitor = true;
}
//-----------------------------------------------------------------------------

TGReferenceCounter* TGReferenceCounter::GetReferenceCounter()
{
	return this;
}
//-----------------------------------------------------------------------------

long TGReferenceCounter::GetReferenceCount() const
{
	return ReferenceCount;
}