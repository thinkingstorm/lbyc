#ifndef _COMPAT_UNICODETOANSI_H_
#define _COMPAT_UNICODETOANSI_H_

#ifdef _MSC_VER

HRESULT AnsiToUnicode(const char* pszA, wchar_t* ppszW,unsigned long ulen)
{



   /* int sSize       =   strlen(pszA);  
    wchar_t * dBuf  =   NULL;  
    int dSize       =   mbstowcs(dBuf, pszA, 0)+1;
    dBuf            =   new wchar_t[dSize];  
    wmemset(dBuf, 0, dSize);  
    int nRet        =   mbstowcs(dBuf, sBuf, sSize);  
    if(nRet<=0)  
    {  

    }  
    else  
    {  
        
    } 
    
    
    size_t sSize=strlen(sBuf);  
  
wchar_t * dBuf=NULL;  
  
<span style="color:#ff0000;">//注意：需要多分配一个空间，以存放终止符</span>  
int dSize=mbstowcs(dBuf, sBuf, 0)+1;  
  
dBuf=new wchar_t[dSize];  
wmemset(dBuf, 0, dSize);  
  
int nRet=mbstowcs(dBuf, sBuf, sSize);  
    
    
    
    
     */

}

HRESULT __fastcall UnicodeToAnsi(LPCOLESTR pszW, LPSTR* ppszA)
{

		

}

#endif



#endif

