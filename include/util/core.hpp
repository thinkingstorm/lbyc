#ifndef	_UTIL_CORE_H_
#define _UTIL_CORE_H_



#define 	OS_WINDOWS				0
#define 	OS_NATIVE				10
#define 	OS_POSIX				20
#define 	OS_MAC					30

#define 	CC_MSVC					0
#define 	CC_GCC					1


#define 	ARCH_32BIT				32
#define 	ARCH_64BIT				64

#define		TARGET_X86				0
#define		TARGET_NOT_X86			1
#define		TARGET_X64				2

#ifdef _MSC_VER
	#define 	TARGET_OS		   OS_WINDOWS
	#define 	CPP_COMPILER 	   CC_MSVC

#endif

#ifdef __GNUC__
	#define 	TARGET_OS		   OS_POSIX
	#define 	CPP_COMPILER	   CC_GCC	
#endif

#ifdef _MAC
	#define 	TARGET_OS		   OS_MAC
	#define 	CPP_COMPILER 	   CC_MSVC

#endif 


#if (defined(i386) || defined(_i386) || defined(__i386) || defined(__i386__)) || (defined(_WIN32)) || defined(_M_IX86)
	#define		TARGET_BITS				ARCH_32BIT
#endif

#if defined(_WIN64) || defined(__x86_64__) || defined(_M_X64)
	#undef		TARGET_BITS
	#define		TARGET_BITS				ARCH_64BIT
#endif

#if !defined(TARGET_BITS)
	#define		TARGET_BITS				ARCH_32BIT
#endif




#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include <wchar.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <errno.h>



#if (TARGET_OS == OS_WINDOWS)
	#include <windows.h>
	#pragma warning(disable:4996)
	#define	byint64		__int64
	#define	byuint64	unsigned __int64
	#define	FMT_I64D	"%I64d"
	#define	FMT_I64U	"%I64u"

#elif (TARGET_OS == OS_POSIX)
	#include <stdbool.h>
	#include <dlfcn.h>
	#include <unistd.h>
    #include <sys/socket.h>

	//address 
	#include <netinet/in.h>
	//setsockopt opations
	#include <netinet/tcp.h>
    #include <arpa/inet.h>
	
	#define byint64		long long int
	#define	byuint64	unsigned long long int
	#define	FMT_I64D	"%lld"
	#define	FMT_I64U	"%llu"

#elif (TAGET_OS == OS_MAC)
	#include <stdbool.h>
	#include <dlfcn.h>
#endif





#if TARGET_BITS == 64

	#if (TARGET_OS == OS_POSIX )
		typedef long long INT_PTR, *PINT_PTR;
		typedef unsigned long long UINT_PTR, *PUINT_PTR;
		typedef long long LONG_PTR, *PLONG_PTR;
		typedef unsigned long long ULONG_PTR, *PULONG_PTR;
	#elif (TAGET_OS == OS_MAC)
		typedef long long INT_PTR, *PINT_PTR;
		typedef unsigned long long UINT_PTR, *PUINT_PTR;
		typedef long long LONG_PTR, *PLONG_PTR;
		typedef unsigned long long ULONG_PTR, *PULONG_PTR;
	#endif
#else

	#if (TARGET_OS == OS_POSIX )
		typedef int INT_PTR, *PINT_PTR;
		typedef unsigned int UINT_PTR, *PUINT_PTR;
		typedef long LONG_PTR, *PLONG_PTR;
		typedef unsigned long ULONG_PTR, *PULONG_PTR;


	#elif (TAGET_OS == OS_MAC)
		typedef int INT_PTR, *PINT_PTR;
		typedef unsigned int UINT_PTR, *PUINT_PTR;
		typedef long LONG_PTR, *PLONG_PTR;
		typedef unsigned long ULONG_PTR, *PULONG_PTR;
	#endif
#endif


#ifndef _OFF_T_DEFINED
    #define _OFF_T_DEFINED
    typedef long _off_t; 
#endif


#if (CPP_COMPILER == CC_GCC )


#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif // !FALSE


#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

typedef long long 			LONGLONG;
typedef unsigned long long 	ULONGLONG;


