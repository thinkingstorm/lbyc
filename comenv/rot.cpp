#include "stdafx.h"
#include "rot.h"

CRot::CRot(void)
{
}

CRot::~CRot(void)
{
}

std_method_impl CRot::init_class(IModuleBase *prot, IModuleBase *punkOuter)
{
	return S_OK;
}


std_method_impl CRot::Register(const GUID& rpid, IModuleBase *punk)
{
	retrtpv(S_OK != IsRunning(rpid), MK_S_MONIKERALREADYREGISTERED);

	RUNNINGTABLEITEM& Item = m_map[rpid];
	Item.dwInitMark = 0;
	Item.m_ptr = punk;

	return S_OK;
}

std_method_impl CRot::Revoke(const GUID& rpid)
{
	retrtpv(S_OK == IsRunning(rpid), E_INVALIDARG);
	m_map.erase(rpid);

	return S_OK;
}

std_method_impl CRot::IsRunning(const GUID& rpid)
{
	return m_map.end() != m_map.find(rpid) ? S_OK : S_FALSE;
}

std_method_impl CRot::GetObject(const GUID& rpid, const IID iid, IModuleBase **ppunk)
{
	OBJMAP::iterator it = m_map.find(rpid);
	retrtpv(m_map.end() != it, E_INVALIDARG);

	if (it->second.dwInitMark == 0)
	{
		if(it->second.m_ptr)
			return it->second.m_ptr->QueryInterface(iid, (void**)ppunk);
	}
	else
	{
		//m_ObjLoader->CreateInstance(m_ObjLoader,it->second.clsid, 0, it->second.iid, (void**)ppunk);
	}

	return E_NOINTERFACE;
}

std_method_impl CRot::RevokeAll()
{
	char strGuid[_MAX_PATH] = {0};
	for (OBJMAP::iterator it = m_map.begin(); it != m_map.end(); ++it )
	{
		GUIDToSA(it->first, strGuid, _MAX_PATH);
		it->second.m_ptr = INULL;
	}
	m_map.clear();

	return S_OK;
}

std_method_impl CRot::RegisterCreateInterface(const GUID& rpid, const CLSID& clsid,const IID& iid)
{
	retrtpv(S_OK != IsRunning(iid), MK_S_MONIKERALREADYREGISTERED);

	RUNNINGTABLEITEM& Item = m_map[iid];
	Item.dwInitMark = 1;
	Item.clsid = clsid;
	Item.iid = iid;
	return S_OK;
}

std_method_type_impl(LPCSTR) CRot::ProgIDFromCLSID(REFCLSID clsid)
{
	_lComPtr<IObjectLoaderEx> pObjLoader;
	
	retrtpv(SUCCEEDED(GetObject(CLSID_CObjectLoader, re_uuidof(IObjectLoaderEx), (IModuleBase**)&pObjLoader)),"");
	retrtpv(pObjLoader, "");

	return pObjLoader->ProgIDFromCLSID(clsid);
}

std_method_type_impl(CLSID) CRot::CLSIDFromProgID(LPCSTR lpProgId)
{
	_lComPtr<IObjectLoaderEx> pObjLoader;

	retrtpv(SUCCEEDED(GetObject(CLSID_CObjectLoader, re_uuidof(IObjectLoaderEx), (IModuleBase**)&pObjLoader)), GUID_NULL);
	retrtpv(pObjLoader, GUID_NULL);

	return pObjLoader->CLSIDFromProgID(lpProgId);
}

std_method_type_impl(UINT) CRot::GetObjectCount()
{
	return m_map.size();
}

std_method_impl CRot::BeginEnum()
{
	m_itEnum = m_map.begin();

	if(m_itEnum == m_map.end())
		return S_FALSE;

	return S_OK;
}

std_method_type_impl(BOOL) CRot::NextObject(CLSID *pclsId)
{
	if(m_itEnum != m_map.end())
	{
		if(pclsId)
		{
			*pclsId = m_itEnum->first;
		}
		m_itEnum++;
	}

	return (m_itEnum != m_map.end());
}