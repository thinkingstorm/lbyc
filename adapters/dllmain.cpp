// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "adaptersimpl.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


BEGIN_CLIDMAP
	CLIDMAPENTRY_BEGIN
		CLIDMAPENTRY_PROGID(CLSID_Adapters, CAdaptersImpl,"Adapters.Impl")
	CLIDMAPENTRY_END
END_CLIDMAP_AND_EXPORTFUN

MD_EXPORTS DllCanUnloadNow(void)
{
	return FALSE;
}

MD_EXPORTS DllRegisterServer(void)
{
	return S_OK;
}
MD_EXPORTS DllUnregisterServer(void)
{
	return S_OK;
}