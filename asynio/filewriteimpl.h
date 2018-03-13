#ifndef _FILEWRITEIMPL_H_
#define _FILEWRITEIMPL_H_

#include "stdafx.h"
#include <io/iasynio.h>

class CFileWriteImpl :	public	IWriteFile,
						public	CUnknownImp

{
public:
	CFileWriteImpl(void);
	virtual ~CFileWriteImpl(void);
	UNKNOWN_IMP1(IWriteFile);
	//////////////////////////////////////////////////////////////////////////
	std_method(LoadFile)(const char* pszLoadFile,
		unsigned long ulwDesiredAccess,
		unsigned long ulShareMode,
		unsigned long ulCreationDisposition,
		unsigned long ulFlagsAndAttributes);
	std_method(CloseFile)();
	std_method(GetFileSize)(unsigned long* ulReadSize);
	std_method(WriteBuffer)(const char* szNodeName,char* szNodeInfo);
	std_method(AsynWriteBuffer)(const char* szNodeName,char* szNodeInfo);
private:


};

#endif