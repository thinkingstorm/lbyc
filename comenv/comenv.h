#ifndef _COMENV_H_ 
#define _COMENV_H_

#pragma once
#include "stdafx.h"

#include <data/iinfoanalsis.h>

class ComEnv :		  public IComEnv
					, public IExit
					, public CUnknownImp 
{
public:
	ComEnv(void);
	~ComEnv(void);
	UNKNOWN_IMP3_(IComEnv, IObjectRun, IExit);

	std_method(init_class)(IModuleBase* prot, IModuleBase* punkOuter);

	//IObjectRun
	std_method(Init)(HINSTANCE hInstance
		, LPCTSTR lpCfgName
		, int iType);

	std_method_(INT, Run)();
	std_method(Uninit)();


	std_method(InitEnv)(bool bUseEnumObject	
		, HINSTANCE hInstance = NULL
		, LPCTSTR lpCfgFile = NULL
		, LPCTSTR lpInfoAnalysisLib = NULL
		, LPCTSTR lpComModuleFile = NULL
		);
	std_method_(INT, RunEnv)(const CLSID& mainPlugin);

	std_method(GetRot)(IModuleBase** pRot, IID iid = re_uuidof(IComRunningObjectTable));	
	std_method(GetObjectLoader)(IModuleBase** pRot, IID iid = re_uuidof(IObjectLoader));

	std_method_(LPCTSTR, GetXmlFile)();
	std_method_(LPCTSTR, GetXmlLib)();
	std_method_(LPCTSTR, GetRunPath)();
	std_method_(LPCTSTR, GetProcessName)();

	std_method(NotifyExit)(bool* bExit = NULL);
private:
	HINSTANCE							m_hInstance;
	tstring								m_strCfgFile;
	tstring								m_strAnalysiLib;
	tstring								m_strRunPath;
	tstring								m_strProcessName;

private:
	_lComPtr<IOLManager>				m_pOlManager;
	_lComPtr<IComRunningObjectTable>	m_pRot;
	_lComPtr<IModuleBase>				m_pMainPlugin;
	

	CLSID	m_MainPlugin;	
private:
	struct  clsidNode
	{
		CLSID			clisd;
		unsigned long	ulStart;
		char			szParam[PARAMBUFSIZE+1];
		int				iUiPulgin;
		char			szName[NAMEBUFSIZE+1];
		clsidNode()
		{
			clisd		=	GUID_NULL;
			ulStart		=	-1;
			memset(szParam,0,PARAMBUFSIZE+1);
			memset(szName,0,NAMEBUFSIZE+1);
			iUiPulgin	=	0;
		}
		clsidNode(CLSID	csd,unsigned long ulindex,const char *pszParam,int iUi,const char* pszName)
		{
			if (pszName != NULL)
			{
				string_strcpy(szParam,pszParam);
			}
			if (pszName != NULL)
			{
				string_strcpy(szName,pszName);
			}
			clisd		=	csd;
			ulStart		=	ulindex;
			iUiPulgin	=	iUi;

		}

	};
	list<clsidNode>		m_listClsid;


	HRESULT	loadOlAndRot();
	HRESULT	CreatePluginObject(CLSID csPulgin,IModuleBase** pModuleBase);
	HRESULT	loadConfigModule(bool bUseEnumObject);


	HRESULT	LoadProjectSetting();

	HRESULT	RegisterModule(const TCHAR* pCompoents_path);

	HRESULT	InsertCacheList(char* pClsid,
									char* pName,
									char* pParam,
									char* pUi,
									char* pStart);
	HRESULT	SubMitPulgin();



	bool	getModuleInfo(HINSTANCE hInstance);
	bool	initEnvConfig(LPCTSTR lpCfgName, LPCTSTR lpXmlLib, LPCTSTR lpAnalysiscomFile);
	tstring	GetFileFullPath(LPCTSTR lpFile);



	////////////////////////////////////////////////////////////////////////////////////////////


	HRESULT	LoadComConfig(IInfoAnalysis* pAnalysis, bool bUseEnumObject);
	HRESULT	LoadBasecom(InfoRoot* pRoot,InfoNode pCommodule);
	HRESULT	LoadMaincom(InfoRoot* pRoot, InfoNode pCommodule);

	HRESULT	LoadComNode(InfoRoot* pRoot, InfoNode pCommodule,
					char**	pComponents_path,
					int*	pClsidinclude);

	HRESULT	LoadMainPulgin(InfoRoot* pRoot, InfoNode pCommodule);



	HRESULT	LoadComClsidNodeBase(InfoRoot* pRoot, InfoNode pCommodule,
					char** pClsid,
					char** pName,
					char** pParam,
					char** pUi,
					char** pStart);



};
#endif