typedef unsigned int UINT;
typedef int  INT;
typedef long BOOL;
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef short SHORT;
typedef unsigned char byte;
typedef double DOUBLE;
typedef float FLOAT;
typedef void *PVOID;
typedef short VARIANT_BOOL;



#ifndef _WCHAR_DEFINED
#define _WCHAR_DEFINED
typedef wchar_t WCHAR;
typedef WCHAR OLECHAR;
typedef OLECHAR *BSTR;
typedef WCHAR	*LPWSTR;
typedef const WCHAR *LPCWSTR;
#endif // !_WCHAR_DEFINED

typedef char CHAR;
typedef CHAR *LPSTR;
typedef const CHAR *LPCSTR;



#ifdef _UNICODE
	#define LPCTSTR LPCWSTR 
	#define _stprintf       _swprintf
	#define _T(x) L##x
	typedef wchar_t TCHAR;

#else	
	#define LPCTSTR LPCSTR
	#define _stprintf       sprintf
	#define _T(x)   x
	typedef char TCHAR;
#endif



typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

#ifndef VOID
#define VOID 	void
typedef void*	LPVOID;
#endif // !VOID





#ifndef _BYTE_DEFINED
#define _BYTE_DEFINED
typedef byte BYTE;
#endif // !_BYTE_DEFINED

#ifndef _WORD_DEFINED
#define _WORD_DEFINED
typedef unsigned short WORD;
#endif // !_WORD_DEFINED


#ifndef _LONG_DEFINED
#define _LONG_DEFINED
typedef long LONG;
#endif // !_LONG_DEFINED

#ifndef _WPARAM_DEFINED
#define _WPARAM_DEFINED
typedef UINT_PTR WPARAM;
#endif // _WPARAM_DEFINED

#ifndef _DWORD_DEFINED
#define _DWORD_DEFINED
typedef unsigned long DWORD;
#endif // !_DWORD_DEFINED
#ifndef _LPARAM_DEFINED
#define _LPARAM_DEFINED
typedef LONG_PTR LPARAM;

#endif // !_LPARAM_DEFINED
#ifndef _LRESULT_DEFINED
#define _LRESULT_DEFINED
typedef LONG_PTR LRESULT;

#endif // !_LRESULT_DEFINED



typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
typedef const FILETIME *PCFILETIME, *LPCFILETIME;



typedef void* 	HANDLE;
typedef void*	HMODULE;
typedef void*	HINSTANCE;
typedef void*	HTASK;
typedef void*	HKEY;
typedef void*	HDESK;
typedef void*	HMF;
typedef void*	HEMF;
typedef void*	HPEN;
typedef void*	HRSRC;
typedef void*	HSTR;
typedef void*	HWINSTA;
typedef void*	HKL;
typedef void*	HGDIOBJ;
typedef HANDLE 	HDWP;

#ifndef _HFILE_DEFINED
#define _HFILE_DEFINED
typedef INT HFILE;

#endif // !_HFILE_DEFINED
#ifndef _LPWORD_DEFINED
#define _LPWORD_DEFINED
typedef WORD *LPWORD;
#endif // !_LPWORD_DEFINED
#ifndef _LPDWORD_DEFINED
#define _LPDWORD_DEFINED
typedef DWORD *LPDWORD;
#endif // !_LPDWORD_DEFINED


#ifndef _COLORREF_DEFINED
#define _COLORREF_DEFINED
typedef DWORD COLORREF;
#endif // !_COLORREF_DEFINED

#ifndef _LPCOLORREF_DEFINED
#define _LPCOLORREF_DEFINED
typedef DWORD *LPCOLORREF;
#endif // !_LPCOLORREF_DEFINED

typedef HANDLE *LPHANDLE;
typedef struct _RECTL
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;

}RECTL;

typedef struct _RECTL *PRECTL;

typedef struct _RECTL *LPRECTL;

typedef struct tagPOINT
{
	LONG x;
    LONG y;
} POINT;

typedef struct tagPOINT *PPOINT;

typedef struct tagPOINT *LPPOINT;

typedef struct _POINTL
{
    LONG x;
    LONG y;
}POINTL;
typedef struct _POINTL *PPOINTL;
typedef struct tagSIZE
{
	LONG cx;
	LONG cy;
} 	SIZE;

