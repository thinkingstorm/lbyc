#include "adapterluaimpl.h"

CAdapterluaImpl::CAdapterluaImpl(void)
{
}

CAdapterluaImpl::~CAdapterluaImpl(void)
{
}
//////////////////////////////////////////////////////////////////////////
std_method_impl CAdapterluaImpl::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	HRESULT		hr	=	S_OK;
	if (prot != NULL)
	{
		m_pRot	=	prot;
	}
	return hr;
}
std_method_impl CAdapterluaImpl::Init(void*)
{
	HRESULT		hr	=	S_OK;
 
    

	return hr;
}
std_method_impl CAdapterluaImpl::Uninit()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAdapterluaImpl::Start()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAdapterluaImpl::Stop()
{
	HRESULT		hr	=	S_OK;
	return hr;
}

std_method_impl CAdapterluaImpl::RunFile(const char* file)
{
	HRESULT		hr = S_OK;



	pLuaInstance = luaL_newstate();



	tstring strpathlua = GetCurrentRunPath(NULL);


#ifndef __GNUC__
	strpathlua += _T("\\");
#else
	strpathlua += _T("//");
#endif

	strpathlua	+= _T("main.lua");

    int bRet = luaL_loadfile(pLuaInstance,strpathlua.c_str());  
    if(bRet)  
    {  
        cout<<"load file error"<<endl;  
        return hr;
    }

    bRet = lua_pcall(pLuaInstance,0,0,0);  
    if(bRet)  
    {  
        return hr; 
    }  
  
    lua_getglobal(pLuaInstance,"str");  
    string str = lua_tostring(pLuaInstance,-1);  
    cout<<"str = "<<str.c_str()<<endl;

    lua_getglobal(pLuaInstance,"tbl");   
    lua_getfield(pLuaInstance,-1,"name");  
    str = lua_tostring(pLuaInstance,-1);  
    cout<<"tbl:name = "<<str.c_str()<<endl;

	lua_getglobal(pLuaInstance, "main"); 
    lua_pushnumber(pLuaInstance, 10);
    lua_pushnumber(pLuaInstance, 20);

	//luainstance 
	//input param count
	//return param count
    int iRet= lua_pcall(pLuaInstance, 2, 1, 0);

	if (iRet)                   
    {  
        const char *pErrorMsg = lua_tostring(pLuaInstance, -1);  
        cout << pErrorMsg << endl;  
        return hr;  
    }  
    if (lua_isnumber(pLuaInstance, -1))
    {  
        double fValue = lua_tonumber(pLuaInstance, -1);  
        cout <<"Result is "<<fValue<< endl;  
    }  


	return hr;
}