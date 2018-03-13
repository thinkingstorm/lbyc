#ifndef _ASYNIO_H_
#define _ASYNIO_H_


interface IReadFile : public IModuleBase
{

	std_method(LoadFile)(const TCHAR* pszLoadFile,
		unsigned long ulwDesiredAccess,
		unsigned long ulShareMode,
		unsigned long ulCreationDisposition,
		unsigned long ulFlagsAndAttributes)															=	0;
	std_method(CloseFile)()																		=	0;
	std_method_(byint64, GetFileSize)()																=	0;
	std_method(ReadBuffer)(char* szBuffer, byint64 ulReadFileLen, byint64* ulReadSize)				=	0;
	std_method(AsynReadBuffer)(const char* szNodeName,char* szNodeInfo)							=	0;
};

MD_DEFINE_IID(IReadFile, "{9DF32AD9-2C96-446C-B4D4-EC88AFF8A5F9}");


interface IWriteFile : public IModuleBase
{

	std_method(LoadFile)(const char* pszLoadFile,
		unsigned long ulwDesiredAccess,
		unsigned long ulShareMode,
		unsigned long ulCreationDisposition,
		unsigned long ulFlagsAndAttributes)															=	0;
	std_method(CloseFile)()																		=	0;
	std_method(GetFileSize)(unsigned long* ulReadSize)											=	0;
	std_method(WriteBuffer)(const char* szNodeName,char* szNodeInfo)								=   0;
	std_method(AsynWriteBuffer)(const char* szNodeName,char* szNodeInfo)							=   0;
};
MD_DEFINE_IID(IWriteFile, "{6F7C433A-D7C5-4EFB-A525-701A675D7382}");



interface ISocket : public IModuleBase
{
	std_method(CreateSocket)()													=	0;
	std_method(Bind)(const char* addr, unsigned int uport)						=	0;
	std_method_(SOCKET,BindAccept)(const char* addr, unsigned int uport,int n)	=	0;
	std_method(CloseSocket)()													=	0;
	std_method_(ssize_t,Send)(const char* buf,size_t len,int flags)				=	0;
	std_method_(ssize_t,Recv)(char* addr,size_t len,int flags)					=	0;
	std_method_(SOCKET,GetSocket)()												=	0;
	std_method(SetReuseAddr)(bool bstart)										=	0;
	std_method(SetNoDelay)(bool bstart)											=	0;
	std_method(SetLinger)(bool bstart)											=	0;
	std_method(SetKeepalive)(bool bstart)										=	0;
	std_method(SetCork)(bool bstart)											=	0;
	std_method(SetNoSigPipe)(bool bstart)										=	0;
};


//#define SO_SNDBUF       0x1001      // send buffer size
//#define SO_RCVBUF       0x1002      // receive buffer size
//#define SO_SNDLOWAT     0x1003      // send low-water mark
//#define SO_RCVLOWAT     0x1004      // receive low-water mark
//#define SO_SNDTIMEO     0x1005      // send timeout
//#define SO_RCVTIMEO     0x1006      // receive timeout

interface ITcpSocket : public ISocket
{



};
MD_DEFINE_IID(ITcpSocket, "{6F7C433A-D7C5-4EFB-A525-701A675D7388}");

interface IAsynTcpSocket : public ITcpSocket
{

	std_method(SetNonblock)(bool bstart)								=	0;
	std_method(SendBufLen)(int size)									=	0;
	std_method(RecvBufLen)(int size)									=	0;
	std_method(SendTime)(int sec)										=	0;
	std_method(RecvTime)(int sec)										=	0;
	std_method(SendLoWat)(int size)										=	0;
	std_method(RecvLoWat)(int size)										=	0;

};

MD_DEFINE_IID(IAsynTcpSocket, "{6F7C433A-D7C5-4EFB-A525-701A675D7389}");




interface IAsynIo : public IModuleBase
{
	std_method(CreateReadFile)(IModuleBase** pReadFile)				= 0;
	std_method(CreateWriteFile)(IModuleBase** pWriteFile)				= 0;
	std_method(CreateAsynTcpSocket)(IModuleBase** pAsynTcpSocket)		= 0;
	std_method(CreateTcpSocket)(IModuleBase** pTcpSocket)				= 0;
	std_method(CreateAsynUdpSocket)(IModuleBase** pAsynUdpSocket)		= 0;
	std_method(CreateUdpSocket)(IModuleBase** pUdpSocket)				= 0;

	std_method(DeleteIo)(IModuleBase* pAsynIo)						= 0;
};
MD_DEFINE_IID(IAsynIo, "{91559897-31F2-46C1-85AB-1ED97D58EE7B}");



// {B6DDB9B0-186F-4199-A0B3-7BA5026F5888}
MD_DEFINE_GUID(CLSID_IAsynIo,
	0xb6ddb9b0, 0x186f, 0x4199, 0xa0, 0xb3, 0x7b, 0xa5, 0x2, 0x6f, 0x58, 0x88);


#endif // !_ASYNIO_H_