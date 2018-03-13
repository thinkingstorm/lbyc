#ifndef _BYUNKNOWN_H_
#define _BYUNKNOWN_H_


#include <util/util.h>
using namespace util;
#include <dlcom/byguiddef.hpp>
#include <dlcom/byid.hpp>



#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef long HRESULT;
#endif


#ifndef	interface
#define interface 								struct
#endif

#ifndef S_OK
#define S_OK									((HRESULT)0L)
#endif // !S_OK

#ifndef S_FALSE
#define S_FALSE									((HRESULT)1L)
#endif // !S_FALSE

#ifndef S_DELETE
#define S_DELETE								((HRESULT)10L)
#endif // !S_DELETE

#ifndef SUCCEEDED
#define SUCCEEDED(hr)							((HRESULT)(hr) >= 0)
#endif
#ifndef FAILED
#define FAILED(hr)								((HRESULT)(hr) < 0)
#endif


#define RFAILED(x) 								{ HRESULT _h_r_ = (x); if(FAILED(_h_r_)) return _h_r_; }

#define RFAILEDV(x,v) 							{ HRESULT _h_r_ = (x); if(_h_r_ != S_OK) return v;}


#define _STDHRESULT_TYPEDEF_(_sc)				((HRESULT)_sc)

#ifndef PURE
#define PURE						            = 0
#endif




#define std_method(method) 					    virtual HRESULT BY_STDCALL method
#define std_method_impl							HRESULT BY_STDCALL



#define std_method_(type,method)		        virtual type BY_STDCALL method
#define std_method_type_impl(type)				type BY_STDCALL   



                   
#ifdef _MSC_VER

#else
#define E_UNEXPECTED							_STDHRESULT_TYPEDEF_(0x8000FFFFL)
#define E_NOTIMPL					            _STDHRESULT_TYPEDEF_(0x80004001L)
#define E_OUTOFMEMORY							_STDHRESULT_TYPEDEF_(0x8007000EL)
#define E_INVALIDARG							_STDHRESULT_TYPEDEF_(0x80070057L)
#define E_NOINTERFACE							_STDHRESULT_TYPEDEF_(0x80004002L)
#define E_POINTER								_STDHRESULT_TYPEDEF_(0x80004003L)
#define E_HANDLE								_STDHRESULT_TYPEDEF_(0x80070006L)
#define E_ABORT									_STDHRESULT_TYPEDEF_(0x80004004L)
#define E_FAIL									_STDHRESULT_TYPEDEF_(0x80004005L)
#define E_ACCESSDENIED							_STDHRESULT_TYPEDEF_(0x80070005L)
#define MK_S_MONIKERALREADYREGISTERED           _STDHRESULT_TYPEDEF_(0x000401E7L)
#endif


#define IModuleBase								ISupports
#define IBase								    ISupports
#define INULL									((ISupports*)0)

interface  ISupports
{
    std_method(QueryInterface)(const IID & riid, void **ppv)		    =	0;
    std_method_(ULONG, AddRef)()									=	0;
	std_method_(ULONG, Release)()									=	0;
};
MD_DEFINE_IID(ISupports, "{00000000-0000-0000-C000-000000000046}");


interface IClassFactory__ : public ISupports
{
	std_method_(HRESULT, CreateInstance)(IBase *pUnkOuter, REFIID riid,void **ppvObject) = 0;
	std_method_(HRESULT, LockServer)(BOOL fLock) = 0;
};
MD_DEFINE_IID(IClassFactory__, "{00000001-0000-0000-C000-000000000046}");






#endif
