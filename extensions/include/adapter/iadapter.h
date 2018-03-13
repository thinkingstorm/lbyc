#ifndef _IADAPTER_H_
#define _IADAPTER_H_

interface IAdapter : public IModuleBase
{
	std_method(RunFile)(const char* file) = 0;
};


enum AdaptersType{
	AT_LUA	=	1,
	AT_JS	=	2,
	AT_PY	=	3
};

interface IAdapters : public IModuleBase
{
	std_method(RegisterFunc)(const char* file) 		= 0;
	std_method(RegisterVariable)(const char* file) 	= 0;
	std_method(CallFunc)(const char* file) 			= 0;
};

MD_DEFINE_IID(IAdapters, "{8205BA0A-30D5-4C55-8719-C68B5ADEE243}");

// {74785A7F-55A5-4DE4-9030-059DF97C7B70}
MD_DEFINE_GUID(CLSID_Adapters, 
	0x74785a7f, 0x55a5, 0x4de4, 0x90, 0x30, 0x5, 0x9d, 0xf9, 0x7c, 0x7b, 0x70);


#endif



