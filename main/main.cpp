#include "stdafx.h"
#include <data/iinfoanalsis.h>
#include <compat/getpath.hpp>
#include <adapter/ilua.h>
#include <adapter/ipy.h>



int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	

	HRESULT hr	=	S_OK;
	CComLoader loader;
	_lComPtr<IComEnv>	pIComEnv;
	tstring stringcomenv;
	tstring stringpath = GetCurrentRunPath(NULL);

	tstring stringconfig;

#ifndef __GNUC__
	stringpath += _T("\\");
#else
	stringpath += _T("//");
#endif
	
	stringcomenv	=	stringpath;
	stringconfig	=	stringpath;
	stringconfig += _T("mainmoduleconfig.json");

#ifndef __GNUC__
	stringcomenv += _T("comenv.dll");
#else
	stringcomenv += _T("libcomenv.so");
#endif

	printf("11\n");
	BOOL bRet		=	loader.LoadCom(stringcomenv.c_str());
	
	if (bRet == TRUE)
		loader.CreateInstance(CLSID_ComEnv,NULL,NULL,re_uuidof(IComEnv),(void**)&pIComEnv.m_p);
	
	if (pIComEnv.m_p != NULL)
	{
		hr = pIComEnv->InitEnv(TRUE, hInstance, stringconfig.c_str(), NULL, NULL);
		if (hr == S_OK)
		{
			pIComEnv->Run();
		}
	}
	return 1;
}


#ifdef _MSC_VER


#endif


#ifdef __GNUC__

	int main(int argc,char* argv[])
	{
		return WinMain(0,0,argv[0],0);
	}
#endif


