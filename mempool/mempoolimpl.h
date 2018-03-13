#ifndef _ASYNIOIMPL_H_
#define _ASYNIOIMPL_H_

#include "stdafx.h"
#include <compat/getpath.hpp>
#include <mem/imempool.h>

class CMemPoolImpl : 		public	IMemPool,
							public  IMdPlugin,
							public  IMdPluginRun,
							public	CUnknownImp
{
public:
	CMemPoolImpl(void);
	virtual ~CMemPoolImpl(void);
	

	UNKNOWN_IMP3_(IMdPlugin, IMdPluginRun,IMemPool);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	std_method_impl init_class(IModuleBase* prot, IModuleBase* punkOuter);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	std_method(Init)(void*);
	std_method(Uninit)();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	std_method(Start)();
	std_method(Stop)();

	//////////////////////////////////////////////////////////////////////////
	std_method(MemPool)(MemPoolType type,const char* memfile);
	std_method_(void*, Memalloc)(size_t size);
	std_method_(void*, MemNalloc)(size_t size);
	std_method_(void*, MemNallocalign)(size_t size,size_t alignment);
	std_method_(uintptr_t, GetPageSize)();
	std_method(MemPoolFree)();
	std_method(MemPoolRest)();
	//////////////////////////////////////////////////////////////////////////
private:
	_lComPtr<IComRunningObjectTable>	m_pRot;
private:
	uintptr_t			memory_getpagesize();
private:
	uintptr_t 			m_pagesize;

	


};
#endif