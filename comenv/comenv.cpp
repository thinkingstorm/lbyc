#include "stdafx.h"
#include "comenv.h"

#define RC_RUNERROR	-1




#ifdef _MSC_VER
#define DEFAULT_ANALYSISLIB		_T("\\InfoAnalysis.dll")
#define ENVCOM					_T("\\ComEnv.dll")

#elif __GNUC__

#define DEFAULT_ANALYSISLIB		_T("//libinfoanalysis.so")
#define ENVCOM					_T("//libcomenv.so")

#endif // __GNUC__





#define DEFAULT_MAINCONFIG		_T("MainModuleConfig.json")



#include <compat/getpath.hpp>


ComEnv::ComEnv(void):m_hInstance(NULL)
{
	m_MainPlugin = GUID_NULL;
}

ComEnv::~ComEnv(void)
{
	Uninit();
}

std_method_impl ComEnv::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	return !punkOuter ? S_OK : E_INVALIDARG;
}



std_method_impl ComEnv::Init(HINSTANCE hInstance /* = NULL*/
				, LPCTSTR lpCfgName/* = NULL*/
				, int iType/* = NULL*/)

{
	if (iType == 0)
	{
		return InitEnv(false, hInstance, lpCfgName, NULL, NULL);
	}
	return E_FAIL;
}

std_method_impl ComEnv::InitEnv(bool bUseEnumObject
					  , HINSTANCE hInstance/* = NULL*/ 
					  , LPCTSTR lpCfgFile/* = NULL*/
					  , LPCTSTR lpInfoAnalysisLib /* = NULL*/
					  , LPCTSTR lpComModuleFile /* = NULL*/
					  )
{

	m_hInstance = hInstance;
	retrtp(getModuleInfo(m_hInstance), E_FAIL);
	retrtp(initEnvConfig(lpCfgFile, lpInfoAnalysisLib, lpComModuleFile), E_FAIL);
	return loadConfigModule(bUseEnumObject);
}

std_method_type_impl(INT) ComEnv::Run()
{
	return RunEnv(m_MainPlugin);
}
HRESULT ComEnv::CreatePluginObject(CLSID csPulgin,IModuleBase** pModuleBase)
{
	HRESULT hr	=	S_OK;
		
	retrtpv(csPulgin != GUID_NULL, E_FAIL);

 	_lComPtr<IObjectLoader> pObejctLoader(m_pOlManager);
	retrtpv(pObejctLoader, E_FAIL);

	hr = pObejctLoader->CreateInstance(m_pRot, m_MainPlugin, NULL, re_uuidof(IModuleBase), (void**)pModuleBase);
	if(FAILED(hr))
	{
		return E_FAIL;
	}

	return hr;
}
HRESULT	ComEnv::SubMitPulgin()
{
	HRESULT hr	=	S_OK;
	list<clsidNode>::iterator it	=	m_listClsid.begin();
	int nSize = m_listClsid.size();
	retrtpv(nSize > 0, S_OK);
	retrtpv(m_pMainPlugin,E_FAIL);

	
	_lComPtr<IPluginObjectMgr> pPulginObjectMgr(m_pMainPlugin);
	retrtpv(pPulginObjectMgr,E_FAIL);

	while(it != m_listClsid.end())
	{
		hr	=	pPulginObjectMgr->CreateObject((*it).clisd,(*it).ulStart,(*it).iUiPulgin,(*it).szParam);
		if (hr != S_OK)
		{
			return E_FAIL;
		}
		it++;
	}
	return hr;
}
std_method_type_impl(INT) ComEnv::RunEnv(const CLSID& mainPlugin)
{
	INT nRc = RC_RUNERROR;
	HRESULT hr	=	S_OK;
	
	retrtpv(mainPlugin != GUID_NULL, nRc);
	retrtpv(m_pRot, nRc);
	m_MainPlugin = mainPlugin;	
	

	CreatePluginObject(m_MainPlugin,&m_pMainPlugin.m_p);
	_lComPtr<IObjectRun> pObjectRun(m_pMainPlugin);
	if(pObjectRun)
	{
		
	/*	pPulginObjectMgr->insert()*/
		

		_lComPtr<IOLManagerEx> pOlManagerEx(m_pOlManager);	

		//DWORD dwClisdCount	=	pOlManagerEx->GetComponentModuleCount();
 		hr = pObjectRun->Init(m_hInstance,NULL,1);
 		if(FAILED(hr))
 		{
 			pObjectRun->Uninit();
 			return nRc;
 		} 

		hr	=	SubMitPulgin();
		if(FAILED(hr))
		{
			return nRc;
		} 
		m_listClsid.clear();

 		m_pRot->Register(m_MainPlugin, m_pMainPlugin);

		nRc = pObjectRun->Run();

		pObjectRun->Uninit();
	}
 	else
 	{

 		_lComPtr<IMdPlugin> pRsPlugin(m_pMainPlugin);
 		if(!pRsPlugin)
 		{
 			return nRc;
 		}
 
 		hr = pRsPlugin->Init(NULL);
 		if(FAILED(hr))
 		{
 			pObjectRun->Uninit();
 			return nRc;
 		}
 
 		m_pRot->Register(m_MainPlugin, m_pMainPlugin);
 
 		_lComPtr<IMdPluginRun> pRsPluginRun(m_pMainPlugin);
 		if(pRsPluginRun)
 		{
 			nRc = pRsPluginRun->Start();
 			nRc = pRsPluginRun->Stop();
 		}
 		pRsPlugin->Uninit();
 	}

	return nRc;
}

