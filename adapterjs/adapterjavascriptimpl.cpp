#include "adapterjavascriptimpl.h"
CAdapterjavascriptImpl::CAdapterjavascriptImpl(void)
{
}

CAdapterjavascriptImpl::~CAdapterjavascriptImpl(void)
{
}
//////////////////////////////////////////////////////////////////////////
std_method_impl CAdapterjavascriptImpl::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	HRESULT		hr	=	S_OK;
	if (prot != NULL)
	{
		m_pRot	=	prot;
	}
	return hr;
}
std_method_impl CAdapterjavascriptImpl::Init(void*)
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAdapterjavascriptImpl::Uninit()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAdapterjavascriptImpl::Start()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAdapterjavascriptImpl::Stop()
{
	HRESULT		hr	=	S_OK;
	return hr;
}
std_method_impl CAdapterjavascriptImpl::RunFile(const char* file)
{
	HRESULT		hr = S_OK;

	int argc = 2;
	char** argv = new char*[argc + 1];
	string_strcpy(argv[0],"-e");
	string_strcpy(argv[1],"console.log('Hello World')");

	return hr;
}