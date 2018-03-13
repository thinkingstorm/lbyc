#ifndef _IYANGCONTEXT_H_
#define _IYANGCONTEXT_H_



interface IYangModuleInfo : public IModuleBase
{
	std_method_(const char*,GetName)()              =   0;
    std_method_(const char*,GetVersion)()           =   0;
    std_method_(const char*,GetPrefix)()            =   0;
	std_method_(const char*,GetNs)()                =   0;
    std_method_(const char*,GetFilepath)()          =   0;
    std_method_(const char*,GetDsc)()               =   0;
    std_method_(const char*,GetRef)()               =   0;
    std_method_(const char*,GetOrg)()               =   0;
    std_method_(const char*,GetContact)()           =   0;
};
MD_DEFINE_IID(IYangModuleInfo, "{DAE6E1A0-BDCF-4940-838D-0FB844CA11C3}");



interface IYangContext : public IModuleBase
{
    std_method(InitYangFiles)(const char* files)                                =   0;
    std_method(LoadModule)(const char* file,IModuleBase** pYangFile)            =   0;
    std_method(ParseModule)(const char* file,IModuleBase** pYangFile)           =   0;
    std_method_(const char* const*,GetSearchdirs)()                             =   0;

};
MD_DEFINE_IID(IYangContext, "{6CDEEC0C-970D-4559-BA2E-9F4C460FFEC1}");

// {1EFECF2D-B556-4EDB-9B2B-9CAC17AAC4F7}
MD_DEFINE_GUID(CLSID_YangContext, 
    0x1efecf2d, 0xb556, 0x4edb, 0x9b, 0x2b, 0x9c, 0xac, 0x17, 0xaa, 0xc4, 0xf7);


#endif