std_method_impl ComEnv::Uninit()
{
	if(m_pRot)
	{
		m_pRot->RevokeAll();
		m_pRot = INULL;
	}

	if(m_pOlManager)
	{
		m_pOlManager->FreeUnusedLibraries();
		m_pOlManager = INULL;
	}

	return S_OK;
}

std_method_impl ComEnv::GetRot(IModuleBase** pRot, IID iid/* = __uuidof(IComRunningObjectTable)*/)
{
	retrtpv(m_pRot, E_NOINTERFACE);
	return m_pRot->QueryInterface(iid, (void**)pRot);
}

std_method_impl ComEnv::GetObjectLoader(IModuleBase** pRot, IID iid/* = __uuidof(IObjectLoader)*/)
{
	retrtpv(m_pOlManager, E_NOINTERFACE);
	return m_pOlManager->QueryInterface(iid, (void**)pRot);
}

std_method_type_impl(LPCTSTR) ComEnv::GetXmlFile()
{
	return m_strCfgFile.c_str();
}

std_method_type_impl(LPCTSTR) ComEnv::GetXmlLib()
{
	return m_strAnalysiLib.c_str();
}

std_method_type_impl(LPCTSTR) ComEnv::GetRunPath()
{
	return m_strRunPath.c_str();
}

std_method_type_impl(LPCTSTR) ComEnv::GetProcessName()
{
	return m_strProcessName.c_str();
}

std_method_impl ComEnv::NotifyExit(bool* bExit)
{
	retrtpv(m_pRot, E_INVALIDARG);
	_lComPtr<IExit> pExit;
	RFAILED(m_pRot->GetObject(m_MainPlugin, re_uuidof(IExit), (IModuleBase**)&pExit));
	retrtpv(pExit, E_INVALIDARG);

	return pExit->NotifyExit(bExit);
}

