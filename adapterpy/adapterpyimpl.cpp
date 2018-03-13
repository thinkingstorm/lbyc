#include "adapterpyimpl.h"

CAdapterpyImpl::CAdapterpyImpl(void)
{
}

CAdapterpyImpl::~CAdapterpyImpl(void)
{
}
//////////////////////////////////////////////////////////////////////////
std_method_impl CAdapterpyImpl::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	HRESULT		hr	=	S_OK;
	if (prot != NULL)
	{
		m_pRot	=	prot;
	}
	return hr;
}
std_method_impl CAdapterpyImpl::Init(void*)
{
	HRESULT		hr	=	S_OK;
 

	return hr;
}
std_method_impl CAdapterpyImpl::Uninit()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAdapterpyImpl::Start()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAdapterpyImpl::Stop()
{
	HRESULT		hr	=	S_OK;
	return hr;
}

std_method_impl CAdapterpyImpl::RunFile(const char* file)
{
	HRESULT		hr = S_OK;

	Py_Initialize();
	retrtpv(Py_IsInitialized(),E_FAIL)


	PyObject* pModule 	= NULL;
 	PyObject* pFunc 	= NULL;

	tstring strpathpy = GetCurrentRunPath(NULL);

#ifndef __GNUC__
	strpathpy += _T("\\");
#else
	strpathpy += _T("/");
#endif

	char szcurpath[MAX_PATH] = {0x00};
	sprintf(szcurpath,"sys.path.append('%s')",strpathpy.c_str());
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	PyRun_SimpleString(szcurpath);

	PyRun_SimpleString("print (11)");

	pModule =  PyImport_ImportModule("main.py");
	retrtpv(pModule,E_FAIL)

 	pFunc = PyObject_GetAttrString(pModule, "mainx");
	retrtpv(pFunc,E_FAIL)

 	PyEval_CallObject(pFunc, NULL);
 	Py_Finalize();



	return hr;
}