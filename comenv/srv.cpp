// rssrv.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "srv.h"

CSrv::CSrv(void)
:m_mainThreadId(0)
{

#ifdef _MSC_VER
	CDisableIME cdime;			
	cdime.DisableIme(-1);		
#endif // _MSC_VER

}

CSrv::~CSrv(void)
{
}

std_method_impl CSrv::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	return S_OK;
}

std_method_impl CSrv::Init(LPVOID lpVoid/* =NULL*/)
{
	return S_OK;
}

std_method_impl CSrv::Uninit()
{
	return S_OK;
}

std_method_impl CSrv::Start()
{
	return MainRun();
}

std_method_impl CSrv::Stop()
{
	return S_OK;
}

std_method_impl CSrv::NotifyExit(bool* bExit/* = NULL*/)
{
	return S_OK;
}

HRESULT CSrv::MainRun()
{
	
	return S_OK;
}
