#ifndef _ILUA_H_
#define _ILUA_H_

#include <adapter/iadapter.h>

interface IAdapterLua : public IAdapter
{
	
};
MD_DEFINE_IID(IAdapterLua, "{DE45CF04-9710-4C78-BC28-1F9FA49F558A}");

// {CDCADFED-0CDA-41B9-B1BA-5FADD5EF2D16}
MD_DEFINE_GUID(CLSID_AdapaterLua, 
    0xcdcadfed, 0xcda, 0x41b9, 0xb1, 0xba, 0x5f, 0xad, 0xd5, 0xef, 0x2d, 0x16);
#endif

