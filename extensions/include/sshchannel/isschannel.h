#ifndef _ISSHCHANNEL_H_
#define _ISSHCHANNEL_H_

typedef long sshid;

interface ISshChannel : public IModuleBase
{
    std_method_(sshid, CreateSshChannel)()                                              =   0;
    std_method(CloseChannel)(sshid id)                                                  =   0;
    std_method_(ssize_t, SendChannel)(sshid id,char* buf,size_t len)                    =   0;
    std_method_(ssize_t, RecvChannel)(sshid id,char* buf,size_t len)                    =   0;
};
MD_DEFINE_IID(ISshChannel, "{45BAC576-355D-4D08-8B86-0283BE3E7FBF}");

interface ISshCliObj : public ISshChannel
{
    std_method(CreateConnectChannel)(sshid id,const char* adder,uint uport)             =   0;
};
MD_DEFINE_IID(ISshCliObj, "{D2F5C0A1-EAE9-4C6B-B9DF-5716935E930D}");

interface ISshSrvObj : public ISshChannel
{
    std_method_(sshid, CreateAcceptChannel)(sshid id,const char* adder,uint uport)      =   0;
};
MD_DEFINE_IID(ISshSrvObj, "{520BB6DE-BD39-43D7-9452-983141E0C00F}");


// {4A27FA11-BEA7-46E8-9F32-EC0C9F6E1A9E}
MD_DEFINE_GUID(CLSID_SshChannel, 
    0x4a27fa11, 0xbea7, 0x46e8, 0x9f, 0x32, 0xec, 0xc, 0x9f, 0x6e, 0x1a, 0x9e);

#endif