#ifndef _COMFACTORY_H_
#define _COMFACTORY_H_


#include <util/util.h>
using namespace util;
#include <dlcom/ibase.h>
#include <dlcom/comfunc.hpp>
#include <dlcom/comsentry.hpp>

//////////////////////////////////////////////////////////////////////////

namespace by {


	/*
	template<class CLS>
	class TStdClsFactory : public IComObjectFrameworkClassFactory, private CUnknownImp
	{
	public: 
		UNKNOWN_IMP2(IComObjectFrameworkClassFactory, IClassFactory__);
	public: 
		
		std_method(init_class)(IModuleBase* prot, IModuleBase* punkOuter)
		{
			return !punkOuter ? S_OK : E_INVALIDARG;
		}
		std_method(init_class_inner)(IModuleBase* punkOuter)
		{
			return !punkOuter ? S_OK : E_INVALIDARG;
		}
		//IComObjectFrameworkClassFactory
		std_method(CreateInstance)(IModuleBase *prot, IModuleBase *punkOuter, const IID& riid, void **ppv)
		{
			return create_instance(prot, punkOuter, riid, ppv);
		}
		std_method_(CLSID, GetAt)(LONG nIndex)
		{
			return g_mapClassObject[nIndex + 1].clsid;
		}
		std_method_(LONG, GetCount)()
		{
			LONG lCount = sizeof(g_mapClassObject) / sizeof(g_mapClassObject[0]);

			return (lCount > 0) ? lCount - 1 : 0;
		}
		std_method_(LPCSTR, ProgIDFromCLSID)(REFCLSID clsid)
		{
			for (size_t i = 1; i < sizeof(g_mapClassObject) / sizeof(g_mapClassObject[0]); ++i)
			{
				if (clsid == g_mapClassObject[i].clsid)
				{
					return g_mapClassObject[i].ProgID;
				}
			}
			return "";
		}
		// IClassFactory
		std_method(CreateInstance)(IModuleBase *punkOuter,REFIID riid,void **ppv)
		{
			return create_instance(punkOuter, riid, ppv);
		}
		std_method(LockServer)(BOOL fLock)
		{
			return lock_server(fLock);
		}
	public:
		static HRESULT create_instance(IModuleBase *prot, IModuleBase *punkOuter, const IID& riid, void **ppv)
		{
			*ppv = 0;
			// aggregation validate:
			retrtpv(!punkOuter || re_uuidof(IModuleBase) == riid, E_INVALIDARG);
			// create new object/aggregation:
			sentry<CLS*> p(new CLS);
			retrtpv(p, E_UNEXPECTED);
			((IUnknown_Nondelegate*)(CLS*)p)->AddRef_Nondelegate(); // nondelegation, protect reference count
			RFAILED(p->init_class(prot, punkOuter));
			HRESULT hr = ((IUnknown_Nondelegate*)(CLS*)p)->QueryInterface_Nondelegate(riid, ppv);
			((IUnknown_Nondelegate*)p.detach())->Release_Nondelegate(); // nondelegation, balance reference count or destroy.
			return hr;
		}
		static HRESULT create_instance(IModuleBase *punkOuter, const IID& riid, void **ppv)
		{
			*ppv = 0;
			// aggregation validate:
			retrtpv(!punkOuter || re_uuidof(IModuleBase) == riid, E_INVALIDARG);
			// create new object/aggregation:
			sentry<CLS*> p(new CLS);
			retrtpv(p, E_UNEXPECTED);
			((IUnknown_Nondelegate*)(CLS*)p)->AddRef_Nondelegate(); // nondelegation, protect reference count
			if (punkOuter)
			{
				//CUnknownImp_Inner* pInner = (CUnknownImp_Inner*)(p);
				//RFAILED(pInner->init_class_inner(punkOuter));
			}
			HRESULT hr = ((IUnknown_Nondelegate*)(CLS*)p)->QueryInterface_Nondelegate(riid, ppv);
			((IUnknown_Nondelegate*)p.detach())->Release_Nondelegate(); // nondelegation, balance reference count or destroy.
			return hr;
		}
		static HRESULT lock_server(BOOL fLock)
		{
			return S_OK;
		}
		static HRESULT GetClassObject(const IID& riid, void **ppv)
		{
			return TStdClsFactory<TStdClsFactory<CLS> >::create_instance(0, 0, riid, ppv);

			//return TStdClsFactory<CLS>::create_instance(0, 0, riid, ppv);

		}
	};
	*/

template<class CLS, class IFactory = IClassFactory__>
class TClsFactory : public IFactory, public CUnknownImp
{
public: 
	UNKNOWN_IMP1(IClassFactory__);

public:

