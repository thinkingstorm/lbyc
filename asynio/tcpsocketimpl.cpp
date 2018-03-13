#include "tcpsocketimpl.h"

CTcpSocketImpl::CTcpSocketImpl()
{
	m_socketFd	=	-1;
}
CTcpSocketImpl::~CTcpSocketImpl()
{
    
}
//////////////////////////////////////////////////////////////////////////


std_method_impl CTcpSocketImpl::CreateSocket()
{
	HRESULT		hr	=	S_OK;

    m_socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_socketFd == INVALID_SOCKET) {
        return E_FAIL;
    }

	return hr;
}
std_method_impl CTcpSocketImpl::Bind(const char* addr, unsigned int uport)
{
	HRESULT		hr	=	S_OK;

	retrtpv(addr,E_FAIL)
	retrtpv(uport,E_FAIL)

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
    if (INADDR_NONE == (sin.sin_addr.s_addr = inet_addr(addr))) {
        return E_FAIL;
    }
    sin.sin_port = htons(uport);
    if (connect(m_socketFd, (struct sockaddr*)(&sin),sizeof(struct sockaddr_in)) != 0) {
        return E_FAIL;
    }

	return hr;
}
std_method_type_impl(SOCKET) CTcpSocketImpl::BindAccept(const char* addr, unsigned int uport,int n)
{
	return -1;
}
std_method_impl CTcpSocketImpl::CloseSocket()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_type_impl(ssize_t) CTcpSocketImpl::Send(const char* buf,size_t len,int flags)
{
	return -1;
}
std_method_type_impl(ssize_t) CTcpSocketImpl::Recv(char* addr,size_t len,int flags)
{
	return -1;
}
std_method_type_impl(SOCKET) CTcpSocketImpl::GetSocket()
{
	return m_socketFd;
}
std_method_impl CTcpSocketImpl::SetReuseAddr(bool bstart)
{
	HRESULT		hr	=	S_OK;
	
	return hr;
}
std_method_impl CTcpSocketImpl::SetNoDelay(bool bstart)
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CTcpSocketImpl::SetLinger(bool bstart)
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CTcpSocketImpl::SetKeepalive(bool bstart)
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CTcpSocketImpl::SetCork(bool bstart)
{
	HRESULT		hr	=	S_OK;
	int set = 0;
	set = (bstart == true? 1 : 0);
	setsockopt (m_socketFd, SOL_TCP, TCP_CORK, (void *)&set, sizeof(int));
	return hr;
}
std_method_impl CTcpSocketImpl::SetNoSigPipe(bool bstart)
{

	HRESULT		hr	=	S_OK;

	int set = 0;
	set = (bstart == true? 1 : 0);

	//unix no found MSG_NOSIGNAL, but have SO_NOSIGPIPE
	
#if defined(SO_NOSIGPIPE) && !defined(MSG_NOSIGNAL)
	#define MSG_NOSIGNAL SO_NOSIGPIPE
#endif

	setsockopt(m_socketFd, SOL_SOCKET, MSG_NOSIGNAL, (void *)&set, sizeof(int)); 

	



	return hr;
}


