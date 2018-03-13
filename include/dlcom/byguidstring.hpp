#ifndef _BYGUISTRING_H_
#define _BYGUISTRING_H_

#include <dlcom/byguiddef.hpp>

#define GUID_SLEN	40
#define USES_GUIDCONVERSION char lpGuidBuf[GUID_SLEN];



/*


struct nsID {

 

  PRUint32 m0;
  PRUint16 m1;
  PRUint16 m2;
  PRUint8 m3[8];


static const char gIDFormat[] =
  "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}";

#define UID_STRING_LENGTH 39

static void GetIDString(const nsID& aCID, char buf[UID_STRING_LENGTH])
{
    PR_snprintf(buf, UID_STRING_LENGTH, gIDFormat,
                aCID.m0, (PRUint32) aCID.m1, (PRUint32) aCID.m2,
                (PRUint32) aCID.m3[0], (PRUint32) aCID.m3[1],
                (PRUint32) aCID.m3[2], (PRUint32) aCID.m3[3],
                (PRUint32) aCID.m3[4], (PRUint32) aCID.m3[5],
                (PRUint32) aCID.m3[6], (PRUint32) aCID.m3[7]);
}


    char c1 = -1;  
    printf("%02x\n", c1); // ffffffff  
  
    char c2 = 250;  
    printf("%02x\n", c2); // fffffffa  
  
    printf("heheda\n");  
  
    unsigned char c3 = -1;  
    printf("%02x\n", c3); // ff  
  
    unsigned char c4 = 250;  
    printf("%02x\n", c4); // fa  


*/
inline static GUID S2GUIDA(const char* lpString, bool bHaveBracket = true)
{
	GUID guid;
	bzero(&guid, sizeof(GUID));


	if ((bHaveBracket && string_strlen(lpString) != 38) || (!bHaveBracket && string_strlen(lpString) != 36))
		return guid;

	char szTemp[128] = { 0 };
	string_strcpy(szTemp, lpString);


	unsigned int Data234[10] 	= 	{0x00};
	unsigned int Data12[2]	=	{0x00};
	sscanf(szTemp,bHaveBracket?"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}" : "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		(unsigned int*)(&guid.Data1), 
		(unsigned int*)(Data12 + 0), 
		(unsigned int*)(Data12 + 1),
		(unsigned int*)(Data234 + 2), 
		(unsigned int*)(Data234 + 3), 
		(unsigned int*)(Data234 + 4), 
		(unsigned int*)(Data234 + 5),
		(unsigned int*)(Data234 + 6), 
		(unsigned int*)(Data234 + 7), 
		(unsigned int*)(Data234 + 8), 
		(unsigned int*)(Data234 + 9));

	guid.Data2 		= static_cast<unsigned short>(Data12[0]);
	guid.Data3 		= static_cast<unsigned short>(Data12[1]);
	guid.Data4[0] 	= static_cast<unsigned char>(Data234[2]);
	guid.Data4[1] 	= static_cast<unsigned char>(Data234[3]);
	guid.Data4[2] 	= static_cast<unsigned char>(Data234[4]);
	guid.Data4[3] 	= static_cast<unsigned char>(Data234[5]);
	guid.Data4[4] 	= static_cast<unsigned char>(Data234[6]);
	guid.Data4[5] 	= static_cast<unsigned char>(Data234[7]);
	guid.Data4[6] 	= static_cast<unsigned char>(Data234[8]);
	guid.Data4[7] 	= static_cast<unsigned char>(Data234[9]);





	return guid;
};
inline static GUID S2GUIDW(wchar_t* lpString, bool bHaveBracket = true)
{
	GUID guid;
	bzero(&guid, sizeof(GUID));
	//todo it's lpString shit thing
	if ((bHaveBracket && wstring_strlen(lpString) != 38) || (!bHaveBracket && wstring_strlen(lpString) != 36))
		return guid;

	wchar_t szTemp[128] = { 0 };
	wstring_strcpy(szTemp, lpString);

	unsigned int Data234[10] 	= 	{0x00};
	unsigned int Data12[2]		=	{0x00};
	swscanf(szTemp,bHaveBracket?L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}" : L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		(unsigned int*)(&guid.Data1), 
		(unsigned int*)(Data12 + 0), 
		(unsigned int*)(Data12 + 1),
		(unsigned int*)(Data234 + 2), 
		(unsigned int*)(Data234 + 3), 
		(unsigned int*)(Data234 + 4), 
		(unsigned int*)(Data234 + 5),
		(unsigned int*)(Data234 + 6), 
		(unsigned int*)(Data234 + 7), 
		(unsigned int*)(Data234 + 8), 
		(unsigned int*)(Data234 + 9));

	guid.Data2 		= static_cast<unsigned short>(Data12[0]);
	guid.Data3 		= static_cast<unsigned short>(Data12[1]);
	guid.Data4[0] 	= static_cast<unsigned char>(Data234[2]);
	guid.Data4[1] 	= static_cast<unsigned char>(Data234[3]);
	guid.Data4[2] 	= static_cast<unsigned char>(Data234[4]);
	guid.Data4[3] 	= static_cast<unsigned char>(Data234[5]);
	guid.Data4[4] 	= static_cast<unsigned char>(Data234[6]);
	guid.Data4[5] 	= static_cast<unsigned char>(Data234[7]);
	guid.Data4[6] 	= static_cast<unsigned char>(Data234[8]);
	guid.Data4[7] 	= static_cast<unsigned char>(Data234[9]);

	return guid;
};
inline static const char* GUIDToSA(const GUID& guid, char* lpGuidBuf, unsigned long dwSize, bool bHaveBracket = true)
{
	if (bHaveBracket && !(lpGuidBuf && dwSize >= 38))
		return NULL;
	if (!bHaveBracket && !(lpGuidBuf && dwSize >= 36))
		return NULL;

	sprintf(lpGuidBuf,
		bHaveBracket ? "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}" : "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		(unsigned int)guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return lpGuidBuf;
};
inline static const wchar_t* GUIDToSW(const GUID& guid, wchar_t* lpGuidBuf, DWORD dwSize, bool bHaveBracket = true)
{
	if (bHaveBracket && !(lpGuidBuf && dwSize >= 38))
		return NULL;
	if (!bHaveBracket && !(lpGuidBuf && dwSize >= 36))
		return NULL;

	swprintf(lpGuidBuf,
		wcslen(lpGuidBuf),
		bHaveBracket ? L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}" : L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		(unsigned int)guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return lpGuidBuf;
};

#define GUID2SA(guid)			GUIDToSA(guid, lpGuidBuf, GUID_SLEN)
#define GUID2SW(guid)			GUIDToSW(guid, lpGuidBuf, GUID_SLEN)

#define GUID2S_NOBracketA(guid) GUIDToSA(guid, lpGuidBuf, GUID_SLEN, false)
#define GUID2S_NOBracketW(guid) GUIDToSW(guid, lpGuidBuf, GUID_SLEN, false)



#ifdef UNICODE
	#define S2GUID				S2GUIDW
	#define GUIDToS				GUIDToSW
	#define GUID2S				GUID2SW
	#define GUID2S_NOBracket	GUID2S_NOBracketW
#else
	#define S2GUID				S2GUIDA
	#define GUIDToS				GUIDToSA
	#define GUID2S				GUID2SA
	#define GUID2S_NOBracket	GUID2S_NOBracketA
#endif




#endif // !_BYGUISTRING_H_