typedef struct tagSIZE *PSIZE;
typedef struct tagSIZE *LPSIZE;

typedef struct tagSIZEL
{
	LONG cx;
	LONG cy;
}SIZEL;

typedef struct tagSIZEL *PSIZEL;
typedef struct tagSIZEL *LPSIZEL;


typedef struct _LARGE_INTEGER
{
    LONGLONG QuadPart;
}LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;

typedef struct _ULARGE_INTEGER
{
	ULONGLONG QuadPart;
} ULARGE_INTEGER;


typedef LONG SCODE;

#define DLL_PROCESS_ATTACH   1    
#define DLL_THREAD_ATTACH    2    
#define DLL_THREAD_DETACH    3    
#define DLL_PROCESS_DETACH   0   

#define MAX_PATH          260
#define _MAX_PATH   260 // max. length of full pathname
#define _MAX_DRIVE  3   // max. length of drive component
#define _MAX_DIR    256 // max. length of path component
#define _MAX_FNAME  256 // max. length of file name component
#define _MAX_EXT    256 // max. length of extension component







#endif


#if(CPP_COMPILER == CC_MSVC)
	#define _aligned(g)		__declspec(align(g))
#else
	#define _aligned(g)		__attribute__((aligned(g)))
#endif

#define __aligned(g, type) _aligned(g) type


#define	PACK_ONEBYTE		__attribute__((packed))
#define	PACK_EIGHTBYTE		__attribute__((aligned(8))) 




#ifndef MAX_PATH
#define MAX_PATH          260
#endif


#if (CPP_COMPILER == CC_MSVC )
	#define __attribute__(x)
#elif (CPP_COMPILER == CC_GCC )

#endif


#ifdef _MAC
#define CALLBACK    PASCAL
#define WINAPI      CDECL
#define WINAPIV     CDECL
#define APIENTRY    WINAPI
#define APIPRIVATE  CDECL
#ifdef _68K_
#define PASCAL      __pascal
#else
#define PASCAL
#endif
#elif _MSC_VER

#ifndef WINAPI
#define WINAPI __stdcall
#endif

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#ifndef WINAPIV
#define WINAPIV     __cdecl
#endif 


#ifndef APIENTRY
#define APIENTRY    WINAPI
#endif 



#ifndef APIPRIVATE
#define APIPRIVATE  __stdcall
#endif 


#ifndef PASCAL
#define PASCAL      __stdcall
#endif 


#elif __GNUC__
#define CALLBACK
#define WINAPI
#define WINAPIV
#define APIENTRY    WINAPI
#define APIPRIVATE
#define PASCAL      pascal
#endif


#ifdef BY_NO_VTABLE
#undef BY_NO_VTABLE
#endif

#if defined(_MSC_VER)
#define BY_NO_VTABLE __declspec(novtable)
#else
#define BY_NO_VTABLE
#endif


//dll 
//__declspec(dllexport)
//so no display 
#ifdef  __GNUC__
#define BY_VISIBILITY_HIDDEN   __attribute__ ((visibility ("hidden")))
#else
#define BY_VISIBILITY_HIDDEN
#endif

//so display 
#ifdef __GNUC__
#define BY_VISIBILITY_DEFAULT __attribute__ ((visibility ("default")))
#else
#define BY_VISIBILITY_DEFAULT
#endif


#ifdef	__GNUC__
#define	_unused	__attribute__ ((__unused__))
#else
#define  _unused 
#endif




#define BY_HIDDEN_(type)                        BY_VISIBILITY_HIDDEN type
#define BY_EXTERNAL_VIS_(type)                  BY_VISIBILITY_DEFAULT type

#define BY_HIDDEN                               BY_VISIBILITY_HIDDEN
#define BY_EXTERNAL_VIS                         BY_VISIBILITY_DEFAULT

#undef  IMETHOD_VISIBILITY
#define IMETHOD_VISIBILITY                      BY_VISIBILITY_HIDDEN

#ifdef _MSC_VER

