#ifndef _LOADCOM_H_
#define _LOADCOM_H_


#include <util/util.h>
using namespace util;

#include <dlcom/byunknown.hpp>




MD_EXPORTS DllGetClassObject(REFCLSID rclsid,REFIID riid,LPVOID* ppv);



typedef	HRESULT (BY_STDCALL *DefineDllGetClassObject)(REFCLSID rclsid,REFIID riid,LPVOID* ppv);
typedef HRESULT (BY_STDCALL *DefineDllCanUnloadNow)(void);
typedef	HRESULT (BY_STDCALL *DefineDllRegisterServer)(void);
typedef	HRESULT (BY_STDCALL *DefineDllUnregisterServer)(void);

 

class CComLoader : protected tImpModuleMid<CComLoader>  
{
public:
	DefineDllGetClassObject 	DllGetClassObject;
	DefineDllCanUnloadNow 		DllCanUnloadNow;
	DefineDllRegisterServer 	DllRegisterServer;
	DefineDllUnregisterServer 	DllUnregisterServer;
public: 
	inline CComLoader(TCHAR* modname) :tImpModuleMid<CComLoader>(modname)
	{
		LoadCom(modname);
		InitIAT();
	}
	inline CComLoader(HMODULE hMod) : tImpModuleMid<CComLoader>(hMod)
	{
		if (m_hMod != NULL)
			InitIAT();
	} 
	inline CComLoader() : tImpModuleMid<CComLoader>(_T("modulecom"))
	{
		//InitIAT();
	} 
	virtual STFunDesc *GetFunDefs() 
	{ 
		static STFunDesc s_FunDefs[]= 
		{
			/*
			{ (char *)"DllGetClassObject",offsetof(class CComLoader, DllGetClassObject)},
			{ (char *)"DllCanUnloadNow", offsetof(class CComLoader, DllCanUnloadNow)},
			{ (char *)"DllRegisterServer", offsetof(class CComLoader, DllRegisterServer)},
			{ (char *)"DllUnregisterServer", offsetof(class CComLoader, DllUnregisterServer)},
			{ (char *)"null",0}
			*/
			{ (char *)"DllGetClassObject",0},
			{ (char *)"DllCanUnloadNow",1},
			{ (char *)"DllRegisterServer",2},
			{ (char *)"DllUnregisterServer",3},
			{ (char *)"null",4}

		}; 
		return s_FunDefs;
	}
	virtual bool setfuncaddress(int i,void *p)
	{

		switch(i)
		{
			case 0:
				this->DllGetClassObject = (DefineDllGetClassObject)(p);
				break;
			case 1:
				this->DllCanUnloadNow =  (DefineDllCanUnloadNow)(p);
				break;
			case 2:
				this->DllRegisterServer = (DefineDllRegisterServer)(p);
				break;
			case 3:
				this->DllUnregisterServer = (DefineDllUnregisterServer)(p);
				break;
			default:
				break;
		}
		return true;

	}
	virtual ~CComLoader()
	{
		UnloadCom();
	}
public:
	BOOL LoadCom(const TCHAR* pModPathName)
	{
		memset(m_szModuleName,0,MAX_PATH);
		tstring_strcpy(m_szModuleName,pModPathName);


		int nRet = Load();
		if (nRet == -1)
		{
			memset(m_szModuleName,0,MAX_PATH);
			return FALSE;
		}
		

		if(DllGetClassObject == NULL) return FALSE;

		DllGetClassObject(CLSID_MDClassFactory, re_uuidof(IComObjectFrameworkClassFactory), (void**)&m_pClassFactory);
		if(m_pClassFactory)
		{
			return TRUE;
		}

		UnloadCom();
		return FALSE;
	}
	virtual void UnloadCom()
	{
		//m_pClassFactory = INULL;

		if(m_pClassFactory)
			m_pClassFactory = INULL;
		UnLoad();
	}
	HRESULT CreateInstance(REFCLSID rclsid, IModuleBase *prot, IModuleBase *punkOuter, const IID& riid, void **ppv)
	{
		*ppv = NULL;

		retrtpv(IsLoaded(), E_FAIL);
		{	
			/*
			m_pClassFactory = INULL;
			_lComPtr<IComObjectFrameworkClassFactory> pClassFactory = INULL;
			 
			if(SUCCEEDED(DllGetClassObject(rclsid, re_uuidof(IComObjectFrameworkClassFactory), (void**)&pClassFactory)) && pClassFactory)
			{
				return pClassFactory->CreateInstance(prot, punkOuter, riid, ppv);
			}
			*/
		
			_lComPtr<IClassFactory__> pClassFactory;
			if(SUCCEEDED(DllGetClassObject(rclsid, re_uuidof(IClassFactory__), (void**)&pClassFactory)) && pClassFactory)
			{
				_lComPtr<IComObjectFrameworkClassFactory> pOFClassFactory = pClassFactory;
				if(pOFClassFactory)
					return pOFClassFactory->CreateInstance(prot, punkOuter, riid, ppv);
				else
					return pClassFactory->CreateInstance(punkOuter, riid, ppv);
			}

		}

		return E_FAIL;
	}
	LONG GetCount()
	{
		if(m_pClassFactory)
			return m_pClassFactory->GetCount();

		return 0;
	}
	CLSID GetAt(INT nIndex)
	{
		if(m_pClassFactory)
			return m_pClassFactory->GetAt(nIndex);
		return GUID_NULL;
	}
	LPCSTR ProgIDFromCLSID(REFCLSID clsid)
	{
		if(m_pClassFactory)
			return m_pClassFactory->ProgIDFromCLSID(clsid);
		return "";
	}
	bool IsLoaded()
	{
		return tImpModuleMid<CComLoader>::IsLoaded();
	}
	LPCTSTR GetModuleName()
	{
		return m_szModuleName;
	}
protected:
	typedef tImpModuleMid<CComLoader> TBase;
	_lComPtr<IComObjectFrameworkClassFactory> m_pClassFactory;

};

#endif 