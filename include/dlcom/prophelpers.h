

#pragma once
#include <dlcom/propvariant.h>
#include <dlcom/combase.h>
#include <tchar.h>

#define VT_BUFFER	(VT_UI1|VT_VECTOR)
#define VT_DATETIME	(VT_UI2|VT_VECTOR)

//--------------------------------------------------------------------
//	Type & VARTYPE conversions
//--------------------------------------------------------------------
template<class T> 
struct Type2Var
{
	enum { _vt = VT_EMPTY }; 
};

#define PROPTYPEDEF( type, vt ) \
template<> struct Type2Var<type> { enum { _vt = vt }; }; \

PROPTYPEDEF( char,				VT_I1 )
PROPTYPEDEF( BYTE,				VT_UI1 )
PROPTYPEDEF( short,				VT_I2 )
PROPTYPEDEF( unsigned short,	VT_UI2 )
PROPTYPEDEF( int,				VT_INT )
PROPTYPEDEF( unsigned int,		VT_UINT )
PROPTYPEDEF( long,				VT_I4 )
PROPTYPEDEF( unsigned long,		VT_UI4 )
PROPTYPEDEF( LONGLONG,			VT_I8 )
PROPTYPEDEF( const char*,		VT_LPSTR )
PROPTYPEDEF( char*,				VT_LPSTR )
PROPTYPEDEF( wchar_t*,			VT_LPWSTR )
PROPTYPEDEF( const wchar_t*,	VT_LPWSTR )
PROPTYPEDEF( CLSID*,			VT_CLSID )

#define IsNumericType(vt) !( vt&VT_VECTOR || vt==VT_LPSTR || vt==VT_LPWSTR || vt==VT_CLSID)


class CPropVar : public PROPVARIANT
{
public:
	static VOID PropInit( PROPVARIANT * pvar )
	{
		memset( pvar, 0, sizeof(PROPVARIANT) );
	}

	CPropVar()
	{
		PropInit( this );
	}

	CPropVar( const PROPVARIANT& var )
	{
		memcpy( this, &var, sizeof(PROPVARIANT) );
	}

	CPropVar( const PROPVARIANT* pVar )
	{
		memcpy( this, pVar, sizeof(PROPVARIANT) );
	}

	template<class T>
	CPropVar( const T src )
	{
		PropInit( this );

		vt = Type2Var<T>::_vt;
		*(T*)&cVal = src;
	}

	CPropVar( const GUID& guid )
	{
		PropInit( this );

		vt = VT_CLSID;
		puuid = (CLSID*)&guid;
	}

	CPropVar( const SYSTEMTIME& sysTime )
	{
		PropInit( this );

		SetVector( (WORD*)&sysTime, sizeof(sysTime)/sizeof(DWORD) );
	}

	template<class T>
	CPropVar( T* src, int nElem )
	{
		PropInit( this );

		SetVector( src, nElem );
	}

	template<class T>
	VOID SetVector( T* src, int nElem )
	{
		vt = Type2Var<T>::_vt | VT_VECTOR;
		cac.cElems = nElem;
		cac.pElems = (char*)src;
	}

	template<>
	VOID SetVector<CLSID>( CLSID* src, int nElem )
	{
		vt = VT_CLSID | VT_VECTOR;
		cauuid.cElems = nElem;
		cauuid.pElems = src;
	}

	template<>
	VOID SetVector<VOID>( VOID* src, int nElem )
	{
		vt = VT_BUFFER;
		cac.cElems = nElem;
		cac.pElems = (char*)src;
	}


	template<class T>
	CPropVar& operator=( const T src )
	{
		vt = Type2Var<T>::_vt;
		*(T*)&cVal = src;

		return *this;
	}

	CPropVar& operator=( const GUID& guid )
	{
		vt = Type2Var<CLSID*>::_vt;
		puuid = (CLSID*)&guid;

		return *this;
	}

	CPropVar& operator=( const SYSTEMTIME& sysTime )
	{
		SetVector( (WORD*)&sysTime, sizeof(sysTime)/sizeof(WORD) );

		return *this;
	}

	// Comparison operators
	//
	bool operator!()
	{
		return vt==VT_NULL;
	}

	// Extractors
	//
	template<class T>
	operator T () const
	{
		VARTYPE targetType = Type2Var<T>::_vt;

		if( vt == targetType )
			return *(T*)&cVal;

		if( IsNumericType(vt) && IsNumericType(targetType) )
			return *(T*)&cVal;

		return 0;
	}

	operator GUID* () const
	{
		if( vt == VT_CLSID )
			return puuid;

		if( vt == VT_BUFFER && cac.cElems==sizeof(GUID) )
			return (GUID*)cac.pElems;

		return NULL;
	}

	operator GUID () const
	{
		if( vt == VT_CLSID )
			return *puuid;

		if( vt == VT_BUFFER && cac.cElems==sizeof(GUID) )
			return *(GUID*)cac.pElems;
		
		GUID guid;
		memset( &guid, 0, sizeof(guid) );
		return guid;
	}

