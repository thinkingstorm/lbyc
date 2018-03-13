#ifndef _ASYNIOIMPL_H_
#define _ASYNIOIMPL_H_

#include "stdafx.h"
#include <compat/getpath.hpp>
#include <sshchannel/isschannel.h>
#include <io/iasynio.h>

class CSshChannelImpl : 	public	ISshChannel,
							public  IMdPlugin,
							public  IMdPluginRun,
							public	CUnknownImp
{
public:
	CSshChannelImpl(void);
	virtual ~CSshChannelImpl(void);

	UNKNOWN_IMP3_(IMdPlugin, IMdPluginRun,ISshChannel);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	std_method_impl init_class(IModuleBase* prot, IModuleBase* punkOuter);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	std_method(Init)(void*);
	std_method(Uninit)();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	std_method(Start)();
	std_method(Stop)();

	//////////////////////////////////////////////////////////////////////////

    std_method_(sshid, CreateSshChannel)();
    std_method(CloseChannel)(sshid id);
    std_method_(ssize_t, SendChannel)(sshid id,char* buf,size_t len);
    std_method_(ssize_t, RecvChannel)(sshid id,char* buf,size_t len);


	//////////////////////////////////////////////////////////////////////////
private:
	_lComPtr<IComRunningObjectTable>	m_pRot;
	_lComPtr<IAsynIo>					m_pIAsynIo;
private:
	typedef struct TagSshSession {
		ITcpSocket*			pSocket;
	}SshSession;
	typedef map<sshid,ITcpSocket*>		MapChannel;
	MapChannel							m_mapSschannel;


};
#endif
