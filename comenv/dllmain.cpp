// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"


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



#include "comenv.h"
#include "objectloader.h"
#include "rot.h"
#include "mainrun.h"
#include <dlcom/tproperty.h>
#include "srv.h"

typedef TProperty<IProperty, CNullCriticalSection, memless<CLSID> >	CProperty;
typedef TProperty<IProperty, CAutoCriticalSection, memless<CLSID> >	CPropertyThread;
typedef TProperty<IProperty2>										CProperty2;
typedef TProperty<IProperty2, CAutoCriticalSection>					CProperty2Thread;




BEGIN_CLIDMAP
	CLIDMAPENTRY_BEGIN
		CLIDMAPENTRY_PROGID(CLSID_ComEnv, ComEnv, "RscomEnv.1")
		CLIDMAPENTRY_PROGID(CLSID_CObjectLoader, CObjectLoader, "ObjectLoader.1")
		CLIDMAPENTRY_PROGID(ClSID_CRunningObjectTable, CRot, "Rot.1")
		CLIDMAPENTRY_PROGID(CLSID_CMainRun, CMainRun,"MainRun.1")
		CLIDMAPENTRY_PROGID(CLSID_SRV, CSrv,"RsSrv.1")
		CLIDMAPENTRY_PROGID(CLSID_CProperty, CProperty,"Property.1")
		CLIDMAPENTRY_PROGID(CLSID_CProperty_thread, CPropertyThread,"PropertyThread.1")
		CLIDMAPENTRY_PROGID(CLSID_CProperty2, CProperty2,"Property2.1")
		CLIDMAPENTRY_PROGID(CLSID_CProperty2_thread, CProperty2Thread,"Property2Thread.1")
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