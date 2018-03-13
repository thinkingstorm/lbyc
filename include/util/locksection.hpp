#ifndef _LOCKSECTION_H_
#define _LOCKSECTION_H_

#include <util/core.hpp>
#include <util/lockex.hpp>

#ifndef __GNUC__
		
#else
	#include <pthread.h>
#endif



namespace util {

class CNullCriticalSection
{
public:
	void Lock() {}
	void Unlock() {}
	CNullCriticalSection() {}
	~CNullCriticalSection() {}
};

class CAutoCriticalSection
{
public:
	void Lock() 
	{
#ifndef __GNUC__
		EnterCriticalSection(&m_sec);
#else
		pthread_mutex_lock(&m_sec);
#endif
	}

	void Unlock() 
	{
#ifndef __GNUC__
		LeaveCriticalSection(&m_sec);
#else
		pthread_mutex_unlock(&m_sec);
#endif
	}
	
	CAutoCriticalSection() 
	{
		 
#ifndef __GNUC__
		InitializeCriticalSection(&m_sec);
#else
		pthread_mutex_init(&m_sec, NULL);
#endif
	}


	~CAutoCriticalSection() 
	{
#ifndef __GNUC__
		DeleteCriticalSection(&m_sec);
#else
		pthread_mutex_destroy(&m_sec);
#endif
	}

#ifndef __GNUC__
	CRITICAL_SECTION m_sec;
#else
	pthread_mutex_t m_sec;
#endif
};

class CSingleAutoCriticalSection
{
protected:
	inline LONG Increment(long* p) 
	{
#ifndef __GNUC__
		return ::InterlockedIncrement(p);
#else
		__sync_add_and_fetch(p, 1);
		return *p;
#endif
	}

	inline LONG Decrement(long* p) 
	{
#ifndef __GNUC__
		return ::InterlockedDecrement(p);
#else
		__sync_sub_and_fetch(p, 1);
		return *p;
#endif
	}

public:
	CSingleAutoCriticalSection() 
	{
		m_dwRef = 1L;
#ifndef __GNUC__
		InitializeCriticalSection(&m_sec);
#else
		pthread_mutex_init(&m_sec, NULL);
#endif
	}
	~CSingleAutoCriticalSection() 
	{
#ifndef __GNUC__
		DeleteCriticalSection(&m_sec);
#else
		pthread_mutex_destroy(&m_sec);
#endif
	}	
	
	void Lock() 
	{
#ifndef __GNUC__
		EnterCriticalSection(&m_sec);
#else
		pthread_mutex_lock(&m_sec);
#endif
	}

	void Unlock()
   {
#ifndef __GNUC__
		LeaveCriticalSection(&m_sec);
#else
		pthread_mutex_unlock(&m_sec);
#endif
	}
	
	LONG AddRef() 
	{
		return Increment(&m_dwRef);
	}
	LONG ReleaseRef()
	{
		LONG l = Decrement(&m_dwRef);		
		return l;
	}

#ifndef __GNUC__
	CRITICAL_SECTION m_sec;
#else
	pthread_mutex_t m_sec;
#endif
	LONG m_dwRef;
};


template<class _TInterface>
class CSingleInstance : public _TInterface
{
protected:
	LONG m_dwRef;

	inline ULONG Increment(long* p) 
	{
#ifndef __GNUC__
		return ::InterlockedIncrement(p);
#else
		__sync_add_and_fetch(p, 1);
		return *p;
#endif
	}
	inline ULONG Decrement(long* p)
   {
#ifndef __GNUC__
		return ::InterlockedDecrement(p);
#else
		__sync_sub_and_fetch(p, 1);
		return *p;
#endif
	}

public:
	CSingleInstance() 
	{
		m_dwRef = 1L;
	}
	virtual ~CSingleInstance() 
	{
		Decrement(&m_dwRef);
	}

	virtual long AddRef() {return Increment(&m_dwRef);}
	virtual long ReleaseRef()
	{
		LONG l = Decrement(&m_dwRef);
		if (l == 0)
		{
			delete this;
		}
		return l;
	}
};




template <class T>
class CStackLockWrapper
{
	public:
		CStackLockWrapper(T& _t) : t(_t)
		{
			t.Lock();
		}
		~CStackLockWrapper()
		{
			t.Unlock();
		}
		T &t;
};


template <class T>
class CStackLockWrapper2
{
public:
	CStackLockWrapper2(T* _t) : t(_t)
	{
		t->Lock();
	}
	~CStackLockWrapper2()
	{
		t->Unlock();
	}
	T *t;
};

typedef CStackLockWrapper<CAutoCriticalSection> CStackAutoCSLock;


#define	DECLARE_AUTOLOCK_CS(name)				CAutoCriticalSection	m_cs ## name
#define AUTOLOCK_CS(name)						CStackAutoCSLock lock(m_cs ## name)
#define AUTOLOCK_CS_LOCK(name)					m_cs ## name.Lock()		
#define AUTOLOCK_CS_UNLOCK(name)				m_cs ## name.Unlock()

} 
#endif 
