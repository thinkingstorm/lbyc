#ifndef _ICOMBASE_H_
#define _ICOMBASE_H_

#include <dlcom/byunknown.hpp>

namespace by {

//////////////////////////////////////////////////////////////////////////
interface IObjectLoader : public IModuleBase
{
	std_method(CreateInstance)(IModuleBase* prot, const CLSID& rclsid, IModuleBase *punkOuter, const IID& riid, void **ppv) = 0;
};
MD_DEFINE_IID(IObjectLoader, "{1C97345C-7834-4218-8BA8-C0E04F642118}");

interface IObjectLoaderEx : public IObjectLoader
{
	std_method_(LPCSTR, ProgIDFromCLSID)(REFCLSID clsid) = 0;
	std_method_(CLSID, CLSIDFromProgID)(LPCSTR lpProgId) = 0;
};
MD_DEFINE_IID(IObjectLoaderEx, "{F2527941-9539-44f9-AABE-A2A325274C92}");

interface IOLManager : public IModuleBase
{
public:
	std_method(Register)(const CLSID& rclsid, LPCTSTR filename, LPVOID lpGetProc = NULL) = 0;
	std_method(Revoke)(const CLSID& rclsid) = 0;
	std_method(FreeUnusedLibraries)() = 0;
	std_method(IsComponentValid)() = 0;
	std_method(IsLibValid)() = 0;
	std_method_(DWORD, GetComponentModuleNames)(DWORD count, const char **ppreceive) = 0;
	std_method_(DWORD, GetComponentModuleCount)() = 0;

};
MD_DEFINE_IID(IOLManager, "{E00AD446-D124-40f8-9397-D3D8425F3235}");

interface IOLManagerEx : public IOLManager
{
public:
	std_method(SetProgId)(const CLSID& rclsid, LPCSTR progId) = 0;
};
MD_DEFINE_IID(IOLManagerEx, "{844335FE-289B-4117-8CC1-B3E27E2621D3}");

// {4F496E7F-D8FD-4ded-967D-C4F53BFB9452}
MD_DEFINE_GUID(CLSID_CObjectLoader, 
	0x4f496e7f, 0xd8fd, 0x4ded, 0x96, 0x7d, 0xc4, 0xf5, 0x3b, 0xfb, 0x94, 0x52);

//////////////////////////////////////////////////////////////////////////
interface IComRunningObjectTable : public IModuleBase
{	
public:
	std_method(Register)(const CLSID& rpid, IModuleBase *punk) = 0;
	std_method(Revoke)(const CLSID& rpid) = 0;
	std_method(IsRunning)(const CLSID& rpid) = 0;
	std_method(GetObject)(const CLSID& rpid, const IID iid, IModuleBase **ppunk) = 0;
	std_method(RevokeAll)() = 0;
};
MD_DEFINE_IID(IComRunningObjectTable, "{50EAFCD5-FF5B-4744-9C3C-980A521A5DF3}");

interface IComRunningObjectTableEx : public IComRunningObjectTable
{
public:
	std_method_(LPCSTR, ProgIDFromCLSID)(REFCLSID clsid) = 0;
	std_method_(CLSID, CLSIDFromProgID)(LPCSTR lpProgId) = 0;

