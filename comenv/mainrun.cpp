#include "stdafx.h"
#include "mainrun.h"


#define SUBPROCFILE_START_SEQ	100000	//认为每个文件里不会超过这个数值

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4302)	// 'type cast' : truncation from 'LPSTR' to 'TCHAR'
#endif 

#ifdef _MSC_VER
#pragma warning (pop)
#endif 


CMainRun* CMainRun::s_pRsSrv = NULL;

CMainRun::CMainRun(void):m_hInstance(NULL)
{
	m_runMode = RM_APPLICATION;
	

	m_dwNumServicesArgs		= 0;
	m_lpServiceArgVectors	= 0;
}

CMainRun::~CMainRun(void)
{
	Uninit();
}

std_method_impl CMainRun::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	m_pRot = prot;
	retrtpv(m_pRot, E_FAIL);

	RFAILED(m_pRot->GetObject(CLSID_CObjectLoader, re_uuidof(IObjectLoader), (IModuleBase**)&m_pObjLoader));
	retrtpv(m_pObjLoader, E_FAIL);

	s_pRsSrv = this;
	return S_OK;
}

std_method_impl CMainRun::Init(HINSTANCE hInstance/* = NULL*/
							 , LPCTSTR lpCfgXMLName/* = NULL*/
							 , int iType/* = NULL*/)
{
	m_hInstance = hInstance;
	
	

	return S_OK;
}

std_method_type_impl(INT) CMainRun::Run()
{
	RFAILED(CheckCommandLine());
	switch(m_runMode)
	{
	case RM_SYSTEM:
		return ServerRun();
	case RM_SERVICE:
		return StartServer();
	case RM_NULL:
	case RM_APPLICATION:
	default:
		return ApplicationRun();
	}

	return 0;
}

std_method_impl CMainRun::Uninit()
{
	UninitPlugins();

	//////////////////////////////////////////////////////////////////////////
	if(m_pObjLoader)
	{
		m_pObjLoader = INULL;
	}

	if(m_pRot)
	{
		m_pRot = INULL;
	}

	uninitEnv();

	return S_OK;
}

std_method_impl CMainRun::NotifyExit(bool* bExit)
{
	retrtpv(m_pRot, E_INVALIDARG);

	if(GUID_NULL == m_clsMainPlugin)
	{
		if(bExit)
			(*bExit) = true;
		return S_OK;
	}

	_lComPtr<IExit> pExit;
	RFAILED(m_pRot->GetObject(m_clsMainPlugin, re_uuidof(IExit), (IModuleBase**)&pExit));
	retrtpv(pExit, E_INVALIDARG);

	return pExit->NotifyExit(bExit);
}

std_method_type_impl(BOOL) CMainRun::IsServerRun()
{
	return m_runMode == RM_SYSTEM;
}

std_method_type_impl(LPCTSTR) CMainRun::GetServerName()
{
	retrtpv(m_runMode == RM_SYSTEM, NULL);

	return m_strSrvName.c_str();
}

std_method_type_impl(LPCTSTR*) CMainRun::GetServerArg(DWORD *pdwArgc)
{
	retrtpv(m_runMode == RM_SYSTEM, NULL);
	
	if(pdwArgc)
	{
		*pdwArgc = m_dwNumServicesArgs;
	}

	return m_lpServiceArgVectors;
}

bool CMainRun::initEnv(LPCTSTR lpCfgXMLName, LPCTSTR lpXmlFile)
{
	uninitEnv();
	return true;
}

void CMainRun::uninitEnv()
{
	m_initList.clear();
	m_startList.clear();
}

HRESULT CMainRun::CheckCommandLine()
{

	return S_OK;

}

HRESULT	CMainRun::CreatePlugin(const CLSID& rpid)
{
	_lComPtr<IModuleBase> pUnknown;
	HRESULT hr = CreateRotPlugin(rpid, (IModuleBase **)&pUnknown);
	if(FAILED(hr))
	{
		return hr;
	}
	_lComPtr<IMdPlugin> pPlugin(pUnknown);

	if(pPlugin)
	{
		hr = pPlugin->Init(NULL);
		if(FAILED(hr))
		{
			pPlugin->Uninit();
			DestroyRotPlugin(rpid);
		}
		else
		{
			m_initList.push_back(rpid);
		}
	}
	return hr;
}
std_method_impl CMainRun::CreateObject(const CLSID& clsid,
						unsigned long  ulIndex,
						int		 iUi,
						const char* pszParam)
{
	HRESULT hr	=	S_OK;
	
	hr	=	CreatePlugin(clsid);
	if (hr == S_OK)
	{
		m_startList.push_back(ST_PLUGIN(ulIndex,clsid,iUi,pszParam));
	}
	else
	{
		return E_FAIL;
	}
	
	
	return hr;
}
std_method_impl CMainRun::RemoveObject(const CLSID& clsid)
{
	HRESULT hr	=	S_OK;
	return hr;
}
HRESULT CMainRun::StartPlugins()
{
	m_clsMainPlugin = GUID_NULL;
	return StartOrStopPlugins(true);
}

