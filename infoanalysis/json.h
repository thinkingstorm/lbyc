#ifndef _JSON_H_
#define _JSON_H_

#include "cjson.h"
#include <string>
using namespace std;
class CJson
{
public:
	static string Json2Xml(const string &strJson);
	static string Xml2Json(const string &strxml);
	static void remove_char(string &str, char c);  
	static string&  replace_all(string& str, const string& old_value, const string& new_value);
	static string GetXmlKey(const string &strxml);
	static string GetXmlValueFromKey(const string &strxml, const string &strKey);
	static string GoToNextItem(const string &strxml, const string &strKey);
	static int GetArrayItem(const string stxml);   
	static string GetNumFromJson(const string& strJson, const string& strKey);
};

#endif

