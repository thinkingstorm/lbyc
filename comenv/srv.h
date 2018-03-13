#ifndef _SRV_H_
#define _SRV_H_
#include "stdafx.h"


// {5D37C04C-8F58-4d47-94C8-B94153399473}
MD_DEFINE_GUID(CLSID_SRV,0x5d37c04c, 0x8f58, 0x4d47, 0x94, 0xc8, 0xb9, 0x41, 0x53, 0x39, 0x94, 0x73);


#ifdef _MSC_VER

class CDisableIME
{
public:
	CDisableIME()
	{
		m_hMod = NULL;
		pImmDisableIME = NULL;
	}

	bool LoadFunctions()
	{
		if(!m_hMod) 
			m_hMod = LoadLibrary(L"IMM32.DLL");

		if(m_hMod)
		{
			if(!pImmDisableIME)
				*(void**)&pImmDisableIME = GetProcAddress(m_hMod, "ImmDisableIME");

		}

		return (pImmDisableIME != NULL); // && pImmSetOpenStatus && pImmEnumInputContext);
	}

	void DisableIme(DWORD dwThreadID)
	{
		if(LoadFunctions())
			pImmDisableIME(dwThreadID);

	}

	void FreeIme()
	{
		if(m_hMod)
		{
			FreeLibrary(m_hMod);
			m_hMod = NULL;
		}
	}

	~CDisableIME()
	{
		FreeIme();
	}

private:
	HMODULE m_hMod;
	BOOL (WINAPI *pImmDisableIME)(DWORD);
};

#endif



class CSrv : public IMdPlugin,
	public IMdPluginRun,
	public IExit,
	public CUnknownImp
{
public:
	CSrv(void);
	~CSrv(void);

	UNKNOWN_IMP3_(IMdPlugin, IMdPluginRun, IExit);
	std_method_impl init_class(IModuleBase* prot, IModuleBase* punkOuter);

	std_method(Init)(void*);
	std_method(Uninit)();

	std_method(Start)();
	std_method(Stop)();

	std_method(NotifyExit)(bool* bExit = NULL);

private:
	DWORD	m_mainThreadId;

	HRESULT MainRun();
};
#endif