HRESULT CMainRun::StopPlugins()
{
	return StartOrStopPlugins(false);
}

HRESULT CMainRun::StartOrStopPlugins(bool bStart)
{
	int nSize = m_startList.size();
	retrtpv(nSize > 0, S_OK);

	retrtpv(m_pRot, E_FAIL);

	static int sLastStartIndex = 0;

	int nStart	= bStart ? 0 : sLastStartIndex;	
	int nStep	= bStart ? 1 : -1;
	
	for(int i = nStart; i < nSize && i >= 0; i += nStep)
	{
		_lComPtr<IModuleBase> pUnknown;
		RFAILED(m_pRot->GetObject(m_startList[i].clsId, re_uuidof(IModuleBase), (IModuleBase**)&pUnknown));

		_lComPtr<IMdPluginRun> pPluginRun(pUnknown);
		if(!pPluginRun)
		{
			return E_FAIL;
		}

		HRESULT hr = S_OK;

		if(bStart)
		{
			sLastStartIndex = i;
			m_clsMainPlugin = m_startList[i].clsId;
			hr = pPluginRun->Start();
			if(FAILED(hr))
			{
				return hr;
			}
			m_clsMainPlugin = GUID_NULL;
		} 
		else
		{
			hr = pPluginRun->Stop();
		}

	}

	return S_OK;
}

HRESULT CMainRun::UninitPlugins()
{
	int nSize = m_initList.size();
	retrtpv(nSize > 0, S_OK);
	retrtpv(m_pRot, E_FAIL);

	int nStart	= nSize - 1;	
	int nStep	= -1;

	for(int i = nStart; i < nSize && i >= 0; i += nStep)
	{
		_lComPtr<IModuleBase> pUnknown;
		RFAILED(m_pRot->GetObject(m_initList[i], re_uuidof(IModuleBase), (IModuleBase**)&pUnknown));

		_lComPtr<IMdPlugin> pPlugin(pUnknown);
		if(pPlugin)
		{
			pPlugin->Uninit();
		}
	}

	return S_OK;
}

HRESULT CMainRun::CreateRotPlugin(const CLSID& rpid, IModuleBase **ppunk)
{
	retrtpv(rpid != GUID_NULL, E_FAIL);
	
	retrtpv(m_pRot, E_FAIL);
	//HRESULT hr = m_pRot->GetObject(rpid, re_uuidof(IModuleBase), ppunk);
	//if(SUCCEEDED(hr))
	//	return hr;

	retrtpv(m_pObjLoader, E_FAIL);
	RFAILED(m_pObjLoader->CreateInstance(m_pRot, rpid, NULL, re_uuidof(IModuleBase), (void**)ppunk));

	retrtpv(*ppunk, E_FAIL);
	
	m_pRot->Register(rpid, *ppunk);

	return S_OK;
}

HRESULT CMainRun::DestroyRotPlugin(const CLSID& rpid)
{
	retrtpv(rpid != GUID_NULL, E_FAIL);
	retrtpv(m_pRot, E_FAIL);
	
	return m_pRot->Revoke(rpid);
}

HRESULT CMainRun::Install()
{
	
	return S_OK;
}

HRESULT CMainRun::Uninstall()
{
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CMainRun::ServerRun()
{
	return S_OK;
}

HRESULT CMainRun::StartServer()
{
	return S_OK;
}

HRESULT CMainRun::ApplicationRun()
{
	return MainRun();
}
void CMainRun::OnSvcMain(DWORD dwArgc, LPSTR *lpszArgv)
{
	
}

void CMainRun::OnServiceCtrl(DWORD dwCtrlCode)
{
	
}

BOOL CMainRun::ReportStatusToSCMgr(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint)
{
	return FALSE;
}

HRESULT CMainRun::MainRun()
{
	HRESULT hr = StartPlugins();	
	hr = StopPlugins();
	return hr;
}
