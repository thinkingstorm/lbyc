#include "json.h"
#include <iostream>
using namespace std;

void CJson::remove_char(string &str, char c)
{
	while (1)
	{
		string::size_type nPos = str.find_first_of(c);
		if (nPos != string::npos)
		{
			str = str.substr(0, nPos) + str.substr(nPos + 1, -1);
		}
		else
			break;
	}
}

string&  CJson::replace_all(string& str, const string& old_value, const string& new_value)
{
	while (true)
	{
		string::size_type   pos(0);
		if ((pos = str.find(old_value)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else
			break;
	}
	return   str;
}

string CJson::Json2Xml(const string &strJson)
{
	return "";
}

string CJson::Xml2Json(const string &strxml)
{
	return "";
}

string CJson::GetXmlKey(const string &strxml)
{
	int nKeyS = strxml.find("<");
	int nKeyE = strxml.find(">");
	if (nKeyE == -1 || nKeyS == -1)
	{
		return "";
	}

	string strKey = strxml.substr(nKeyS + 1, nKeyE - nKeyS - 1);
	return strKey;
}

string CJson::GetXmlValueFromKey(const string &strxml, const string &strKey)
{
	int nValueE = strxml.find("</" + strKey + ">");
	int nValueS = strxml.find(">");

	if (-1 == nValueE || nValueS == -1)
	{
		return "";
	}

	string strValue = strxml.substr(nValueS + 1, nValueE - nValueS - 1);
	return strValue;
}

string CJson::GoToNextItem(const string &strxml, const string &strKey)
{
	int nPos = strxml.find("</" +  strKey + ">");
	string strNext = strxml.substr(nPos + strKey.size() + 3);
	return strNext;
}

int CJson::GetArrayItem(const string stxml)
{
	string strKey = GetXmlKey(stxml);
	int iCnt = 0;
	string strNextXml = stxml;
	string strNextKey = "";
	while (true)
	{
		strNextXml = GoToNextItem(strNextXml, strKey);
		strNextKey = GetXmlKey(strNextXml);

		if (strNextKey != strKey)
		{
			break;
		}
		iCnt++;
	}
	return iCnt + 1;
}

string CJson::GetNumFromJson(const string& strJson, const string& strKey)
{
	string strNum = "";
	string::size_type nPos = strJson.find(strKey);
	if (nPos != string::npos)
	{
		string strItem = strJson.substr(nPos);
		int nFirst = strItem.find(":");
		int nEnd = 0;
		const char *pTemp = strItem.c_str();
		while (NULL != pTemp && '\0' != *pTemp && (!isalpha(*pTemp) || ' ' == *pTemp))
		{
			pTemp++;
		}
		return strItem.substr(nFirst, nEnd - nFirst);
	}
	return "";
}
