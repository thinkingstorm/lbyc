#ifndef _CINFOANLYSISIMPL_H_ 
#define _CINFOANLYSISIMPL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include <data/iinfoanalsis.h>


class CInfoAnalysisImpl :	public  IInfoAnalysis,
							public  IDataJsonToXML,
							public  IMdPlugin,
							public  IMdPluginRun,
							public	CUnknownImp
{
public:
	CInfoAnalysisImpl(void);
	~CInfoAnalysisImpl(void);


	UNKNOWN_IMP4_(IMdPlugin, IMdPluginRun,IInfoAnalysis,IDataJsonToXML);
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
	std_method(NewObject)(const char* data, IModuleBase** ioNodeInfo);
	std_method(NewLoadFileObject)(const TCHAR* filepath, IModuleBase** ioNodeInfo);
	std_method(DelObject)(IModuleBase* ioNodeInfo);
	//////////////////////////////////////////////////////////////////////////
	std_method(JsonToXML)(const char* input, char*  output, unsigned long ulen);
	std_method(XMLToJson)(const char* input, char*  output, unsigned long ulen);

private:

	_lComPtr<IComRunningObjectTable>				m_pRot;

};
#endif