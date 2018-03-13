#ifndef _IJAVASCRIPYT_H_
#define _IJAVASCRIPYT_H_

#include <adapter/iadapter.h>

interface IAdapterJavaScript : public IAdapter
{
	
};
MD_DEFINE_IID(IAdapterJavaScript, "{D4FD08F2-BCE4-4A75-A9BF-266409DC4A80}");


// {A484C623-C2A8-4CC0-BBFB-8582687B763F}
MD_DEFINE_GUID(CLSID_AdapaterJavaScript, 
    0xa484c623, 0xc2a8, 0x4cc0, 0xbb, 0xfb, 0x85, 0x82, 0x68, 0x7b, 0x76, 0x3f);

#endif