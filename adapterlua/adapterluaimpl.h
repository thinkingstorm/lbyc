#ifndef _ASYNIOIMPL_H_
#define _ASYNIOIMPL_H_

#include "stdafx.h"
#include <adapter/ilua.h>
#include <compat/getpath.hpp>

extern "C"  
{  
	#include <lua5.1/lua.h>  
	#include <lua5.1/lualib.h>  
	#include <lua5.1/lauxlib.h> 
}

class CAdapterluaImpl : 	public	IAdapterLua,
							public  IMdPlugin,
							public  IMdPluginRun,
							public	CUnknownImp
{
public:
	CAdapterluaImpl(void);
	virtual ~CAdapterluaImpl(void);
	

	UNKNOWN_IMP3_(IMdPlugin, IMdPluginRun,IAdapterLua);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	std_method_impl init_class(IModuleBase* prot, IModuleBase* punkOuter);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	std_method(Init)(void*);
	std_method(Uninit)();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	std_method(Start)();
	std_method(Stop)();

	//////////////////////////////////////////////////////////////////////////
	std_method(RunFile)(const char* file);
	//////////////////////////////////////////////////////////////////////////
private:
	_lComPtr<IComRunningObjectTable>	m_pRot;
private:

	struct lua_sentry
	{
		static lua_State* default_value()
		{
			return 0;
		}
		template<class _Ptr> static bool equal_to(_Ptr l, _Ptr r)
		{
			return l == r;
		}
		template<class _Ptr> static void destroy(_Ptr p)
		{
			if (p != 0)
			{ 
				lua_close(p);
				p = 0;
			}
		}
	};
	sentry<lua_State* , lua_sentry> pLuaInstance;

};
#endif