	std_method_(HRESULT, CreateInstance)(IModuleBase *pUnkOuter, REFIID riid, void **ppvObject)
	{
		return create_instance(pUnkOuter, riid, ppvObject);
	}
	std_method_(HRESULT, LockServer)(BOOL fLock)
	{
		return lock_server(fLock);
	}
public:
	static HRESULT create_instance(IModuleBase *punkOuter, REFIID riid, void **ppv)
	{
		*ppv = 0;
		// aggregation validate:
		retrtpv(!punkOuter || re_uuidof(IModuleBase) == riid, E_INVALIDARG);
		// create new object/aggregation:
		sentry<CLS*> p(new CLS);
		retrtpv(p, E_UNEXPECTED);
		((IUnknown_Nondelegate*)(CLS*)p)->AddRef_Nondelegate(); // nondelegation, protect reference count
		if (punkOuter)
		{
			//CUnknownImp_Inner* pInner = (CUnknownImp_Inner*)(p);
			//RFAILED(pInner->init_class_inner(punkOuter));
		}
		HRESULT hr = ((IUnknown_Nondelegate*)(CLS*)p)->QueryInterface_Nondelegate(riid, ppv);
		((IUnknown_Nondelegate*)p.detach())->Release_Nondelegate(); // nondelegation, balance reference count or destroy.
		return hr;
	}
	static HRESULT lock_server(BOOL /*fLock*/)
	{
		return S_OK;
	}
	static HRESULT GetClassObject(const IID& riid, void **ppv)
	{
		return TClsFactory<TClsFactory<CLS> >::create_instance(0, riid, ppv);
	}
};



#pragma pack(1)

typedef struct __class_object_map{ 
	CLSID clsid; 
	HRESULT (*pfnGetClassObject)(const IID&, void**);
	char ProgID[MAX_PROGIDLEN];
}class_object_map, *pclass_object_map;

#pragma pack()

template<class CLS>
class TStdClsFactory : public TClsFactory<CLS, IComObjectFrameworkClassFactory>
{
public: // IRSBase:
	UNKNOWN_IMP2(IComObjectFrameworkClassFactory, IClassFactory__);

	std_method(init_class)(IModuleBase* prot, IModuleBase* punkOuter)
	{
		return !punkOuter ? S_OK : E_INVALIDARG;
	}
	std_method(init_class_inner)(IModuleBase* punkOuter)
	{
		return !punkOuter ? S_OK : E_INVALIDARG;
	}



public: 
	std_method(CreateInstance)(IModuleBase *prot, IModuleBase *punkOuter, REFIID riid, void **ppv)
	{
		return create_instance(prot, punkOuter, riid, ppv);
	}
#ifndef __GNUC__
	std_method_(CLSID, GetAt)(LONG nIndex)
	{
		return g_mapClassObject[nIndex + 1].clsid;
	}
	std_method_(LONG, GetCount)()
	{
		LONG lCount = sizeof(g_mapClassObject) / sizeof(g_mapClassObject[0]);
		return (lCount > 0) ? lCount - 1 : 0;
	}
	std_method_(LPCSTR, ProgIDFromCLSID)(REFCLSID clsid)
	{
		for (size_t i = 1; i < sizeof(g_mapClassObject) / sizeof(g_mapClassObject[0]); ++i)
		{
			if (clsid == g_mapClassObject[i].clsid)
			{
				return g_mapClassObject[i].ProgID;
			}
		}
		return "";
	}
#else

private:

public:
	const class_object_map* GetClassObjectMap();
	const long 				GetClassObjectMapSize();


	std_method_(CLSID, GetAt)(LONG nIndex) 
	{
		const class_object_map* pMap = GetClassObjectMap();

		return pMap[nIndex+1].clsid;
	}

	std_method_(LONG, GetCount)()
	{
		const long lCount = GetClassObjectMapSize();
		return (lCount > 0)?lCount-1:0;
	}

