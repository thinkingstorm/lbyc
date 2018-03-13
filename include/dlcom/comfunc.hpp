#ifndef _STD_COM_H__
#define _STD_COM_H__

#include <dlcom/comsentry.hpp>
#define MAX_PROGIDLEN	100

namespace by {
	//////////////////////////////////////////////////////////////////////////


	inline bool operator < (const GUID& left, const GUID& right)
	{
		return memcmp(&left, &right, sizeof(GUID)) < 0;
	}

	class CUnknownImp
	{
	public:
		ULONG m_RefCount;
		CUnknownImp() :m_RefCount(0)
		{

		}
		virtual ~CUnknownImp()
		{

		}
	};

#define QIBEGIN	\
	std_method(QueryInterface)(REFGUID riid, void **ppv)	{					\

#define QIUNKNOWN	\
	if(re_uuidof(IModuleBase) == riid)											\
	{																			\
		*ppv = static_cast<IModuleBase*>(this);									\
		AddRef();																\
		return S_OK;															\
	}																			\

#define QIUNKNOWN_(icast)														\
	if(re_uuidof(IModuleBase) == riid)											\
	{																			\
		*ppv = static_cast<IModuleBase*>(static_cast<icast*>(this));			\
		AddRef();																\
		return S_OK;															\
	}																			\

#define QIENTRY(iface)															\
	if(re_uuidof(iface) == riid)												\
	{																			\
		*ppv = static_cast<iface*>(this);										\
		AddRef();																\
		return S_OK;															\
	}																			\

#define QIENTRY_(iface, icast)													\
	if(re_uuidof(iface) == riid)												\
	{																			\
		*ppv = static_cast<iface*>(static_cast<icast*>(this));					\
		AddRef();																\
		return S_OK;															\
	}																			\

#define QIEND																	\
	return E_NOINTERFACE; }														\



#define ADDREF																	\
	std_method_(ULONG, AddRef)()												\
	{																			\
		lockadd((LONG*)(LPVOID)&this->m_RefCount);								\
		return this->m_RefCount;												\
	}																			\

#define RELEASE																	\
	std_method_(ULONG, Release)()												\
	{																			\
		lockdel((LONG*)(LPVOID)&this->m_RefCount);								\
		if(this->m_RefCount)													\
			return this->m_RefCount;											\
		delete this;															\
		return 0;																\
	}																			\


#define UNKNOWN_IMP_SPEC(entrys) \
	QIBEGIN  QIUNKNOWN  entrys  QIEND  ADDREF  RELEASE

#define UNKNOWN_IMP_SPEC_(icast, entrys) \
	QIBEGIN  QIUNKNOWN_(icast)  entrys  QIEND  ADDREF  RELEASE


#define ADDREF_EX																\
	std_method_(ULONG, AddRef)()												\
	{																			\
		lockadd((LONG*)(LPVOID)&this->m_RefCount);								\
		return this->m_RefCount;												\
	}																			\

#define RELEASE_EX																\
	std_method_(ULONG, Release)()												\
	{																			\
		lockdel((LONG*)(LPVOID)&this->m_RefCount);								\
		if(this->m_RefCount)													\
			return this->m_RefCount;											\
		delete this;															\
		return 0;																\
	}																			\

#define UNKNOWN_IMP_SPEC_EX(entrys) \
	QIBEGIN  QIUNKNOWN  entrys  QIEND  ADDREF_EX  RELEASE_EX

#define UNKNOWN_IMP1(i) \
	UNKNOWN_IMP_SPEC( QIENTRY(i) )
#define UNKNOWN_IMP2(i1, i2) \
	UNKNOWN_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) )
#define UNKNOWN_IMP3(i1, i2, i3) \
	UNKNOWN_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) )
#define UNKNOWN_IMP4(i1, i2, i3, i4) \
	UNKNOWN_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) )
#define UNKNOWN_IMP5(i1, i2, i3, i4, i5) \
	UNKNOWN_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) QIENTRY(i5) )

#define UNKNOWN_IMP1_(i) \
	UNKNOWN_IMP_SPEC_( QIENTRY(i) )
