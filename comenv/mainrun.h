#ifndef _MAINRUN_H_ 
#define _MAINRUN_H_

#include "stdafx.h"

template<class _Ty>
class SORT_LIST : public std::vector<_Ty>
{
public:
	typedef std::vector<_Ty> _base;
	void push_back(const _Ty& _Val)
	{
		if(_base::size() > 0)
		{
			push_back_sort(_Val);
		}
		else
		{
			_base::push_back(_Val);
		}
	}

	void push_back_sort(const _Ty& _Val)
	{
		typename _base::iterator _it = _base::begin();
		for(; _it != _base::end(); _it++)
		{
			if(_Val < *_it)
			{
				_base::insert(_it, _Val);
				return;
			}
		}

		if(_it == _base::end())
		{
			_base::push_back(_Val);
		}
	}

};

class CMainRun : public IObjectRun
	, public IPluginObjectMgr
	, public IExit
	, public IServerInfo
	, public CUnknownImp
{
public:
	CMainRun(void);
	virtual ~CMainRun(void);

	UNKNOWN_IMP4_(IObjectRun, IExit, IServerInfo,IPluginObjectMgr);

	std_method(init_class)(IModuleBase* prot, IModuleBase* punkOuter);

	std_method(Init)(HINSTANCE hInstance
		, LPCTSTR lpCfgXMLName
		, int iType);
	std_method_(INT, Run)();
	std_method(Uninit)();

	std_method(NotifyExit)(bool* bExit);

	std_method_(BOOL, IsServerRun)();

	std_method_(LPCTSTR, GetServerName)();

	std_method_(LPCTSTR*, GetServerArg)(DWORD *pdwArgc);


	std_method(CreateObject)(const CLSID& clsid,	
		unsigned long  ulIndex,
		int		 iUi,
		const char* pszParam);
	std_method(RemoveObject)(const CLSID& clsid);

	enum RUN_MODE
	{
		RM_NULL,
		RM_SYSTEM,			
		RM_SERVICE,			
		RM_APPLICATION		
	};

private:
	HINSTANCE		m_hInstance;
	string			m_strCfgXMLName;	
	string			m_strXmlFile;

	_lComPtr<IObjectLoader>				m_pObjLoader;	
	_lComPtr<IComRunningObjectTable>	m_pRot;			

	CLSID		m_clsMainPlugin;		
	//////////////////////////////////////////////////////////////////////////
	typedef std::vector<CLSID> PLUGIN_LIST;
	PLUGIN_LIST m_initList;		

	typedef struct _ST_PLUGIN  
	{
		DWORD	nIndex;
		CLSID	clsId;
		int		iUIPulgin;
		char	szParam[PARAMBUFSIZE+1];

		_ST_PLUGIN()
		{
			nIndex		= -1;
			clsId		= GUID_NULL;
			iUIPulgin	= 0;
			memset(szParam,0,PARAMBUFSIZE+1);
		}

		_ST_PLUGIN(int n, CLSID guid, int iUI,const char* pszParam)
		{
			nIndex		= n;
			clsId		= guid;
			iUIPulgin	= iUI;
			string_strcpy(szParam,pszParam);			
		}

		bool operator>(const _ST_PLUGIN &it) const
		{
			return nIndex > (it.nIndex);
		}

		bool operator <(const _ST_PLUGIN &it) const
		{
			return !(operator >(it));
		}
	}ST_PLUGIN;
	typedef SORT_LIST<ST_PLUGIN> SORTPLUGIN_LIST;
	SORTPLUGIN_LIST m_startList;	

private:
	HRESULT Install();
	HRESULT Uninstall();

	HRESULT ServerRun();
	HRESULT StartServer();
	HRESULT ApplicationRun();

	HRESULT MainRun();

	static CMainRun*	s_pRsSrv;



	static VOID WINAPI SvcMain(DWORD   dwNumServicesArgs,LPSTR  *lpServiceArgVectors);
	static VOID WINAPI ServiceCtrl(DWORD dwCtrlCode);

	VOID	OnSvcMain(DWORD   dwNumServicesArgs,LPSTR  *lpServiceArgVectors);
	VOID	OnServiceCtrl(DWORD dwCtrlCode);
	BOOL	ReportStatusToSCMgr(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);

	RUN_MODE	m_runMode;

	tstring		m_strSrvName;			
	tstring		m_strSrvDesc;			
	DWORD		m_dwControlsAccepted;	
	DWORD		m_dwStartType;
	DWORD		m_dwNumServicesArgs;
	LPCTSTR*	m_lpServiceArgVectors;

private:

	bool initEnv(LPCTSTR lpCfgXMLName, LPCTSTR lpXmlFile);
	void uninitEnv();
	CComLoader m_xmlLoader;
	HRESULT CheckCommandLine();
	HRESULT StartPlugins();
	HRESULT StopPlugins();
	
	HRESULT StartOrStopPlugins(bool bStart);
	HRESULT UninitPlugins();
	HRESULT	CreatePlugin(const CLSID& rpid);
	HRESULT CreateRotPlugin(const CLSID& rpid, IModuleBase **ppunk);
	HRESULT DestroyRotPlugin(const CLSID& rpid);
};
#endif