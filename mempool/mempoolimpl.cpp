#include "mempoolimpl.h"

CMemPoolImpl::CMemPoolImpl(void)
{	
}

CMemPoolImpl::~CMemPoolImpl(void)
{
}
//////////////////////////////////////////////////////////////////////////
std_method_impl CMemPoolImpl::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	DOCALLRESULT		hr	=	S_OK;
	if (prot != NULL)
	{
		m_pRot	=	prot;
	}
	return hr;
}
std_method_impl CMemPoolImpl::Init(void*)
{
	DOCALLRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CMemPoolImpl::Uninit()
{
	DOCALLRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CMemPoolImpl::Start()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CMemPoolImpl::Stop()
{
	HRESULT		hr	=	S_OK;
	return hr;
}
std_method_impl CMemPoolImpl::MemPool(MemPoolType type,const char* memfile)
{
	return S_OK;
}
std_method_type_impl(void*) CMemPoolImpl::Memalloc(size_t size)
{
	return malloc(size);
}

std_method_type_impl(void*) CMemPoolImpl::MemNalloc(size_t size)
{
	return malloc(size);
}
std_method_type_impl(void*) CMemPoolImpl::MemNallocalign(size_t size,size_t alignment)
{
	return malloc(size);
}
std_method_type_impl(uintptr_t) CMemPoolImpl::GetPageSize()
{
	return memory_getpagesize();
}
std_method_impl CMemPoolImpl::MemPoolFree()
{
	return S_OK;
}
std_method_impl CMemPoolImpl::MemPoolRest()
{
	return S_OK;
}
//////////////////////////////////////////////////////////////////////////////////////
 uintptr_t CMemPoolImpl::memory_getpagesize()
 {
	 
	uintptr_t size = 4096;
#ifndef __GNUC__
	SYSTEM_INFO systemInfo;  
    GetSystemInfo(&systemInfo);
	size = systeminfo.dwPageSize;
#else
	size = getpagesize();
#endif
	return size;
 }
