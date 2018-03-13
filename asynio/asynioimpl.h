#ifndef _ASYNIOIMPL_H_
#define _ASYNIOIMPL_H_

#include "stdafx.h"
#include <io/iasynio.h>


class CAsynIoImpl : public	IAsynIo,
					public  IMdPlugin,
					public  IMdPluginRun,
					public	CUnknownImp
{
public:
	CAsynIoImpl(void);
	virtual ~CAsynIoImpl(void);
	

	UNKNOWN_IMP3_(IMdPlugin, IMdPluginRun,IAsynIo);
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


	std_method(CreateReadFile)(IModuleBase** pReadFile);
	std_method(CreateWriteFile)(IModuleBase** pWriteFile);
	std_method(CreateAsynTcpSocket)(IModuleBase** pAsynTcpSocket);
	std_method(CreateTcpSocket)(IModuleBase** pTcpSocket);
	std_method(CreateAsynUdpSocket)(IModuleBase** pAsynUdpSocket);
	std_method(CreateUdpSocket)(IModuleBase** pUdpSocket);
	std_method(DeleteIo)(IModuleBase* pAsynIo);

private:
	_lComPtr<IComRunningObjectTable>	m_pRot;

};
#endif