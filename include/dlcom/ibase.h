#ifndef _IBASE_H
#define _IBASE_H

#include <dlcom/byunknown.hpp>

#if (TARGET_OS == OS_WINDOWS)

#elif (TARGET_OS == OS_POSIX)
#include <dlcom/propvariant.h>
#elif (TAGET_OS == OS_MAC)
#include <dlcom/propvariant.h>
#endif

namespace by {

	interface IComObjectFrameworkClassFactory: public IClassFactory__
	{
	public:
		std_method(CreateInstance)(IModuleBase *prot, IModuleBase *punkOuter, REFIID riid, void **ppvObject) =0;
		std_method_(CLSID, GetAt)(LONG nIndex) = 0;
		std_method_(LONG, GetCount)() = 0;
		std_method_(LPCSTR, ProgIDFromCLSID)(REFCLSID clsid) = 0;
	};

	MD_DEFINE_IID(IComObjectFrameworkClassFactory,"{6966E385-DBFA-4131-A29E-D0E9464F3F53}");
	// {E2247B54-E329-4ca8-8361-6499FDFF98F4}
	MD_DEFINE_GUID(CLSID_ComObjectFrameworkClassFactory,
				   0xe2247b54, 0xe329, 0x4ca8, 0x83, 0x61, 0x64, 0x99, 0xfd, 0xff, 0x98, 0xf4);

	interface IProperty : public IModuleBase
	{
		typedef GUID KeyType;
		std_method(SetProperty)(const GUID& rpid, const PROPVARIANT *pv) = 0;
		std_method(GetProperty)(const GUID& rpid, const PROPVARIANT **ppv) = 0;
		std_method(DeleteProperty)(const GUID& rpid) = 0;
		std_method(Clear)() = 0;
	};
	MD_DEFINE_IID(IProperty, "{39AA125E-D7F1-46b1-82EB-6D8527269279}");
	// {ED20E0E5-2357-4825-B3FA-198AEC674E81}
	MD_DEFINE_GUID(CLSID_CProperty, 
				   0xed20e0e5, 0x2357, 0x4825, 0xb3, 0xfa, 0x19, 0x8a, 0xec, 0x67, 0x4e, 0x81);
	// {AD4F3A47-0CD6-43de-BC22-E8BE24FFD424}
	MD_DEFINE_GUID(CLSID_CProperty_thread, 
				   0xad4f3a47, 0xcd6, 0x43de, 0xbc, 0x22, 0xe8, 0xbe, 0x24, 0xff, 0xd4, 0x24);
	//-------------------------------------------------------------------------------
	interface IProperty2 : public IModuleBase
	{
		typedef DWORD KeyType;

		std_method(SetProperty)(const DWORD& rpid, const PROPVARIANT *pv) = 0;
		std_method(GetProperty)(const DWORD& rpid, const PROPVARIANT **ppv) = 0;
		std_method(DeleteProperty)(const DWORD& rpid) = 0;
		std_method(Clear)() = 0;
	};
	MD_DEFINE_IID(IProperty2, "{21C975F4-EEE1-4c90-8D39-7D94A6AEDAB7}");
	// {2100E98D-B13E-4306-8081-50F325B10586}
	MD_DEFINE_GUID(CLSID_CProperty2, 
				   0x2100e98d, 0xb13e, 0x4306, 0x80, 0x81, 0x50, 0xf3, 0x25, 0xb1, 0x5, 0x86);
	// {0AEF80FB-9BAF-4e66-96B3-784ED0FCECF1}
	MD_DEFINE_GUID(CLSID_CProperty2_thread, 
				   0xaef80fb, 0x9baf, 0x4e66, 0x96, 0xb3, 0x78, 0x4e, 0xd0, 0xfc, 0xec, 0xf1);

	//com factory you must define
	// {E9678781-A3CB-46fb-9121-3ED22C24CFAD}
	MD_DEFINE_GUID(CLSID_MDClassFactory,
		0xe9678781, 0xa3cb, 0x46fb, 0x91, 0x21, 0x3e, 0xd2, 0x2c, 0x24, 0xcf, 0xad);



} 
#endif 