#define BY_STDCALL                              __stdcall
#define BY_IMPORT                               __declspec(dllimport)
#define BY_IMPORT_(type)                        type __declspec(dllimport) __stdcall
#define BY_EXPORT                               __declspec(dllexport)
#define BY_EXPORT_(type)                        type __declspec(dllexport) __stdcall
#define BY_IMETHOD_(type)                       virtual type __stdcall
#define BY_IMETHODIMP_(type)                    type __stdcall
#define BY_METHOD_(type)                        type __stdcall
#define BY_CALLBACK_(_type, _name)              _type (__stdcall * _name)
#define BY_EXPORT_STATIC_MEMBER_(type)          type
#define BY_IMPORT_STATIC_MEMBER_(type)          type

#else

#define BY_STDCALL								
#define BY_IMPORT                               NS_EXTERNAL_VIS
#define BY_IMPORT_(type)                        NS_EXTERNAL_VIS_(type)
#define BY_EXPORT                               NS_EXTERNAL_VIS
#define BY_EXPORT_(type)                        NS_EXTERNAL_VIS_(type)
#define BY_IMETHOD_(type)                       virtual IMETHOD_VISIBILITY type NS_DEFCALL
#define BY_IMETHODIMP_(type)                    type
#define BY_METHOD_(type)                        type
#define BY_CALLBACK_(_type, _name)              _type (* _name)
#define BY_EXPORT_STATIC_MEMBER_(type)          NS_EXTERNAL_VIS_(type)
#define BY_IMPORT_STATIC_MEMBER_(type)          NS_EXTERNAL_VIS_(type)

#endif




#ifdef __GNUC__
#define BY_STDCALL_FUNCPROTO(ret, name, class, func, args)			\
  typeof(&class::func) name
#else
#define BY_STDCALL_FUNCPROTO(ret, name, class, func, args)			\
  ret (NS_STDCALL class::*name) args
#endif




#ifndef EXTERN_C
	#ifdef __cplusplus
		#define EXTERN_C    extern "C"
		#define STDNOTHROW (std::nothrow)
	#else
		#define EXTERN_C    extern
		#define STDNOTHROW (std::nothrow)
	#endif
#endif






#ifdef __cplusplus
	#define Memory_Allocate new (std::nothrow)

	#ifndef tstring
		#ifdef _UNICODE
			#define _T(x) L##x
			#define tstring std::wstring
		#else	
			#define tstring std::string
			#define _T(x)   x
		#endif
	#endif
	
#else
	#define Memory_Allocate malloc
#endif








#ifdef __GNUC__
#define MODULE_API                              HRESULT    BY_VISIBILITY_DEFAULT 
#else
#define MODULE_API                              HRESULT    BY_STDCALL 
#endif


#define MD_EXPORTS                              EXTERN_C        MODULE_API







#define FAILEXIT_N(x, _h_r_) 					{if(!(x)) return _h_r_; }
#define FAILEXIT_FALSE_N(x) 					{FAILEXIT_N((x),FALSE)}
#define FAILEXIT_NULL_N(x) 						{FAILEXIT_N((x),NULL)}
#define FAILEXIT_FAIL_N(x) 						{FAILEXIT_N((x),RT_FAIL)}
#define FAILEXIT_OTHER_N(x) 					{FAILEXIT_N((x),0xFFFFFFFF)}
#define FAILEXIT_FAIL_ONE(x) 					{FAILEXIT_N((x),1)}
#define FAILEXIT_FAIL_ZERO(x) 					{FAILEXIT_N((x),0)}

#define SAF_DELET(ptr)							if((ptr)){delete ptr;ptr=(0);}
#define SAF_DELET_ARRAY(ptr)					if((ptr)){delete [] ptr;ptr=(0);}


#define _max(a,b)								((a)>(b)?(a):(b))
#define _min(a,b)								((a)>(b)?(b):(a))
#define bzero(p,s)								memset(p,0,s)
#define tzero(p,s) 													\
	{																\
		for(unsigned long iloop = 0; iloop < s; iloop++)			\
		{															\
			bzero(&(p[iloop]), sizeof(p[0]));						\
		}															\
	}																\

#define retrtpv(x, _h_r_)                       { if(!(x))      return _h_r_; }
#define retrtnpv(x, _h_r_)                      { if((x))       return _h_r_; }

#define retret(x)                               { if(!(x))      return; }
#define retrtp(x, _h_r_)                        { if(0 == (x)) return _h_r_; }


#endif 
