#include "sshchannelimpl.h"


CSshChannelImpl::CSshChannelImpl(void)
{
}

CSshChannelImpl::~CSshChannelImpl(void)
{
}
//////////////////////////////////////////////////////////////////////////
std_method_impl CSshChannelImpl::init_class(IModuleBase* prot, IModuleBase* punkOuter)
{
	HRESULT		hr	=	S_OK;
	if (prot != NULL)
	{
		m_pRot	=	prot;
	}
	return hr;
}
std_method_impl CSshChannelImpl::Init(void*)
{
	HRESULT		hr	=	S_OK;


	return hr;
}
std_method_impl CSshChannelImpl::Uninit()
{
	HRESULT		hr	=	S_OK;

	return hr;
}
std_method_impl CSshChannelImpl::Start()
{
	HRESULT		hr	=	S_OK;

	m_pRot->GetObject(CLSID_IAsynIo,re_uuidof(IAsynIo),(IModuleBase**)&m_pIAsynIo.m_p);
	retrtpv(m_pIAsynIo,E_FAIL)

	return hr;
}
std_method_impl CSshChannelImpl::Stop()
{
	HRESULT		hr	=	S_OK;

	WaitDebug();
	
	return hr;
}

std_method_type_impl(sshid) CSshChannelImpl::CreateSshChannel()
{
	retrtpv(m_pIAsynIo,E_FAIL)
	ITcpSocket* pSock = NULL;
	HRESULT hr = m_pIAsynIo->CreateTcpSocket((IModuleBase**)&pSock);
	RFAILEDV(hr,-1)
	retrtpv(pSock,-1)
	pSock->CreateSocket();
	m_mapSschannel[pSock->GetSocket()] = pSock;
	return pSock->GetSocket();
}
std_method_impl CSshChannelImpl::CloseChannel(sshid id)
{
	MapChannel::iterator it	= m_mapSschannel.find(id);
	retrtpv(it != m_mapSschannel.end(),E_FAIL)
	m_mapSschannel.erase(id);
	return (*it).second->CloseSocket();
}
std_method_type_impl(ssize_t) CSshChannelImpl::SendChannel(sshid id,char* buf,size_t len)
{
    return -1;
}
std_method_type_impl(ssize_t) CSshChannelImpl::RecvChannel(sshid id,char* buf,size_t len)
{
    return -1;
}






