#include "asynioimpl.h"
#include "filereadimpl.h"
#include "filewriteimpl.h"
#include "tcpsocketimpl.h"

CAsynIoImpl::CAsynIoImpl(void)
{
}

CAsynIoImpl::~CAsynIoImpl(void)
{
}
//////////////////////////////////////////////////////////////////////////
std_method_impl CAsynIoImpl::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	HRESULT		hr	=	S_OK;
	if (prot != NULL)
	{
		m_pRot	=	prot;
	}
	return hr;
}
std_method_impl CAsynIoImpl::Init(void*)
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAsynIoImpl::Uninit()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAsynIoImpl::Start()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CAsynIoImpl::Stop()
{
	HRESULT		hr	=	S_OK;
	return hr;
}
std_method_impl CAsynIoImpl::CreateReadFile(IModuleBase** pReadFile)
{
	HRESULT		hr	=	S_OK;
	IReadFile*	pObject			=	NULL;
	pObject						=	new CFileReadImpl;
	pObject->AddRef();
	*pReadFile					=	reinterpret_cast<IModuleBase*>(pObject);
	return hr;
}
std_method_impl CAsynIoImpl::CreateWriteFile(IModuleBase** pWriteFile)
{
	HRESULT		hr	=	S_OK;
	IWriteFile*	pObject			=	NULL;
	pObject						=	new CFileWriteImpl;
	pObject->AddRef();

	*pWriteFile					=	reinterpret_cast<IModuleBase*>(pObject);
	return hr;
}
std_method_impl CAsynIoImpl::CreateAsynTcpSocket(IModuleBase** pAsynTcpSocket)
{
	HRESULT		hr	=	S_OK;
	return hr;
}
std_method_impl CAsynIoImpl::CreateTcpSocket(IModuleBase** pTcpSocket)
{
	HRESULT		hr	=	S_OK;

	ITcpSocket*	pObject			=	NULL;
	pObject						=	new CTcpSocketImpl;
	pObject->AddRef();

	*pTcpSocket					=	reinterpret_cast<IModuleBase*>(pObject);

	return hr;
}
std_method_impl CAsynIoImpl::CreateAsynUdpSocket(IModuleBase** pAsynUdpSocket)
{
	HRESULT		hr	=	S_OK;
	return hr;
}
std_method_impl CAsynIoImpl::CreateUdpSocket(IModuleBase** pUdpSocket)
{
	HRESULT		hr	=	S_OK;
	return hr;
}

std_method_impl CAsynIoImpl::DeleteIo(IModuleBase* pAsynIo)
{
	HRESULT		hr	=	S_OK;
	if (pAsynIo != NULL)
	{
		pAsynIo->Release();
	}
	return hr;
}