bool ComEnv::getModuleInfo(HINSTANCE hInstance)
{
#ifndef __GNUC__
		WCHAR szBuf[MAX_PATH * 2 + 1] = { 0x00 };
		::GetModuleFileNameW(hInstance, szBuf, MAX_PATH * 2);

		if (wstring_strlen(szBuf) <= 0)
			return false;

		tstring strBuf;
		strBuf.append(szBuf);

		size_t npos = strBuf.rfind(_T("\\"));

		m_strRunPath = strBuf.substr(0, npos);

		tstring strFullName = strBuf.substr(npos + 1);
		npos = strFullName.rfind(_T('.'));

		if (npos >= 0)
			m_strProcessName = strFullName.substr(0, npos);
		else
			m_strProcessName = strFullName;

#else

		char szBuf[MAX_PATH * 2 + 1] = { 0x00 };

		int npos = -1;

		int nCount = readlink("/proc/self/exe", szBuf, MAX_PATH * 2);
		if (nCount < 0 || nCount > MAX_PATH)
		{
			return false;
		}
		szBuf[nCount] = _T('0');
		
		if (string_strlen(szBuf) <= 0)
			return false;

		std::string strBuf;
		strBuf.assign(szBuf);
		npos = strBuf.find_last_of('/');
		m_strRunPath = strBuf.substr(0, npos);

		std::string strFullName = strBuf.substr(npos + 1);
		npos = strFullName.find_last_of(_T('.'));
		if (npos >= 0)
			m_strProcessName = strFullName.substr(0, npos);
		else
			m_strProcessName = strFullName;
#endif

	return true;
}

bool ComEnv::initEnvConfig(LPCTSTR lpCfgName, LPCTSTR lpXmlLib, LPCTSTR lpAnalysiscomFile)
{

	if (lpXmlLib == NULL)
	{
		m_strAnalysiLib = GetFileFullPath(DEFAULT_ANALYSISLIB);
	}
	if (lpCfgName == NULL)
	{
		 m_strCfgFile = GetFileFullPath(DEFAULT_MAINCONFIG);
	}
	else
		m_strCfgFile = lpCfgName;

	
	if (FAILED(loadOlAndRot()))
		return false;

	return true;
}

HRESULT ComEnv::loadOlAndRot()
{
	_lComPtr<IComObjectFrameworkClassFactory> pClassFactory;

	HRESULT hr = E_FAIL;

	hr = DllGetClassObject(CLSID_CObjectLoader, re_uuidof(IComObjectFrameworkClassFactory), (void**)&pClassFactory);
	RFAILED(hr);
	retrtpv(pClassFactory, E_FAIL);

	hr = pClassFactory->CreateInstance(NULL, NULL, re_uuidof(IOLManager), (void**)&m_pOlManager);
	RFAILED(hr);
	retrtpv(m_pOlManager, E_FAIL);

	pClassFactory = INULL;
	//////////////////////////////////////////////////////////////////////////
	hr = DllGetClassObject(ClSID_CRunningObjectTable, re_uuidof(IComObjectFrameworkClassFactory), (void**)&pClassFactory);
	RFAILED(hr);
	retrtpv(pClassFactory, E_FAIL);

	hr = pClassFactory->CreateInstance(NULL, NULL, re_uuidof(IComRunningObjectTable), (void**)&m_pRot);
	RFAILED(hr);
	retrtpv(m_pRot, E_FAIL);

	_lComPtr<IModuleBase> pUnknown(m_pOlManager);
	if(pUnknown)
		RFAILED(m_pRot->Register(CLSID_CObjectLoader, pUnknown));

	_lComPtr<IModuleBase> pUnknownEnv(this);
	if(pUnknownEnv)
		RFAILED(m_pRot->Register(CLSID_ComEnv, pUnknownEnv));

	tstring strComEnv = m_strRunPath + ENVCOM;

	m_pOlManager->Register(CLSID_CObjectLoader, strComEnv.c_str(), (LPVOID)DllGetClassObject);
	m_pOlManager->Register(ClSID_CRunningObjectTable, strComEnv.c_str(), (LPVOID)DllGetClassObject);
	m_pOlManager->Register(CLSID_CMainRun, strComEnv.c_str(), (LPVOID)DllGetClassObject);
	m_pOlManager->Register(CLSID_CProperty, strComEnv.c_str(), (LPVOID)DllGetClassObject);
	m_pOlManager->Register(CLSID_CProperty_thread, strComEnv.c_str(), (LPVOID)DllGetClassObject);
	m_pOlManager->Register(CLSID_CProperty2, strComEnv.c_str(), (LPVOID)DllGetClassObject);
	m_pOlManager->Register(CLSID_CProperty2_thread, strComEnv.c_str(), (LPVOID)DllGetClassObject);

	return S_OK;
}

