#ifndef _IPY_H_
#define _IPY_H_

#include <adapter/iadapter.h>

interface IAdapterPy : public IAdapter
{
	
};
MD_DEFINE_IID(IAdapterPy, "{A7D46745-2E87-4143-B88A-AAD2AF1D9FE0}");

// {69345794-5989-4FEB-AD67-0C3B4FFBA61C}
MD_DEFINE_GUID(CLSID_AdapterPy, 
    0x69345794, 0x5989, 0x4feb, 0xad, 0x67, 0xc, 0x3b, 0x4f, 0xfb, 0xa6, 0x1c);



#endif

