#include "stdafx.h"
#include "mainviewimpl.h"


mainviewimpl::mainviewimpl()
{
}


mainviewimpl::~mainviewimpl()
{
}

//////////////////////////////////////////////////////////////////////////
DOCALLMETHODIMP mainviewimpl::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	DOCALLRESULT	hr = S_OK;
	if (prot != NULL)
	{
		m_pRot = prot;
	}
	return hr;
}
DOCALLMETHODIMP mainviewimpl::Init(void*)
{
	DOCALLRESULT		hr = S_OK;

	return hr;
}
DOCALLMETHODIMP mainviewimpl::Uninit()
{
	DOCALLRESULT		hr = S_OK;

	return hr;
}
DOCALLMETHODIMP mainviewimpl::Start()
{
	DOCALLRESULT		hr = S_OK;

	return hr;
}
DOCALLMETHODIMP mainviewimpl::Stop()
{
	DOCALLRESULT		hr = S_OK;

	return hr;
}
//////////////////////////////////////////////////////////////////////////
DOCALLMETHODIMP mainviewimpl::InitParams(const wchar_t* directui, DWORD dwStyles, DWORD dwExStyles)
{
	DOCALLRESULT		hr = S_OK;

	return hr;
}
DOCALLMETHODIMP_(void*) mainviewimpl::Create(void* hParentHwnd)
{
	return this;
}
DOCALLMETHODIMP mainviewimpl::Destroy()
{
	DOCALLRESULT		hr = S_OK;

	return hr;
}
DOCALLMETHODIMP_(BOOL) mainviewimpl::Show(int nCmdShow)
{
	BOOL bret = TRUE;
	return bret;
}
DOCALLMETHODIMP_(INT_PTR) mainviewimpl::DoModal(void* hParentHwnd)
{
	INT_PTR intPtr = 1;
	return intPtr;
}
DOCALLMETHODIMP mainviewimpl::EndModal(INT_PTR nResult)
{
	DOCALLRESULT		hr = S_OK;

	return hr;
}

DOCALLMETHODIMP_(void*) mainviewimpl::GetView()
{
	return this;
}
DOCALLMETHODIMP mainviewimpl::InitMessageLoop(IPaintManagerUI* pPaintManager)
{
	DOCALLRESULT		hr = S_OK;

	return hr;
}
DOCALLMETHODIMP mainviewimpl::UnInitMessageLoop()
{
	DOCALLRESULT		hr = S_OK;

	return hr;
}