tstring ComEnv::GetFileFullPath(LPCTSTR lpFile)
{
	tstring strFullPath;

	return strFullPath;

}

HRESULT ComEnv::loadConfigModule(bool bUseEnumObject)
{
	HRESULT hr	=	S_OK;
	
	CComLoader xmlLoader;
	_lComPtr<IInfoAnalysis> pInfoAnalysis;

	tstring curpath = GetCurrentRunPath(m_hInstance);

	curpath += DEFAULT_ANALYSISLIB;

	BOOL bLoad = xmlLoader.LoadCom(curpath.c_str());
	if(!bLoad)
	{
		return FALSE;
	}
	else
	{
		
		HRESULT hr = xmlLoader.CreateInstance(CLSID_InfoAnalysis, NULL, NULL, re_uuidof(IInfoAnalysis), (void**)&pInfoAnalysis.m_p);
		if(FAILED(hr) || INULL == pInfoAnalysis)
		{
			return FALSE;
		}
		hr	=	LoadComConfig(pInfoAnalysis,bUseEnumObject);
	}

	return hr;
}
HRESULT ComEnv::InsertCacheList(char* pClsid, char* pName, char* pParam, char* pUi, char* pStart)
{
	HRESULT hr	=	S_OK;
	retrtpv(pClsid,E_FAIL);
	
	
	CLSID id	=	S2GUIDA(pClsid);
	
	int iUi		=	0;
	unsigned long  iStart	=	0;


	if (pUi	!=	NULL)
	{
		iUi	=	atoi(pUi);

	}
	if (pStart != NULL)
	{
		iStart	=	atol(pStart);
	}

	m_listClsid.push_back(clsidNode(id,iStart,pParam,iUi,pName));

	return hr;
}


HRESULT ComEnv::RegisterModule(const TCHAR* pCompoents_path)
{
	retrtpv(pCompoents_path,E_FAIL);
	HRESULT hr	=	S_OK;


	tstring stringpath = GetCurrentRunPath(m_hInstance);

#ifdef _MSC_VER
	stringpath += _T("\\");
#elif __GNUC__
	stringpath += _T("//");
#endif // __GNUC__


	stringpath +=	pCompoents_path;

	CComLoader comLoader;
	BOOL bLoad = comLoader.LoadCom(stringpath.c_str());
	if(!bLoad)
	{
		return E_FAIL;
	}
	LONG lCount = comLoader.GetCount();
	if(lCount <= 0)
	{
		return E_FAIL;
	}
	retrtpv(m_pOlManager,E_FAIL);
	_lComPtr<IOLManagerEx> pOlManagerEx(m_pOlManager);
	
	LONG lplugin	=	0;
	for( lplugin = 0; lplugin < lCount; lplugin++)
	{
		CLSID clsid = comLoader.GetAt(lplugin);
		LPCSTR lpProgId = comLoader.ProgIDFromCLSID(clsid);
		m_pOlManager->Register(clsid, stringpath.c_str());
		if(pOlManagerEx && lpProgId && *lpProgId)
			pOlManagerEx->SetProgId(clsid, lpProgId);
	}

	return hr;
}

