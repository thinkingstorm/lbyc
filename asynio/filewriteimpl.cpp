#include "filewriteimpl.h"

CFileWriteImpl::CFileWriteImpl(void)
{
}

CFileWriteImpl::~CFileWriteImpl(void)
{
}
//////////////////////////////////////////////////////////////////////////
std_method_impl CFileWriteImpl::LoadFile(const char* pszLoadFile,
										 unsigned long ulwDesiredAccess,
										 unsigned long ulShareMode,
										 unsigned long ulCreationDisposition,
										 unsigned long ulFlagsAndAttributes)
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CFileWriteImpl::CloseFile()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CFileWriteImpl::GetFileSize(unsigned long* ulReadSize)
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CFileWriteImpl::WriteBuffer(const char* szNodeName,char* szNodeInfo)
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CFileWriteImpl::AsynWriteBuffer(const char* szNodeName,char* szNodeInfo)
{
	HRESULT		hr	=	S_OK;

	return hr;
}

