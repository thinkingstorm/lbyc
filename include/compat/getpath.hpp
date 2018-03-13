#ifndef _COMPAT_GETPATH_H_
#define _COMPAT_GETPATH_H_

#include <util/core.hpp>
#include <util/string_ex.h>

#define TAG_XML_BUF		    "<"
#define TAG_JSON_BUF		"{"

inline static bool IsXmlBuf(const char* lpFile)
{
	if (NULL == lpFile || 0x00 == (*lpFile))
		return false;
	if (0 == string_stricmp(lpFile, TAG_XML_BUF))
	{
		return true;
	}
	return false;
}
inline static bool IsJsonBuf(const char* lpFile)
{
	if (NULL == lpFile || 0x00 == (*lpFile))
		return false;
	if (0 == string_stricmp(lpFile, TAG_JSON_BUF))
	{
		return true;
	}
	return false;
}


inline static bool FileIsExist(LPCTSTR lpFile)
{
	if(NULL == lpFile || 0x00 == (*lpFile ))
		return false;

#ifndef __GNUC__
	DWORD dwAttributes = GetFileAttributes(lpFile);
	if(0xFFFFFFFF == dwAttributes || dwAttributes&FILE_ATTRIBUTE_DIRECTORY) 
		return false;
#else
	 int fd = access (lpFile, F_OK);
	 if(fd < 0)
		 return false;
#endif
 

	return true;
}

#ifdef __cplusplus
inline static tstring GetCurrentRunPath(HINSTANCE hInstance)
{

	tstring strrunpath;
	strrunpath.clear();
#ifndef __GNUC__
	TCHAR szBuf[MAX_PATH*2 + 1]    =   {0x00};
	::GetModuleFileNameW(hInstance, szBuf, MAX_PATH*2);

	if(tstring_strlen(szBuf) <= 0)
		return _T("");

	tstring strBuf = szBuf;
	size_t npos = strBuf.rfind(_T("\\"));
	strrunpath = strBuf.substr(0, npos);

#else

	TCHAR szBuf[MAX_PATH*2 + 1]  =   {0x00};

	int npos = -1;

	//int nCount = readlink("/proc/self/exe", szBuf, MAX_PATH*2);


	pid_t cur_pid = getpid();
    char cur_exe_link[256] = {0};
    sprintf(cur_exe_link, "/proc/%u/exe", cur_pid);
	int nCount = readlink(cur_exe_link, szBuf, MAX_PATH*2);


	if(nCount < 0 || nCount > MAX_PATH)
	{
		return "";
	}
	szBuf[nCount] = _T('0');

	if(string_strlen(szBuf) <= 0)
		return _T("");

	std::string strBuf;
	strBuf.assign(szBuf);
    npos = strBuf.find_last_of('/');
	strrunpath = strBuf.substr(0, npos);

#endif


	return strrunpath;
}

#ifndef __GNUC__
	#define path_slash _T("\\")
#else
	#define path_slash _T("/")
#endif


inline static tstring GetCurAbsolutepath(tstring curpath,tstring dir)
{
	curpath +=path_slash;
	curpath += dir;
	return curpath;
}

#endif









#endif