#define UNKNOWN_IMP2_(i1, i2) \
	UNKNOWN_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) )
#define UNKNOWN_IMP3_(i1, i2, i3) \
	UNKNOWN_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) )
#define UNKNOWN_IMP4_(i1, i2, i3, i4) \
	UNKNOWN_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) )
#define UNKNOWN_IMP5_(i1, i2, i3, i4, i5) \
	UNKNOWN_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) QIENTRY(i5) )


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	class IUnknown_Nondelegate
	{
	public:
		std_method(QueryInterface_Nondelegate)(REFGUID riid, void **ppv)	= 0;
		std_method_(ULONG, AddRef_Nondelegate)()							= 0;
		std_method_(ULONG, Release_Nondelegate)()							= 0;
	};


	class CUnknownImp_Inner
	{
	public:
		ULONG m_RefCount;
		CUnknownImp_Inner() : m_RefCount(0), m_punkOuter(0) 
		{

		}
	public:
		IModuleBase *m_punkOuter;
		HRESULT init_class_inner(IModuleBase *punkOuter)
		{
			m_punkOuter = punkOuter;
			return S_OK;
		}
	};



#define QIBEGIN_NONDELEGATE														\
	std_method(QueryInterface_Nondelegate)(REFGUID riid, void **ppv) {

#define QIUNKNOWN_NONDELEGATE													\
	if(re_uuidof(IModuleBase) == riid)											\
	{																			\
		*ppv = static_cast<IUnknown_Nondelegate*>(this);						\
		AddRef_Nondelegate();													\
		return S_OK;															\
	}																			\

#define QIUNKNOWN_NONDELEGATE_(icast)											\
	if(re_uuidof(IModuleBase) == riid)											\
	{																			\
		*ppv = static_cast<IUnknown_Nondelegate*>(static_cast<icast*>(this));	\
		AddRef_Nondelegate();													\
		return S_OK;															\
	}																			\

#define ADDREF_NONDELEGATE														\
	std_method_(ULONG, AddRef_Nondelegate)()									\
	{																			\
		lockadd((LONG*)(LPVOID)&this->m_RefCount);								\
		return this->m_RefCount;												\
	}																			\

#define RELEASE_NONDELEGATE														\
	std_method_(ULONG, Release_Nondelegate)()									\
	{																			\
		lockdel((LONG*)(LPVOID)&this->m_RefCount);								\
		if(this->m_RefCount)													\
			return this->m_RefCount;											\
		delete this ;															\
		return 0;																\
	}																			\

#define QI_INNER																\
	std_method(QueryInterface)(REFGUID riid, void **ppv)						\
	{																			\
		if(m_punkOuter)															\
		{																		\
			return m_punkOuter->QueryInterface(riid, ppv);						\
		}																		\
		else																	\
		{																		\
			return QueryInterface_Nondelegate(riid, ppv);						\
		}																		\
	}																			\

#define ADDREF_INNER															\
	std_method_(ULONG, AddRef)()												\
	{																			\
		if(m_punkOuter)															\
		{																		\
			return m_punkOuter->AddRef();										\
		}																		\
		else																	\
		{																		\
			return AddRef_Nondelegate();										\
		}																		\
	}																			\

#define RELEASE_INNER															\
	std_method_(ULONG, Release)()												\
	{																			\
		if(m_punkOuter)															\
		{																		\
			return m_punkOuter->Release();										\
		}																		\
		else																	\
		{																		\
			return Release_Nondelegate();										\
		}																		\
	}																			\

#define UNKNOWN_INNER_IMP_SPEC(entrys) \
	QIBEGIN_NONDELEGATE  QIUNKNOWN_NONDELEGATE  entrys  QIEND  ADDREF_NONDELEGATE  RELEASE_NONDELEGATE  QI_INNER  ADDREF_INNER  RELEASE_INNER

#define UNKNOWN_INNER_IMP_SPEC_(icast, entrys) \
	QIBEGIN_NONDELEGATE  QIUNKNOWN_NONDELEGATE_(icast)  entrys  QIEND  ADDREF_NONDELEGATE  RELEASE_NONDELEGATE  QI_INNER  ADDREF_INNER  RELEASE_INNER

#define UNKNOWN_INNER_IMP1(i) \
	UNKNOWN_INNER_IMP_SPEC( QIENTRY(i) )
#define UNKNOWN_INNER_IMP2(i1, i2) \
	UNKNOWN_INNER_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) )