HRESULT ComEnv::LoadComConfig(IInfoAnalysis* pAnalysis, bool bUseEnumObject)
{
	HRESULT hr = S_OK;

	if (pAnalysis != INULL)
	{
		InfoRoot*	pRoot = NULL;
		RFAILED(pAnalysis->NewLoadFileObject(m_strCfgFile.c_str(), (IModuleBase**)&pRoot));
		if (hr != S_OK)
		{
		}
		if (pRoot != NULL)
		{
			InfoNode	pProjectSettingRoot		= NULL;
			InfoNode	pClientModuleRoot		= NULL;
			InfoNode	pRootNode				= NULL;
			pRoot->GetRootNode(&pRootNode);
			retrtpv(pRootNode, E_FAIL);
			pRoot->GetNode(pRootNode, "commodule", &pClientModuleRoot);
			retrtpv(pClientModuleRoot, E_FAIL);
			pRoot->GetNode(pRootNode, "projectsetting", &pProjectSettingRoot);
			retrtpv(pProjectSettingRoot, E_FAIL);
			RFAILED(LoadMaincom(pRoot, pClientModuleRoot));
			RFAILED(LoadBasecom(pRoot, pClientModuleRoot));
		}

		pAnalysis->DelObject(pRoot);

	}
	else
		return E_FAIL;


	return hr;
}

HRESULT ComEnv::LoadBasecom(InfoRoot* pRoot, InfoNode pCommodule)
{

	retrtpv(pRoot, E_FAIL);
	retrtpv(pCommodule, E_FAIL);
	InfoNode pioBaseCom = NULL;
	pRoot->GetNode(pCommodule, "basecom", &pioBaseCom);
	retrtpv(pioBaseCom, E_FAIL);


	unsigned long ulBaseComCount = 0;
	int Count = pRoot->GetNodeCount(pioBaseCom, &ulBaseComCount);
	int uloop = 0;
	for (uloop = 0; uloop < Count; uloop++)
	{

		retrtpv(pioBaseCom, E_FAIL);
		char *pComponentPath = NULL;
		int ulCount = 0;
		InfoNode	pBaseComNode = NULL;
		pRoot->GetNodeIndexNode(pioBaseCom, uloop, &pBaseComNode);
		InfoNode pBaseComClsidNode = NULL;
		pRoot->GetNode(pBaseComNode, "clsidinclude", &pBaseComClsidNode);

		retrtpv(pBaseComClsidNode, E_FAIL);
		LoadComNode(pRoot, pBaseComNode, &pComponentPath, &ulCount);
		int uloop = 0;
		for (uloop = 0; uloop < ulCount; uloop++)
		{
			char *pClsid = NULL;
			char *pName = NULL;
			char *pParam = NULL;
			char *pUI = NULL;
			char *pStart = NULL;
			InfoNode pClsidNode = NULL;

			pRoot->GetNodeIndexNode(pBaseComClsidNode, uloop, &pClsidNode);
			retrtpv(pClsidNode, E_FAIL);
			LoadComClsidNodeBase(pRoot, pClsidNode, &pClsid, &pName, &pParam, &pUI, &pStart);

			RFAILED(InsertCacheList(pClsid, pName, pParam, pUI, pStart));

			retrtpv(pName, E_FAIL);
		}
		if (pComponentPath[0] != 0 && ulCount != 0)
		{

#ifdef _MSC_VER
			int sSize = string_strlen(pComponentPath);
			sentry<wchar_t*, default_array_sentry> dBuf;
			int dSize = mbstowcs(dBuf, pComponentPath, 0) + 1;
			dBuf = new wchar_t[dSize];
			wmemset(dBuf, 0, dSize);
			int nRet = mbstowcs(dBuf, pComponentPath, sSize);
			RegisterModule(dBuf);
#elif __GNUC__
			RegisterModule(pComponentPath);
#endif // MSC_VER
		}
		else
		{
			return E_FAIL;
		}
	}
	return S_OK;
}
HRESULT ComEnv::LoadMaincom(InfoRoot* pRoot, InfoNode pCommodule)
{

	retrtpv(pRoot, E_FAIL);
	retrtpv(pCommodule, E_FAIL);
	InfoNode pioMainCom = NULL;
	pRoot->GetNode(pCommodule, "maincom", &pioMainCom);
	retrtpv(pioMainCom, E_FAIL);
	char *pComponentPath = NULL;
	int ulCount = 0;

	LoadComNode(pRoot, pioMainCom, &pComponentPath, &ulCount);

	if (ulCount != 1)
	{
		return E_FAIL;
	}


	InfoNode pioMainComClsidNode = NULL;
	pRoot->GetNode(pioMainCom, "clsidinclude", &pioMainComClsidNode);
	int uloop = 0;
	for (uloop = 0; uloop < ulCount; uloop++)
	{
		char *pClsid = NULL;
		char *pName = NULL;
		char *pParam = NULL;
		char *pUI = NULL;
		char *pStart = NULL;

		InfoNode pClsidNode = NULL;
		pRoot->GetNodeIndexNode(pioMainComClsidNode, uloop, &pClsidNode);
		retrtpv(pClsidNode, E_FAIL);
		LoadComClsidNodeBase(pRoot, pClsidNode, &pClsid, &pName, &pParam, &pUI, &pStart);
		retrtpv(pName, E_FAIL);

		if (string_stricmp(pName, "main") == 0)
		{
			if (pClsid != NULL)
			{
				m_MainPlugin = S2GUIDA(pClsid);
			}
		}
	}

	if (pComponentPath != NULL)
	{
#ifdef _MSC_VER
		int sSize = string_strlen(pComponentPath);
		sentry<wchar_t*, default_array_sentry> dBuf;
		int dSize = mbstowcs(dBuf, pComponentPath, 0) + 1;
		dBuf = new wchar_t[dSize];
		wmemset(dBuf, 0, dSize);
		int nRet = mbstowcs(dBuf, pComponentPath, sSize);
		RegisterModule(dBuf);
#elif __GNUC__
		RegisterModule(pComponentPath);
#endif // MSC_VER


	}
	else
	{
		return E_FAIL;
	}





	return S_OK;
}

