#ifndef _MAINVIEW_H_
#define _MAINVIEW_H_

#pragma once

#include <ui/iuibase.h>


class mainviewimpl :	public  IView,
						public  IMdPlugin,
						public  IMdPluginRun,
						public	CUnknownImp
{
public:
	mainviewimpl();
	~mainviewimpl();

	UNKNOWN_IMP3_(IMdPlugin, IMdPluginRun, IView);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	DOCALLMETHODIMP init_class(IModuleBase* prot, IModuleBase* punkOuter);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	DOCALLMETHOD(Init)(void*);
	DOCALLMETHOD(Uninit)();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	DOCALLMETHOD(Start)();
	DOCALLMETHOD(Stop)();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	DOCALLMETHOD(InitParams)(const wchar_t* directui, DWORD dwStyles = 0, DWORD dwExStyles = 0);
	DOCALLMETHOD_(void*, Create)(void* hParentHwnd = NULL);
	DOCALLMETHOD(Destroy)();
	DOCALLMETHOD_(BOOL, Show)(int nCmdShow) = 0;
	DOCALLMETHOD_(INT_PTR, DoModal)(void* hParentHwnd = NULL);
	DOCALLMETHOD(EndModal)(INT_PTR nResult);
	DOCALLMETHOD_(void*, GetView)();
	DOCALLMETHOD(InitMessageLoop)(IPaintManagerUI* pPaintManager);
	DOCALLMETHOD(UnInitMessageLoop)();
private:
	_lComPtr<IComRunningObjectTable>				m_pRot;

};
#endif