#define UNKNOWN_INNER_IMP3(i1, i2, i3) \
	UNKNOWN_INNER_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) )
#define UNKNOWN_INNER_IMP4(i1, i2, i3, i4) \
	UNKNOWN_INNER_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) )
#define UNKNOWN_INNER_IMP5(i1, i2, i3, i4, i5) \
	UNKNOWN_INNER_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) QIENTRY(i5) )
#define UNKNOWN_INNER_IMP2_(i1, i2) \
	UNKNOWN_INNER_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) )
#define UNKNOWN_INNER_IMP3_(i1, i2, i3) \
	UNKNOWN_INNER_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) )
#define UNKNOWN_INNER_IMP4_(i1, i2, i3, i4) \
	UNKNOWN_INNER_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) )
#define UNKNOWN_INNER_IMP5_(i1, i2, i3, i4, i5) \
	UNKNOWN_INNER_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) QIENTRY(i5) )


#define QIEND_OUTER \
	return m_punkInner->QueryInterface(riid, ppv); }

#define UNKNOWN_OUTER_IMP_SPEC(entrys) \
	QIBEGIN  QIUNKNOWN  entrys  QIEND_OUTER  ADDREF  RELEASE
#define UNKNOWN_OUTER_IMP_SPEC_(icast, entrys) \
	QIBEGIN  QIUNKNOWN_(icast)  entrys  QIEND_OUTER  ADDREF  RELEASE
#define UNKNOWN_OUTER_IMP0 \
	QIBEGIN  QIUNKNOWN  QIEND_OUTER  ADDREF  RELEASE



#define UNKNOWN_OUTER_IMP1(i) \
	UNKNOWN_OUTER_IMP_SPEC( QIENTRY(i) )
#define UNKNOWN_OUTER_IMP2(i1, i2) \
	UNKNOWN_OUTER_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) )
#define UNKNOWN_OUTER_IMP3(i1, i2, i3) \
	UNKNOWN_OUTER_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) )
#define UNKNOWN_OUTER_IMP4(i1, i2, i3, i4) \
	UNKNOWN_OUTER_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) )
#define UNKNOWN_OUTER_IMP5(i1, i2, i3, i4, i5) \
	UNKNOWN_OUTER_IMP_SPEC( QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) QIENTRY(i5) )


#define UNKNOWN_OUTER_IMP2_(i1, i2) \
	UNKNOWN_OUTER_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) )
#define UNKNOWN_OUTER_IMP3_(i1, i2, i3) \
	UNKNOWN_OUTER_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) )
#define UNKNOWN_OUTER_IMP4_(i1, i2, i3, i4) \
	UNKNOWN_OUTER_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) )
#define UNKNOWN_OUTER_IMP5_(i1, i2, i3, i4, i5) \
	UNKNOWN_OUTER_IMP_SPEC_(i1, QIENTRY(i1) QIENTRY(i2) QIENTRY(i3) QIENTRY(i4) QIENTRY(i5) )


	class CUnknownImp_Outer
	{
	public:
		ULONG m_RefCount;
		CUnknownImp_Outer() : m_RefCount(0) 
		{

		}
	public:
		com_ptr<IModuleBase> m_punkInner;
		HRESULT init_class_outer(IModuleBase *prot, IModuleBase *punkThisOuter, const CLSID& rclsid)
		{
			retrtpv(prot, E_INVALIDARG);

			com_ptr<IComRunningObjectTable> pRot(prot);
			retrtpv(pRot, E_INVALIDARG);

			com_ptr<IObjectLoader> pol;
			RFAILED(pRot->GetObject(CLSID_CObjectLoader, re_uuidof(IObjectLoader), (IModuleBase**)&pol));

			RFAILED(pol->CreateInstance(prot, rclsid, punkThisOuter, re_uuidof(IModuleBase), (void**)&m_punkInner));

			return S_OK;
		}
	};



}
	


#endif
