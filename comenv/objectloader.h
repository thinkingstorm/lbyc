#ifndef _OBJECTLOADER_H_
#define _OBJECTLOADER_H_


#include "stdafx.h"
#include "innerlock.h"

class CObjectLoader : public IObjectLoaderEx
	, public IOLManagerEx
	, public CUnknownImp 
{
public:
	CObjectLoader(void);
	~CObjectLoader(void);

	UNKNOWN_IMP4_(IObjectLoaderEx, IObjectLoader, IOLManagerEx, IOLManager);

	std_method_impl init_class(IModuleBase* prot, IModuleBase* punkOuter);

	std_method(CreateInstance)(IModuleBase* prot, const CLSID& rclsid, IModuleBase *punkOuter, const IID& riid, void **ppv);
	std_method_(LPCSTR, ProgIDFromCLSID)(REFCLSID clsid);
	std_method_(CLSID, CLSIDFromProgID)(LPCSTR lpProgId);

public:
	std_method(Register)(const CLSID& rclsid, LPCTSTR filename, LPVOID lpGetProc = NULL);
	std_method(Revoke)(const CLSID& rclsid);	
	std_method(FreeUnusedLibraries)();
	std_method(IsComponentValid)()
	{
		return E_NOTIMPL;
	}
	std_method(IsLibValid)()
	{
		return E_NOTIMPL;
	}
	std_method_(DWORD, GetComponentModuleNames)(DWORD count, const char **ppreceive)
	{
		return 0;
	}
	std_method_(DWORD, GetComponentModuleCount)()
	{
		return m_mapCls.size();
	}

	//IOLManagerEx
	std_method(SetProgId)(const CLSID& rclsid, LPCSTR progId);

private:
	HINSTANCE		m_hInstance;
	string			m_strCfgXMLName;	
	string			m_strXmlFile;

	string			m_strRunPath;
	string			m_strProcessName;
private:

	template<class It> void init_class_map(It begin, It end)
	{
		m_mapCls.clear();
	}

	typedef HRESULT (WINAPI * PFNGetClsObj)(const CLSID&, const IID&, void**);

	struct ClsInfo
	{
		HMODULE hModule;
		tstring filename;
		PFNGetClsObj pfnGetClsObj;
		char ProgID[MAX_PROGIDLEN];

		ClsInfo(): hModule(NULL)
			, pfnGetClsObj(NULL)
		{
			filename.clear();

		}
	};

	typedef std::map<CLSID, ClsInfo, memless<CLSID> > CLSMAP;

	CLSMAP m_mapCls;

	CSrvCriticalSection m_CrtSection;
	typedef CSrvCriticalSectionAtuoLock<CSrvCriticalSection> INNER_LOCK;
};
#endif