	std_method_(LPCTSTR, ProgIDFromCLSID)(REFCLSID clsid)
	{
		const class_object_map* pMap = GetClassObjectMap();
		for(long i = 1; i < GetClassObjectMapSize(); ++i)
		{
			if(clsid == pMap[i].clsid)
			{
				return pMap[i].ProgID;
			}
		}
		return _T("");		
	}
#endif

public:
	static HRESULT create_instance(IModuleBase *prot, IModuleBase *punkOuter, REFIID riid, void **ppv)
	{
		*ppv = 0;
		// aggregation validate:
		retrtpv(!punkOuter || re_uuidof(IModuleBase) == riid, E_INVALIDARG);
		// create new object/aggregation:
		sentry<CLS*> p(new CLS);
		retrtpv(p, E_UNEXPECTED);
		((IUnknown_Nondelegate*)(CLS*)p)->AddRef_Nondelegate(); // nondelegation, protect reference count
		RFAILED(p->init_class(prot, punkOuter));
		HRESULT hr = ((IUnknown_Nondelegate*)(CLS*)p)->QueryInterface_Nondelegate(riid, ppv);
		((IUnknown_Nondelegate*)p.detach())->Release_Nondelegate(); // nondelegation, balance reference count or destroy.
		return hr;
	}
	static HRESULT GetClassObject(const IID& riid, void **ppv)
	{
		return TStdClsFactory<TStdClsFactory<CLS> >::create_instance(0, 0, riid, ppv);
	}
};



class CNullObjcetUnkown :	public	IModuleBase,
							private CUnknownImp
{
public:
	UNKNOWN_IMP1(IModuleBase);

	std_method(init_class)(IModuleBase* prot, IModuleBase* punkOuter)
	{
		return !punkOuter ? S_OK : E_INVALIDARG;
	}

	std_method(init_class_inner)(IModuleBase* punkOuter)
	{
		return !punkOuter ? S_OK : E_INVALIDARG;
	}
};






#ifndef __GNUC__

#define BEGIN_CLIDMAP \
		static const  class_object_map g_mapClassObject[] = { 

#define CLIDMAPENTRY_BEGIN \
		{CLSID_MDClassFactory,&TStdClsFactory<CNullObjcetUnkown>::GetClassObject, ""},

#define CLIDMAPENTRY(CID,CLASS) \
		{CID, &TStdClsFactory<CLASS>::GetClassObject, ""},

#define CLIDMAPENTRY_PROGID(CID,CLASS,PROGID) \
		{CID, &TStdClsFactory<CLASS>::GetClassObject, PROGID},

#define CLIDMAPENTRY_END  

#define END_CLIDMAP };																			
																																								
#define DEFINE_ALL_EXPORTFUN																	\
		MD_EXPORTS DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv);					\
		MD_EXPORTS DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)					\
		{																						\
			for(size_t i = 0; i < sizeof(g_mapClassObject)/sizeof(g_mapClassObject[0]); ++i)	\
			{																					\
				if(rclsid == g_mapClassObject[i].clsid)											\
				{																				\
					return g_mapClassObject[i].pfnGetClassObject(riid, ppv);					\
				}																				\
			}																					\
			return E_INVALIDARG;																\
		}																						\

#define END_CLIDMAP_AND_EXPORTFUN };															\
		DEFINE_ALL_EXPORTFUN;																																	


#else



#define BEGIN_CLIDMAP \
		static const  class_object_map g_mapClassObject[] = { 

#define CLIDMAPENTRY_BEGIN \
		{CLSID_MDClassFactory,&TStdClsFactory<CNullObjcetUnkown>::GetClassObject, ""},

#define CLIDMAPENTRY(CID,CLASS) \
		{CID, &TStdClsFactory<CLASS>::GetClassObject, ""},

#define CLIDMAPENTRY_PROGID(CID,CLASS,PROGID) \
		{CID, &TStdClsFactory<CLASS>::GetClassObject, PROGID},

#define CLIDMAPENTRY_END 

#define END_CLIDMAP };\
	template<class CLS>\
	const class_object_map* TStdClsFactory<CLS>::GetClassObjectMap(){\
		return g_mapClassObject;\
	}\
	template<class CLS>\
	const long  TStdClsFactory<CLS>::GetClassObjectMapSize(){\
		return sizeof(g_mapClassObject)/sizeof(g_mapClassObject[0]);\
	}\

#define DEFINE_ALL_EXPORTFUN \
	MD_EXPORTS DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv);\
	MD_EXPORTS DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)\
	{\
		for(size_t i = 0; i < sizeof(g_mapClassObject)/sizeof(g_mapClassObject[0]); ++i)\
		{\
			if(rclsid == g_mapClassObject[i].clsid)\
			{\
				return g_mapClassObject[i].pfnGetClassObject(riid, ppv);\
			}\
		}\
		return E_INVALIDARG;\
	}
	
#define END_CLIDMAP_AND_EXPORTFUN };\
	template<class CLS>\
	const class_object_map* TStdClsFactory<CLS>::GetClassObjectMap(){\
		return g_mapClassObject;\
	}\
	template<class CLS> \
	const long TStdClsFactory<CLS>::GetClassObjectMapSize(){\
		return sizeof(g_mapClassObject)/sizeof(g_mapClassObject[0]);\
	}\
	DEFINE_ALL_EXPORTFUN;

																										



#endif


	//////////////////////////////////////////////////////////////////////////


}





#endif // !_COM_FACTORY_H_