#include "stdafx.h"
#include "objectloader.h"

CObjectLoader::CObjectLoader(void)
{
	m_hInstance = NULL;
}

CObjectLoader::~CObjectLoader(void)
{
}

std_method_impl CObjectLoader::init_class(IModuleBase* /*prot*/, IModuleBase *punkOuter)
{
	retrtpv(!punkOuter, E_INVALIDARG);
	//init_class_map(g_mapBootClass, g_mapBootClass + sizeof(g_mapBootClass)/sizeof(g_mapBootClass[0]));
	//init_class_map(NULL, NULL);
	return S_OK;
}

std_method_impl CObjectLoader::Register(const CLSID& rclsid, LPCTSTR filename, LPVOID lpGetProc/* = NULL*/)
{
	INNER_LOCK lock(&m_CrtSection);

	CLSMAP::iterator it = m_mapCls.find(rclsid);
	if(m_mapCls.end() != it)
	{
		if(it->second.hModule) 
		{ 
			closemd(it->second.hModule); 
		}
	}
	else
	{
		std::pair<CLSMAP::iterator, bool> ib = m_mapCls.insert(std::make_pair(rclsid, ClsInfo()));
		retrtpv(ib.second, E_UNEXPECTED);
		it = ib.first;
	}

	it->second.filename = filename;
	if(lpGetProc)
	{
		it->second.hModule = (HMODULE)NULL;
		it->second.pfnGetClsObj = (PFNGetClsObj)lpGetProc;
	}
	else
	{
		it->second.hModule = 0;
		it->second.pfnGetClsObj = 0;
	}
	bzero(it->second.ProgID, sizeof(it->second.ProgID));

	return S_OK;
}

std_method_impl CObjectLoader::CreateInstance(IModuleBase *prot,const CLSID& rclsid, IModuleBase *punkOuter,
										   const IID& riid, void **ppv)
{	
	INNER_LOCK lock(&m_CrtSection);
	CLSMAP::iterator it = m_mapCls.find(rclsid);
	retrtpv(m_mapCls.end() != it, E_INVALIDARG);
	if(!it->second.hModule)
	{
		it->second.hModule = openmd((TCHAR*)it->second.filename.c_str());
		retrtpv(it->second.hModule, E_UNEXPECTED);
		it->second.pfnGetClsObj = (PFNGetClsObj)openfunc(it->second.hModule, (char*)"DllGetClassObject");
	}
	retrtpv(it->second.pfnGetClsObj, E_UNEXPECTED);
	_lComPtr<IComObjectFrameworkClassFactory> pfac;

	RFAILED(it->second.pfnGetClsObj(rclsid, re_uuidof(IComObjectFrameworkClassFactory), (void**)&pfac));
	return pfac->CreateInstance(prot, punkOuter, riid, ppv);
}

std_method_impl CObjectLoader::Revoke(const CLSID& rclsid)
{
	INNER_LOCK lock(&m_CrtSection);

	CLSMAP::iterator it = m_mapCls.find(rclsid);
	retrtpv(m_mapCls.end() != it, S_FALSE);
	if(it->second.hModule && it->second.hModule != (HMODULE)-1) 
	{ 
		closemd(it->second.hModule); 
	}

	m_mapCls.erase(it);
	return S_OK;
}

std_method_impl CObjectLoader::FreeUnusedLibraries()
{
	INNER_LOCK lock(&m_CrtSection);
	for(CLSMAP::iterator it = m_mapCls.begin(); it != m_mapCls.end(); ++it)
	{
		if(it->second.hModule && it->second.hModule !=(HMODULE) -1)
		{
			closemd(it->second.hModule);
			it->second.hModule = 0;
		}
	}
	m_mapCls.clear();

	return S_OK;

}

std_method_type_impl(LPCSTR) CObjectLoader::ProgIDFromCLSID(REFCLSID clsid)
{
	CLSMAP::const_iterator it = m_mapCls.find(clsid);
	retrtpv(m_mapCls.end() != it, "");

	return it->second.ProgID;
}

std_method_type_impl(CLSID) CObjectLoader::CLSIDFromProgID(LPCSTR lpProgId)
{
	retrtpv(lpProgId && *lpProgId, GUID_NULL);
	size_t sSize = m_mapCls.size();
	retrtpv(sSize > 0, GUID_NULL);

	CLSMAP::iterator it = m_mapCls.begin();
	for(; it != m_mapCls.end(); it++)
	{
		ClsInfo &info = it->second;
		if(0 == string_stricmp(info.ProgID, lpProgId))
		{
			return it->first;
		}
	}

	return GUID_NULL;
}

std_method_impl CObjectLoader::SetProgId(const CLSID& rclsid, LPCSTR progId)
{
	retrtpv(progId, E_FAIL);

	CLSMAP::iterator it = m_mapCls.find(rclsid);
	retrtpv(m_mapCls.end() != it, E_FAIL);

	ClsInfo &clsInfo = it->second;
	string_strcpy(clsInfo.ProgID, progId);

	return S_OK;
}
