#include "infoanalysisimpl.h"
#include "crootimpl.h"
#include "json.h"
#include <io/iasynio.h>

CInfoAnalysisImpl::CInfoAnalysisImpl(void)
{
	
}

CInfoAnalysisImpl::~CInfoAnalysisImpl(void)
{

}
//////////////////////////////////////////////////////////////////////////
std_method_impl CInfoAnalysisImpl::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	if (prot != NULL)
	{
		m_pRot	=	prot;
	}
	return S_OK;
}
std_method_impl CInfoAnalysisImpl::Init(void*)
{
	
	return S_OK;
}
std_method_impl CInfoAnalysisImpl::Uninit()
{

	return S_OK;
}
std_method_impl CInfoAnalysisImpl::Start()
{

	return S_OK;
}
std_method_impl CInfoAnalysisImpl::Stop()
{
	return S_OK;
}
//////////////////////////////////////////////////////////////////////////

std_method_impl CInfoAnalysisImpl::NewObject(const char* data, IModuleBase** ioNodeInfo)
{
	InfoRoot*	pObject = NULL;
	pObject = new CRootImpl();

	pObject->LoadData((char*)data);
	pObject->AddRef();
	*ioNodeInfo = reinterpret_cast<IModuleBase*>(pObject);

	return S_OK;
}
std_method_impl CInfoAnalysisImpl::NewLoadFileObject(const TCHAR* filepath, IModuleBase** ioNodeInfo)
{

	HRESULT hr = S_OK;

	retrtpv(filepath, E_FAIL);
	retrtpv(ioNodeInfo, E_FAIL);
	CComLoader			comLoader;
	_lComPtr<IAsynIo>	pAsynIo = INULL;

	IReadFile*			pReadFile = NULL;

	if (m_pRot != INULL)
	{
		m_pRot->GetObject(CLSID_IAsynIo, re_uuidof(IAsynIo), (IModuleBase**)&pAsynIo.m_p);
	}

	if (pAsynIo != NULL)
	{
		pAsynIo->CreateReadFile((IModuleBase**)ioNodeInfo);
	}
	else
	{

		tstring path = GetCurrentRunPath(NULL);

		tstring asynio;
		asynio.append(path);

#ifdef _MSC_VER
		asynio += _T("\\asynIo.dll");
#elif __GNUC__
		asynio += _T("//libasynio.so");
#endif // __GNUC__
	

		retrtpv(FileIsExist(asynio.c_str()), E_FAIL)

		BOOL bRet = FALSE;
		bRet = comLoader.LoadCom(asynio.c_str());
		if (bRet == FALSE)
		{
			return E_FAIL;
		}
		hr = comLoader.CreateInstance(CLSID_IAsynIo, NULL, NULL, re_uuidof(IAsynIo), (void**)&pAsynIo.m_p);

		if (hr == S_OK)
		{
			pAsynIo->CreateReadFile((IModuleBase**)&pReadFile);
		}
		else
		{
			return E_FAIL;
		}
	}
	retrtpv(pReadFile, E_FAIL)
	retrtpv(FileIsExist(filepath), E_FAIL)

	hr = pReadFile->LoadFile(filepath, 0, 0, 0, 0);

	byint64 ulFileSize = pReadFile->GetFileSize();

	retrtpv(ulFileSize, E_FAIL)

	sentry<char*, default_array_sentry> pBuffer;
	pBuffer  = Memory_Allocate char[ulFileSize + 1];


	byint64 ulReadLen = -1;
	pReadFile->ReadBuffer(pBuffer, ulFileSize, &ulReadLen);
	pReadFile->CloseFile();

	InfoRoot*	pObject = new CRootImpl();
	pObject->LoadData((char*)pBuffer.m_p);
	pObject->AddRef();

	*ioNodeInfo = reinterpret_cast<IModuleBase*>(pObject);

	pAsynIo->DeleteIo(pReadFile);

	return S_OK;
}
std_method_impl CInfoAnalysisImpl::DelObject(IModuleBase* ioNodeInfo)
{

	if (ioNodeInfo != INULL)
	{
		ioNodeInfo->Release();
	}
	return S_OK;
}


std_method_impl CInfoAnalysisImpl::JsonToXML(const char* input, char*  output, unsigned long ulen)
{

	string strxml = CJson::Json2Xml(input);

	if (strxml.length() <= ulen)
		string_strcpy(output, strxml.c_str());
	else
		return E_FAIL;
	

	return S_OK;
}
std_method_impl CInfoAnalysisImpl::XMLToJson(const char* input, char*  output, unsigned long ulen)
{

	string strjson = CJson::Json2Xml(input);

	if (strjson.length() <= ulen)
		string_strcpy(output, strjson.c_str());
	else
		return E_FAIL;

	return S_OK;
}
