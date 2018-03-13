#include "adaptersimpl.h"

CAdaptersImpl::CAdaptersImpl(void)
{
}

CAdaptersImpl::~CAdaptersImpl(void)
{
}
//////////////////////////////////////////////////////////////////////////
std_method_impl CAdaptersImpl::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	HRESULT		hr	=	S_OK;
	if (prot != NULL)
	{
		m_pRot	=	prot;
	}
	return hr;
}
std_method_impl CAdaptersImpl::Init(void*)
{
	HRESULT		hr	=	S_OK;
 
    

	return hr;
}
std_method_impl CAdaptersImpl::Uninit()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAdaptersImpl::Start()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAdaptersImpl::Stop()
{
	HRESULT		hr	=	S_OK;
	return hr;
}
std_method_impl CAdaptersImpl::RegisterFunc(const char* file)
{
	HRESULT		hr	=	S_OK;
	return hr;
}
std_method_impl CAdaptersImpl::RegisterVariable(const char* file)
{
	HRESULT		hr	=	S_OK;
	return hr;
}
std_method_impl CAdaptersImpl::CallFunc(const char* file)
{
    HRESULT		hr	=	S_OK;
    return hr;   
}
