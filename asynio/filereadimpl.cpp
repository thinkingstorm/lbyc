#include "filereadimpl.h"

CFileReadImpl::CFileReadImpl(void)
{

}
CFileReadImpl::~CFileReadImpl(void)
{
	
}
//////////////////////////////////////////////////////////////////////////
std_method_impl CFileReadImpl::LoadFile(const TCHAR* pszLoadFile,
										  unsigned long ulwDesiredAccess,
										  unsigned long ulShareMode,
										  unsigned long ulCreationDisposition,
										  unsigned long ulFlagsAndAttributes)
{
	HRESULT		hr	=	S_OK;

	m_hFile.m_p =	by_file_open(pszLoadFile, O_RDWR, 0644);

	return hr;
}
std_method_impl CFileReadImpl::CloseFile()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_type_impl(byint64) CFileReadImpl::GetFileSize()
{
	return by_file_fsize(m_hFile.m_p);
}

std_method_impl CFileReadImpl::ReadBuffer(char* szBuffer,byint64 ulReadFileLen, byint64* ulReadSize)
{
	HRESULT		hr	=	S_OK;

	*ulReadSize = by_file_read(m_hFile.m_p, szBuffer, ulReadFileLen);

	return hr;
}
std_method_impl CFileReadImpl::AsynReadBuffer(const char* szNodeName,char* szNodeInfo)
{
	HRESULT		hr	=	S_OK;

	return hr;
}
