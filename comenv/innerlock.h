#ifndef __SRVMGR_INNERLOCK_H__
#define __SRVMGR_INNERLOCK_H__

class CSrvNullCriticalSection
{
public:
	void Lock() {}
	void Unlock() {}
	CSrvNullCriticalSection() {}
	~CSrvNullCriticalSection() {}
};

class CSrvCriticalSection
{
public:
	void Lock() 
	{
		lockadd(&m_sec);
	}
	void Unlock() 
	{
		lockdel(&m_sec);
	}
	
	CSrvCriticalSection() 
	{
		lockinit(&m_sec);
	}
	~CSrvCriticalSection() 
	{
		lockuninit(&m_sec);
	}
	
	long m_sec;
};



template<class LockType>
class CSrvCriticalSectionAtuoLock
{
public:
	LockType* m_lock;
	
	CSrvCriticalSectionAtuoLock(LockType* lock):m_lock(lock)
	{
		m_lock->Lock();
	}

	~CSrvCriticalSectionAtuoLock()
	{
		m_lock->Unlock();
	}
};

#endif