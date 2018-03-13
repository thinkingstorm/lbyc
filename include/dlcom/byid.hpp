
#ifndef _BYID_H_
#define _BYID_H_

#include <dlcom/byguidstring.hpp>

template<class T>
struct memless
{
	bool operator() (const T&left, const T&right) const
	{
		return memcmp(&left, &right, sizeof(T)) < 0;
	}
};


template<class T>
class __uuid_s
{
public:
	static GUID iid;
};



#ifdef __GNUC__

#define re_uuidof(DerivedType)					(__uuid_s<DerivedType>::iid)
#define md_uuidof(iface)						(__uuid_s<iface>::iid)


#else
#define re_uuidof(DerivedType)					__uuidof(DerivedType)
#define md_uuidof(iface)						__uuidof(iface)
#endif


#ifndef DECLSPEC_UUID
#ifdef _MSC_VER
#define DECLSPEC_UUID(x) __declspec(uuid(x))
#else
#define DECLSPEC_UUID(x)
#endif

#endif



#ifndef DECLSPEC_SELECTANY
#define DECLSPEC_SELECTANY

#ifdef _MSC_VER
#define DECLSPEC_SELECTANY  __declspec(selectany)
#else
#define DECLSPEC_SELECTANY
#endif

#endif


#ifndef MIDL_INTERFACE
#define MIDL_INTERFACE(x)   struct DECLSPEC_UUID(x) BY_NO_VTABLE
#endif





#ifdef __GNUC__
#define MD_DEFINE_UUID(name,u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15) \
        static const uuid_t name __attribute__ ((unused)) = {u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15}

#define	MD_DEFINE_IID(iface, uuid_string)	\
	template<> GUID __attribute__((weak)) __uuid_s<iface>::iid = S2GUIDA(uuid_string);


#define MD_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        EXTERN_C const GUID __attribute__((weak)) name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

//#define DEFINE_OLEGUID(name, l, w1, w2) DEFINE_GUID(name, l, w1, w2, 0xC0,0,0,0,0,0,0,0x46)

#else

#define MD_DEFINE_UUID(name,u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15) \
        static const uuid_t name = {u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15};

#define MD_DEFINE_IID(iface, uuid_string)	struct __declspec(uuid(uuid_string)) iface

#define MD_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	EXTERN_C const GUID DECLSPEC_SELECTANY name \
	= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

//#define DEFINE_OLEGUID(name, l, w1, w2) DEFINE_GUID(name, l, w1, w2, 0xC0,0,0,0,0,0,0,0x46)

#endif

#ifndef GUID_NULL
MD_DEFINE_GUID(GUID_NULL, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
#endif


#endif