	operator SYSTEMTIME () const
	{

		SYSTEMTIME sysTime = {0};

		if( vt==VT_LPSTR || vt==VT_LPWSTR )
		{
			LPCTSTR szTime = *this;
			if( _tcschr( szTime, _T('-') ) )
			{
				_stscanf_s( szTime, _T("%d-%d-%d %d:%d:%d"), 
					&sysTime.wYear, &sysTime.wMonth, &sysTime.wDay,
					&sysTime.wHour, &sysTime.wMinute, &sysTime.wSecond );
			}
			else if( _tcschr( szTime, _T('/') ) )
			{
				_stscanf_s( szTime, _T("%d/%d/%d %d:%d:%d"), 
					&sysTime.wYear, &sysTime.wMonth, &sysTime.wDay,
					&sysTime.wHour, &sysTime.wMinute, &sysTime.wSecond );
			}
		}
		else if( vt==VT_DATETIME )
		{
			memcpy( &sysTime, cac.pElems, sizeof(SYSTEMTIME) );
		}

		return sysTime;
	}

	template<class T>
	VOID GetVector( T** ppVec, int& nElem ) const
	{
		if( vt == (Type2Var<T>::_vt|VT_VECTOR) )
		{
			nElem = cac.cElems;
			*ppVec = (T*)cac.pElems;
		}
		else
		{
			nElem = 0;
			*ppVec = NULL;
		}
	}

	template<>
	VOID GetVector<CLSID>( CLSID** ppVec, int& nElem ) const
	{
		if( vt == (VT_CLSID|VT_VECTOR) )
		{
			nElem = cauuid.cElems;
			*ppVec = cauuid.pElems;
		}
		else
		{
			nElem = 0;
			*ppVec = NULL;
		}
	}

	template<>
	VOID GetVector<VOID>( VOID** ppVec, int& nElem ) const
	{
		if( vt == VT_BUFFER )
		{
			nElem = cac.cElems;
			*ppVec = cac.pElems;
		}
		else
		{
			nElem = 0;
			*ppVec = NULL;
		}
	}

	static CPropVar GetNull( VOID )
	{
		CPropVar valNull;
		valNull.vt = VT_NULL;

		return valNull;
	}
};



//--------------------------------------------------------------------

//	
//	ISrvProperty2	*pProp;		
//	
//	CPropSet props( pProp );
//	props[0] = 123;
//	props[1] = _T("Uger");
//	props[2] = re_uuidof(IGenericRS);
//	props[3] = pBuffer;		



//	
//	ISrvProperty2	*pProp;		
//	
//	CPropSet props( pProp );
//	
//	ULONG id = props[0];
//	LPCTSTR szName = props[1];
//	GUID guid = props[2];
//	IUnknown* pBuffer = props[3];
//	
//	BYTE data[100] = {0};
//	CPropVar var( data, 100 );
//	props[4] = var;
//
//	int nLen;
//	LPVOID pBuffer;
//	prop4[4].Val().GetVector( &pBuffer, nLen );
//	
//--------------------------------------------------------------------
template<	
			class IFace, 
			class TVarWrap = CPropVar,
			class T = typename IFace::KeyType 
		>
class CPropVars
{
public:
	class CVarBind
	{
	public:
		CVarBind( IFace* pProps, T key )
			: m_key(key)
		{
			m_pProps = pProps;
		}

		TVarWrap Val() const
		{
			const PROPVARIANT* pVar = NULL;
			HRESULT hr = m_pProps->GetProperty( m_key, &pVar );

			if( hr==S_OK && pVar )
				return TVarWrap( pVar );
			else
				return TVarWrap();
		}

		CVarBind& operator=( TVarWrap var )
		{
			m_pProps->SetProperty( m_key, (PROPVARIANT*)&var );

			return *this;
		}

		template<class TRet>
		operator TRet ()
		{
			return (TRet)Val();
		}

	public:
		IFace*	m_pProps;
		T		m_key;
	};

	CPropVars( VOID )
	{
		m_pProps = NULL;
	}

	CPropVars( IUnknown* pProps )
	{
		if( pProps )
			pProps->QueryInterface(re_uuidof(IFace), (void**)&m_pProps );
	}

	~CPropVars()
	{
		if( m_pProps )
			m_pProps->Release();
	}

	CPropVars& operator=( IFace* pProps )
	{
		if( pProps )
			pProps->QueryInterface(re_uuidof(IFace), (void**)&m_pProps );
		return *this;
	}


	CVarBind operator[]( T key )
	{
		return CVarBind( m_pProps, key );
	}

	VOID Clear()
	{
		if( m_pProps )
			m_pProps->Clear();
	}

	HRESULT Reset( IFace* pNew )
	{
		if( m_pProps )
		{
			m_pProps->Release();
			m_pProps = NULL;
		}

		return pNew->QueryInterface(re_uuidof(IFace), (void**)&m_pProps );
	}

	IFace* GetFace( VOID )
	{
		return m_pProps;
	}

public:
	IFace*	m_pProps;
};

typedef  CPropVars<IProperty2> CPropSet;






