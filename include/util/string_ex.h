#ifndef _STRING_EX_H_
#define _STRING_EX_H_

#define string_strcpy(x,y)	        strcpy(x,y)
#define string_strcat(x,y)	        strcat(x,y)
#define string_strchr(x,y)		    strchr(x,y)
#define string_strlen(x)		    strlen(x)

#define wstring_strcpy(x,y)	        wcscpy(x,y)
#define wstring_strcat(x,y)	        wcscat(x,y)
#define wstring_strchr(x,y)		    wcschr(x,y)
#define wstring_strlen(x)		    wcslen(x)

#ifdef __GNUC__
#define wstring_stricmp(x,y)	    wcscasecmp(x,y)
#define string_stricmp(x,y)		    strcasecmp(x,y)
#endif

#ifdef _MSC_VER
#define wstring_stricmp(x,y)	    wcsicmp(x,y)
#define string_stricmp(x,y)		    stricmp(x,y)
#endif


#ifdef _UNICODE
#define tstring_strcpy(x,y)	        wcscpy(x,y)
#define tstring_strcat(x,y)	        wcscat(x,y)
#define tstring_strchr(x,y)		    wcschr(x,y)
#define tstring_strlen(x)		    wcslen(x)
#else 
#define tstring_strcpy(x,y)	        strcpy(x,y)
#define tstring_strcat(x,y)	        strcat(x,y)
#define tstring_strchr(x,y)		    strchr(x,y)
#define tstring_strlen(x)		    strlen(x)
#endif


#endif