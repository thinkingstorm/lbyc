#ifndef _CALLDLL_H_
#define _CALLDLL_H_

#include <util/util.h>

namespace util {


	#ifndef offsetof
	#define offsetof(s,m) ((size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))
	#endif // !offsetof

	class BY_NO_VTABLE IImpModuleBase
	{
	public:
		struct STFunDesc
		{
			char *pFunName;
			size_t uOffFun;
		};
	public:
		enum{
			FLAG_USEHMODULE=1,
				FLAG_LOADED=2,
		};
		TCHAR m_szModuleName[MAX_PATH];
			
		HMODULE m_hMod;
		unsigned int m_uFlags;		
		virtual void InitIAT()
		{
			STFunDesc *pFunDesc=GetFunDefs();
			while(pFunDesc->pFunName)
			{
				//*(void**)(((char*)this)+pFunDesc->uOffFun)=(void*)0;			
				pFunDesc++;
			}
		}
	public:
		IImpModuleBase(HMODULE hMod):
		m_hMod(hMod),
		m_uFlags(FLAG_USEHMODULE)
		{		
		}
		IImpModuleBase(const TCHAR *pModuleName):m_hMod(NULL),m_uFlags(FLAG_LOADED)
		{
		}
		virtual ~IImpModuleBase()
		{
			UnLoad();
		}	
		virtual int Load(const TCHAR* szPath = NULL)
		{
			STFunDesc *pFunDesc=GetFunDefs();
			int iRet=0;
			HMODULE hMod = NULL;
			if (m_uFlags & FLAG_USEHMODULE)
				hMod = m_hMod;
			else
			{
				if(szPath && szPath[0] && m_szModuleName[0])
				{					
					TCHAR buf[260] = {0x00};
					tstring_strcpy(buf, szPath);
					if(szPath[tstring_strlen(szPath)-1] != _T('\\'))
						tstring_strcat(buf, _T("\\"));
					tstring_strcat(buf, m_szModuleName);
					m_hMod	= openmd(buf);
					hMod	= m_hMod;
				}
				else
					m_hMod	=	openmd(m_szModuleName);
					hMod	=	m_hMod;
			}
			if (!hMod)
				iRet=-1;
			else
			{
				while(string_stricmp(pFunDesc->pFunName,"null") != 0)
				{
					void *p = openfunc(hMod,pFunDesc->pFunName);

					//*(void**)(((char*)this)+pFunDesc->uOffFun)=p;
					setfuncaddress(pFunDesc->uOffFun,p);
					if (!p)
					{
						iRet++;
						if(Exception(iRet, hMod, pFunDesc->pFunName))
							return iRet;
					}
					pFunDesc++;
				}
			}	
			return iRet;
		}
		virtual int UnLoad()
		{
			if (m_uFlags & FLAG_LOADED)
			{
				if(m_hMod)
				{
					closemd(m_hMod);				
				}
				m_hMod = NULL;
				//InitIAT();
			}
			return 0;
		}
		virtual bool IsLoaded()
		{
			return NULL != m_hMod;
		}
		virtual bool Exception(int iCount, HMODULE hModule, const char* lpProcName)
		{
			return true;
		}
		virtual STFunDesc *GetFunDefs() 			= 0;
		virtual bool setfuncaddress(int i,void *p) 	= 0;
	};

	template <class tDerived>
	class BY_NO_VTABLE tImpModuleMid : public IImpModuleBase
	{	
	public:	
		typedef tDerived DerivedType;
		inline tImpModuleMid(const TCHAR *pName) : IImpModuleBase(pName)
		{

		}
		inline tImpModuleMid(HMODULE hMod) : IImpModuleBase(hMod)
		{

		}
	};
}


#endif 
