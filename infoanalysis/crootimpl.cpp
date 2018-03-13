#include "crootimpl.h"


CRootImpl::CRootImpl()
{

}
CRootImpl::~CRootImpl()
{

}
std_method_impl CRootImpl::LoadData(char* data)
{
	HRESULT		hr = S_OK;

	m_ulen = string_strlen(data);
	m_ulen = m_ulen + 1;
	m_pdata = Memory_Allocate char[m_ulen];
	string_strcpy(m_pdata, data);
	m_pJson = cJSON_Parse(m_pdata);

	return hr;
}
std_method_impl CRootImpl::GetRootNode(InfoNode* Node)
{
	HRESULT		hr = S_OK;

	cJSON*	pNode = reinterpret_cast<cJSON*>(m_pJson.m_p);
	retrtpv(pNode, E_FAIL);
	*Node = reinterpret_cast<InfoNode*>(pNode);
	return hr;
}
std_method_impl CRootImpl::GetNode(InfoNode Node, const char* szNodeName, InfoNode* ChildNode)
{
	HRESULT		hr = S_OK;

	cJSON*	pNode = reinterpret_cast<cJSON*>(Node);
	retrtpv(pNode, E_FAIL);
	retrtpv(cJSON_IsObject(pNode), E_FAIL);
	cJSON* item = cJSON_GetObjectItem(pNode, szNodeName);
	*ChildNode = reinterpret_cast<InfoNode*>(item);

	return hr;
}
std_method_type_impl(const char*) CRootImpl::GetStringValue(InfoNode Node, const char* szNodeName)
{
	cJSON*	pNode = reinterpret_cast<cJSON*>(Node);
	retrtpv(pNode, "");
	retrtpv(cJSON_IsObject(pNode), "");
	return (const char*)cJSON_GetObjectItem(pNode, szNodeName)->valuestring;
}
std_method_type_impl(int) CRootImpl::GetIntValue(InfoNode Node, const char* szNodeName)
{
	cJSON*	pNode = reinterpret_cast<cJSON*>(Node);
	retrtpv(pNode, -1);
	retrtpv(cJSON_IsObject(pNode), -1);
	return cJSON_GetObjectItem(pNode, szNodeName)->valueint;
}
std_method_type_impl(double) CRootImpl::GetDoubleValue(InfoNode Node, const char* szNodeName)
{
	cJSON*	pNode = reinterpret_cast<cJSON*>(Node);
	retrtpv(pNode, 0.0);
	retrtpv(cJSON_IsObject(pNode), 0.0);
	return cJSON_GetObjectItem(pNode, szNodeName)->valuedouble;
}
std_method_type_impl(int) CRootImpl::GetNodeCount(InfoNode Node, unsigned long *ulSize)
{
	cJSON*	pNode = reinterpret_cast<cJSON*>(Node);
	retrtpv(pNode, -1);
	retrtpv(cJSON_IsArray(pNode), -1);
	return cJSON_GetArraySize(pNode);
}
std_method_impl CRootImpl::GetNodeIndexNode(InfoNode Node, unsigned long ulIndex, InfoNode* ChildNode)
{
	HRESULT		hr = S_OK;
	cJSON*	pNode = reinterpret_cast<cJSON*>(Node);
	retrtpv(pNode, E_FAIL);
	retrtpv(cJSON_IsArray(pNode), E_FAIL);
	cJSON* item = cJSON_GetArrayItem(pNode, ulIndex);
	*ChildNode = reinterpret_cast<InfoNode*>(item);
	return hr;
}


