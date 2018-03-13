#ifndef _TCPSOCKIMPL_H_
#define _TCPSOCKIMPL_H_



#include "stdafx.h"
#include <io/iasynio.h>

class CTcpSocketImpl :	public	ITcpSocket,
						public	CUnknownImp

{
public:
	CTcpSocketImpl(void);
	virtual ~CTcpSocketImpl(void);
	UNKNOWN_IMP1(ITcpSocket);
	//////////////////////////////////////////////////////////////////////////
	std_method(CreateSocket)();
	std_method(Bind)(const char* addr, unsigned int uport);
	std_method_(SOCKET,BindAccept)(const char* addr, unsigned int uport,int n);
	std_method(CloseSocket)();
	std_method_(ssize_t,Send)(const char* buf,size_t len,int flags);
	std_method_(ssize_t,Recv)(char* addr,size_t len,int flags);
	std_method_(SOCKET,GetSocket)();
	std_method(SetReuseAddr)(bool bstart);
	std_method(SetNoDelay)(bool bstart);
	std_method(SetLinger)(bool bstart);
	std_method(SetKeepalive)(bool bstart);
	std_method(SetCork)(bool bstart);
	std_method(SetNoSigPipe)(bool bstart);

    //////////////////////////////////////////////////////////////////////////
	SOCKET		m_socketFd;



private:



};







#endif