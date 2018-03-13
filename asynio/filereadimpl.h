#ifndef _FILEREADIMPL_H_
#define _FILEREADIMPL_H_

#include "stdafx.h"
#include <io/iasynio.h>
#include <compat/file.hpp>

#include "sys_file.h"

class CFileReadImpl :	public	IReadFile,
						public	CUnknownImp
{
public:
	CFileReadImpl(void);
	virtual ~CFileReadImpl(void);
	UNKNOWN_IMP1(IReadFile);

	//////////////////////////////////////////////////////////////////////////
	std_method(LoadFile)(const TCHAR* pszLoadFile,
		unsigned long ulwDesiredAccess,
		unsigned long ulShareMode,
		unsigned long ulCreationDisposition,
		unsigned long ulFlagsAndAttributes);
	std_method(CloseFile)();
	std_method_(byint64,GetFileSize)();
	std_method(ReadBuffer)(char* szBuffer, byint64 ulReadFileLen, byint64* ulReadSize);
	std_method(AsynReadBuffer)(const char* szNodeName,char* szNodeInfo);

private:

	struct file_sentry
	{
		static FILE_HANDLE default_value()
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
				by_file_close(p);
				p = 0;
			}
		}
	};

	
	sentry<FILE_HANDLE , file_sentry>m_hFile;

};
#endif
