#ifndef _PROPVARIANT_H_
#define _PROPVARIANT_H_


#if defined(OS_POSIX) || defined(OS_MAC)

enum VARENUM
{
	VT_EMPTY	= 0,
	VT_NULL	= 1,
	VT_I2	= 2,
	VT_I4	= 3,
	VT_R4	= 4,
	VT_R8	= 5,
	VT_CY	= 6,
	VT_DATE	= 7,
	VT_BSTR	= 8,
	VT_DISPATCH	= 9,
	VT_ERROR	= 10,
	VT_BOOL	= 11,
	VT_VARIANT	= 12,
	VT_UNKNOWN	= 13,
	VT_DECIMAL	= 14,
	VT_I1	= 16,
	VT_UI1	= 17,
	VT_UI2	= 18,
	VT_UI4	= 19,
	VT_I8	= 20,
	VT_UI8	= 21,
	VT_INT	= 22,
	VT_UINT	= 23,
	VT_VOID	= 24,
	VT_HRESULT	= 25,
	VT_PTR	= 26,
	VT_SAFEARRAY	= 27,
	VT_CARRAY	= 28,
	VT_USERDEFINED	= 29,
	VT_LPSTR	= 30,
	VT_LPWSTR	= 31,
	VT_RECORD	= 36,
	VT_INT_PTR	= 37,
	VT_UINT_PTR	= 38,
	VT_FILETIME	= 64,
	VT_BLOB	= 65,
	VT_STREAM	= 66,
	VT_STORAGE	= 67,
	VT_STREAMED_OBJECT	= 68,
	VT_STORED_OBJECT	= 69,
	VT_BLOB_OBJECT	= 70,
	VT_CF	= 71,
	VT_CLSID	= 72,
	VT_VERSIONED_STREAM	= 73,
	//
	VT_BSTR_BLOB	= 0xfff,
	//
	VT_VECTOR	= 0x1000,
	VT_ARRAY	= 0x2000,
	VT_BYREF	= 0x4000,
	VT_RESERVED	= 0x8000,
	VT_ILLEGAL	= 0xffff,
	VT_ILLEGALMASKED	= 0xfff,
	VT_TYPEMASK	= 0xfff
};

//////////////////////////////////////////////////////////////////////////

typedef unsigned short VARTYPE;

typedef WORD PROPVAR_PAD1;
typedef WORD PROPVAR_PAD2;
typedef WORD PROPVAR_PAD3;

typedef struct tagPROPVARIANT PROPVARIANT;

#define TYPEDEF_CA(type, name) \
    typedef struct tag ## name {\
        ULONG cElems;\
        type *pElems;\
        } name

TYPEDEF_CA(CHAR, CAC);
TYPEDEF_CA(UCHAR, CAUB);
TYPEDEF_CA(SHORT, CAI);
TYPEDEF_CA(USHORT, CAUI);
TYPEDEF_CA(LONG, CAL);
TYPEDEF_CA(ULONG, CAUL);
TYPEDEF_CA(LARGE_INTEGER, CAH);
TYPEDEF_CA(ULARGE_INTEGER, CAUH);
TYPEDEF_CA(FLOAT, CAFLT);
TYPEDEF_CA(DOUBLE, CADBL);
TYPEDEF_CA(VARIANT_BOOL, CABOOL);
TYPEDEF_CA(SCODE, CASCODE);
TYPEDEF_CA(CLSID, CACLSID);
TYPEDEF_CA(LPSTR, CALPSTR);
TYPEDEF_CA(LPWSTR, CALPWSTR);


typedef struct  tagSAFEARRAYBOUND {
	ULONG              cElements;
	LONG               lLbound;
} SAFEARRAYBOUND;
 
typedef struct  tagSAFEARRAY {
	USHORT             cDims;
	USHORT             fFeatures;
	ULONG              cbElements;
	ULONG              cLocks;
	PVOID              pvData;
	SAFEARRAYBOUND     rgsabound [ 1 ];
} SAFEARRAY, *LPSAFEARRAY;

struct tagPROPVARIANT
{
	VARTYPE vt;
	PROPVAR_PAD1 wReserved1;
	PROPVAR_PAD2 wReserved2;
	PROPVAR_PAD3 wReserved3;
	union 
	{
		CHAR cVal;
		UCHAR bVal;
		SHORT iVal;
		USHORT uiVal;
		LONG lVal;
		ULONG ulVal;
		INT intVal;
		UINT uintVal;
		LARGE_INTEGER hVal;
		ULARGE_INTEGER uhVal;
		FLOAT fltVal;
		DOUBLE dblVal;
		VARIANT_BOOL boolVal;
		SCODE scode;
 		FILETIME filetime;
		CLSID *puuid;
 		BSTR bstrVal;
		LPSTR pszVal;
		LPWSTR pwszVal;
		ISupports *punkVal;
		LPSAFEARRAY parray;
		CAC cac;
		CAUB caub;
		CAI cai;
		CAUI caui;
		CAL cal;
		CAUL caul;
		CAH cah;
		CAUH cauh;
		CAFLT caflt;
		CADBL cadbl;
		CABOOL cabool;
		CASCODE cascode;
		CACLSID cauuid;
		CALPSTR calpstr;
		CALPWSTR calpwstr;
		CHAR *pcVal;
		UCHAR *pbVal;
		SHORT *piVal;
		USHORT *puiVal;
		LONG *plVal;
		ULONG *pulVal;
		INT *pintVal;
		UINT *puintVal;
		FLOAT *pfltVal;
		DOUBLE *pdblVal;
		VARIANT_BOOL *pboolVal;
		SCODE *pscode;
		ISupports **ppunkVal;
	};
};


typedef struct tagPROPVARIANT PROPVARIANT;

#endif // #ifdef _WIN32


#endif // duplicate inclusion protection