HRESULT	ComEnv::LoadComNode(InfoRoot* pRoot, InfoNode pCommodule,
						char**	pComponents_path,
						int*	pClsidinclude)
{
	retrtpv(pRoot, E_FAIL);
	retrtpv(pCommodule, E_FAIL);
	HRESULT hr = S_OK;

	*pComponents_path = (char*)pRoot->GetStringValue(pCommodule, "components_path");
	retrtpv(pComponents_path, E_FAIL);

	InfoNode pClsidincludeNode = NULL;
	pRoot->GetNode(pCommodule, "clsidinclude", &pClsidincludeNode);
	retrtpv(pClsidincludeNode, E_FAIL);

	unsigned long ulClsidCount = 0;
	*pClsidinclude = pRoot->GetNodeCount(pClsidincludeNode, &ulClsidCount);
	return hr;
}

HRESULT ComEnv::LoadMainPulgin(InfoRoot* pRoot, InfoNode pCommodule)
{
	return S_OK;
}









///

HRESULT	ComEnv::LoadComClsidNodeBase(InfoRoot* pRoot, InfoNode pCommodule,
						char** pClsid,
						char** pName,
						char** pParam,
						char** pUi,
						char** pStart)
{
	retrtpv(pRoot, E_FAIL);
	retrtpv(pCommodule, E_FAIL);
	HRESULT hr = S_OK;


	*pClsid = (char*)pRoot->GetStringValue(pCommodule, "clsid");
	retrtpv(pClsid, E_FAIL);

	*pName	= (char*)pRoot->GetStringValue(pCommodule, "name");
	retrtpv(pName, E_FAIL);

	*pParam = (char*)pRoot->GetStringValue(pCommodule, "param");

	*pUi	= (char*)pRoot->GetStringValue(pCommodule, "ui");

	*pStart = (char*)pRoot->GetStringValue(pCommodule, "start");

	return hr;
}

