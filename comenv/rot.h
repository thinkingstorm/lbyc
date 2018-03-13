#ifndef _ROT_H_
#define _ROT_H_

#include "stdafx.h"
#include <dlcom/icombase.h>

class CRot : public IComRunningObjectTableEx, private CUnknownImp
{
public:
	CRot(void);
	~CRot(void);

	UNKNOWN_IMP2(IComRunningObjectTableEx, IComRunningObjectTable);
	
	std_method_impl init_class(IModuleBase *prot, IModuleBase *punkOuter);

public: 
	// ISrvRunningObjectTable:
	std_method(Register)(const GUID& rpid, IModuleBase *punk);
	std_method(Revoke)(const GUID& rpid);
	std_method(IsRunning)(const GUID& rpid);
	std_method(GetObject)(const GUID& rpid, const IID iid, IModuleBase **ppunk);
	std_method(RevokeAll)();
	std_method(RegisterCreateInterface)(const GUID& rpid, const CLSID& clsid,const IID& iid);

	//IRscomRunningObjectTableEx
	std_method_(LPCSTR, ProgIDFromCLSID)(REFCLSID clsid);
	std_method_(CLSID, CLSIDFromProgID)(LPCSTR lpProgId);

	std_method_(UINT, GetObjectCount)();
	std_method(BeginEnum());
	std_method_(BOOL, NextObject)(CLSID *pclsId);

private:
	typedef struct tagRunningTableItem
	{
		DWORD dwInitMark;
		CLSID clsid;
		IID	  iid;
		_lComPtr<IModuleBase> m_ptr;
	}
	RUNNINGTABLEITEM;
	

	typedef std::map<GUID, RUNNINGTABLEITEM , memless<CLSID> > OBJMAP;

	OBJMAP m_map;
	OBJMAP::const_iterator m_itEnum;
};
#endif