	std_method_(UINT, GetObjectCount)() = 0;
	std_method(BeginEnum)() = 0;
	std_method_(BOOL, NextObject)(CLSID *pclsId) = 0;
};
MD_DEFINE_IID(IComRunningObjectTableEx, "{81079861-0A53-4820-8C73-7FC9F118EB02}");

// {216DFF2F-B2F0-4ce0-BA5B-72E0B7BFAC28}
MD_DEFINE_GUID(ClSID_CRunningObjectTable, 
	0x216dff2f, 0xb2f0, 0x4ce0, 0xba, 0x5b, 0x72, 0xe0, 0xb7, 0xbf, 0xac, 0x28);

//////////////////////////////////////////////////////////////////////////
interface IObjMgr : public IModuleBase
{
public:
	std_method(CreateInstance)(const CLSID& rpid, const IID& riid, IModuleBase *punk, BOOL bFromRot) = 0;
	std_method(ReleaseInstanceFromRot)(const CLSID& rpid) = 0;
};

//////////////////////////////////////////////////////////////////////////
interface IExit : public IModuleBase
{
	std_method(NotifyExit)(bool* bExit = NULL) = 0;
};
MD_DEFINE_IID(IExit, "{AFFA4FB2-EFF6-4371-AADD-62C0B0766178}");

interface IObjectRun : public IModuleBase
{
	std_method(Init)(HINSTANCE hInstance = NULL
		, LPCTSTR lpCfgName = NULL
		, int iType = 0) = 0;
	std_method_(INT, Run)() = 0;		
	std_method(Uninit)() = 0;
};
MD_DEFINE_IID(IObjectRun, "{616C6DD6-95C9-4837-A2AE-939B52515F6D}");


interface IComEnv : public IObjectRun
{
	std_method(InitEnv)(bool bUseEnumObject	
		, HINSTANCE hInstance			= NULL
		, LPCTSTR lpCfgFile				= NULL
		, LPCTSTR lpInfoAnalysisLib		= NULL
		, LPCTSTR lpComModuleFile		= NULL
		) = 0;


	std_method_(INT, RunEnv)(const CLSID& mainPlugin) = 0;

	std_method(GetRot)(IModuleBase** pRot, IID iid = re_uuidof(IComRunningObjectTable)) = 0;
	std_method(GetObjectLoader)(IModuleBase** pRot, IID iid = re_uuidof(IObjectLoader)) = 0;

	std_method_(LPCTSTR, GetXmlFile)() = 0;
	std_method_(LPCTSTR, GetXmlLib)() = 0;
	std_method_(LPCTSTR, GetRunPath)() = 0;
	std_method_(LPCTSTR, GetProcessName)() = 0;
};
MD_DEFINE_IID(IComEnv, "{50D6F56E-9C94-4060-B6EC-CF71CCB25CAA}");

#define PARAMBUFSIZE	64
#define NAMEBUFSIZE		32
interface IPluginObjectMgr : public IModuleBase
{
	std_method(CreateObject)(const CLSID& clsid,	
		unsigned long  ulIndex,
		int		 iUi,
		const char* pszParam)														PURE;
	std_method(RemoveObject)(const CLSID& clsid)									PURE;

};
// {3F36891F-2BF6-4802-9A00-677CB423305A}
MD_DEFINE_IID(IPluginObjectMgr,"{3F36891F-2BF6-4802-9A00-677CB423305A}");


// {E59BC62D-64AB-439d-BAF3-B2D1BA15E441}
MD_DEFINE_GUID(CLSID_ComEnv,
			0xe59bc62d, 0x64ab, 0x439d, 0xba, 0xf3, 0xb2, 0xd1, 0xba, 0x15, 0xe4, 0x41);

// {C8CA7580-8E65-49e6-A66A-B087C7EF523D}
MD_DEFINE_GUID(CLSID_CMainRun, 
			0xc8ca7580, 0x8e65, 0x49e6, 0xa6, 0x6a, 0xb0, 0x87, 0xc7, 0xef, 0x52, 0x3d);

//////////////////////////////////////////////////////////////////////////
interface IServerInfo : public IModuleBase
{

	std_method_(BOOL, IsServerRun)() = 0;
	std_method_(LPCTSTR, GetServerName)() = 0;
	std_method_(LPCTSTR*, GetServerArg)(DWORD *pdwArgc) = 0;
};
MD_DEFINE_IID(IServerInfo, "{0332DE3F-1D6C-44c9-9158-8C9DF220B41F}");

interface IServiceCtrlConnectPoint : public IModuleBase	
{
	std_method_(DWORD, OnServiceCtrl)(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData, LPVOID lpContext) = 0;
};
MD_DEFINE_IID(IServiceCtrlConnectPoint, "{88E3C375-B6EA-4dd8-8C4E-FE00689AD25A}");

}

#endif 
