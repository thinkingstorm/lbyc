#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

#include <dlcom/byunknown.hpp>

namespace by {

	interface IMdPlugin : public IModuleBase
	{
		std_method(Init)(void*) = 0;
		std_method(Uninit)() 	= 0;
	};
	MD_DEFINE_IID(IMdPlugin, "{74252668-870B-4c27-B69D-C6E199C6D3D5}");

	interface IMdPluginRun : public IModuleBase
	{
		std_method(Start)() 	= 0;
		std_method(Stop)() 		= 0;
	};
	MD_DEFINE_IID(IMdPluginRun, "{24AE3325-4FE1-4c03-8765-6C3C967D9D44}");
}
#endif
