#ifndef _ROOTIMPL_H_
#define _ROOTIMPL_H_

#include "stdafx.h"
#include <data/iinfoanalsis.h>
#include "cjson.h"


class CRootImpl :	public	InfoRoot,
					public	CUnknownImp 
{
public:
	CRootImpl();
	~CRootImpl();
	UNKNOWN_IMP1(InfoRoot);

public:
	std_method(LoadData)(char* data);
	std_method(GetRootNode)(InfoNode* Node);
	std_method(GetNode)(InfoNode Node, const char* szNodeName, InfoNode* ChildNode);
	std_method_(const char*, GetStringValue)(InfoNode Node, const char* szNodeName);
	std_method_(int, GetIntValue)(InfoNode Node, const char* szNodeName);
	std_method_(double, GetDoubleValue)(InfoNode Node, const char* szNodeName);
	std_method_(int, GetNodeCount)(InfoNode Node, unsigned long *ulSize);
	std_method(GetNodeIndexNode)(InfoNode Node, unsigned long ulIndex, InfoNode* ChildNode);

private:
	unsigned long	m_ulen;
	struct json_sentry
	{
		static void* default_value()
		{
			return 0;
		}
		template<class _Ptr> static bool equal_to(_Ptr l, _Ptr r)
		{
			return l == r;
		}
		template<class _Ptr> static void destroy(_Ptr p)
		{
			if (p != NULL)
				cJSON_Delete(p);
		}
	};
	sentry<cJSON*, json_sentry> m_pJson;
	sentry<char*, default_array_sentry> m_pdata;

};


#endif // !_ROOTIMPL_H_