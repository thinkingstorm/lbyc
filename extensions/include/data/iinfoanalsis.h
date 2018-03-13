#ifndef _INFOANALYSIS_H_
#define _INFOANALYSIS_H_


#pragma pack(1)
typedef LPVOID InfoNode;
interface InfoRoot : public IModuleBase
{
	std_method(LoadData)(char* data)																= 0;
	std_method(GetRootNode)(InfoNode* Node)														= 0;
	std_method(GetNode)(InfoNode Node, const char* szNodeName, InfoNode* ChildNode)				= 0;
	std_method_(const char*,GetStringValue)(InfoNode Node, const char* szNodeName)				= 0;
	std_method_(int, GetIntValue)(InfoNode Node, const char* szNodeName)							= 0;
	std_method_(double, GetDoubleValue)(InfoNode Node, const char* szNodeName)					= 0;
	std_method_(int, GetNodeCount)(InfoNode Node, unsigned long *ulSize)							= 0;
	std_method(GetNodeIndexNode)(InfoNode Node, unsigned long ulIndex, InfoNode* ChildNode)		= 0;
};
#pragma pack()
MD_DEFINE_IID(InfoRoot, "{0771D5F4-EBD0-4AB8-B8A1-2D0F49842C01}");



#pragma pack(1)
interface IInfoAnalysis : public IModuleBase
{
	std_method(NewObject)(const char* data, IModuleBase** Root)									= 0;
	std_method(NewLoadFileObject)(const TCHAR* filepath, IModuleBase** Root)						= 0;
	std_method(DelObject)(IModuleBase* Root)														= 0;
};
#pragma pack()
MD_DEFINE_IID(IInfoAnalysis, "{179AFDE4-3C51-4c5a-86B0-C7B61092E106}");



#pragma pack(1)
interface IDataJsonToXML : public IModuleBase
{
	std_method(JsonToXML)(const char* input, char*  output, unsigned long ulen) = 0;
	std_method(XMLToJson)(const char* input, char*  output, unsigned long ulen) = 0;
};
#pragma pack()
MD_DEFINE_IID(IDataJsonToXML, "{CF1B54BF-144E-442C-8BA4-60C7CAE0F193}");


// {E2C3154C-AFC7-4875-8BCC-CB116CA0CF45}
MD_DEFINE_GUID(CLSID_InfoAnalysis,
	0xe2c3154c, 0xafc7, 0x4875, 0x8b, 0xcc, 0xcb, 0x11, 0x6c, 0xa0, 0xcf, 0x45);


#endif