#ifndef _ITPROPERTY_H
#define _ITPROPERTY_H

#include <util/locksection.hpp>
using namespace util;
#include <dlcom/tproperty.impl.h>

namespace by {

	template<class T,class LockType, class KeyLess = less<T> >
	class TProperty_Impl
	{
	public:
		LockType m_lock;
		typedef util::CStackLockWrapper<LockType> SRVATUOLOCK;
	private:
		typedef std::map<T, PROPVARIANT, KeyLess > PROPMAP;
		PROPMAP m_map;

	public: // __tCLSID_CSrvProperty2<T>:
		HRESULT set_property(const T& rpid, const PROPVARIANT *pv)
		{
			SRVATUOLOCK lock(m_lock);
			typename PROPMAP::iterator it = m_map.lower_bound(rpid);
			if(it != m_map.end() && it->first == rpid) { variant_destroy(&it->second); }
			else { it = m_map.insert(it, std::make_pair(rpid, PROPVARIANT())); }
			HRESULT hr = variant_construct_with(&it->second, pv);
			if(FAILED(hr)) { m_map.erase(it); }
			return hr;
		}

		HRESULT get_property(const T& rpid, const PROPVARIANT **ppv)
		{
			SRVATUOLOCK lock(m_lock);

			typename PROPMAP::iterator it = m_map.find(rpid);
			retrtpv(m_map.end() != it, E_INVALIDARG);
			*ppv = &it->second;
			return S_OK;
		}

		HRESULT delete_property(const T& rpid)
		{
			SRVATUOLOCK lock(m_lock);

			typename PROPMAP::iterator it = m_map.find(rpid);
			retrtpv(m_map.end() != it, E_INVALIDARG);
			HRESULT hr = variant_destroy(&it->second);
			m_map.erase(it);
			return hr;
		}

		HRESULT clear()
		{
			SRVATUOLOCK lock(m_lock);

			for(typename PROPMAP::iterator it = m_map.begin(); it != m_map.end(); ++it)
			{
				variant_destroy(&it->second);
			}

			m_map.clear();

			return S_OK;
		}

	public:
		~TProperty_Impl() { clear(); }

	private:
		HRESULT variant_construct_with(PROPVARIANT *pprop, const PROPVARIANT *prhs)
		{
			retrtpv(!((pprop->vt = prhs->vt) & VT_BYREF), (pprop->pszVal = prhs->pszVal, S_OK));
			VARTYPE idEntry = (VARTYPE)(pprop->vt & VT_TYPEMASK);
			retrtpv(idEntry < sizeof(g_tblVariantEntry)/sizeof(g_tblVariantEntry[0]), E_INVALIDARG);
			if(pprop->vt == VT_NULL)
			{
				return S_OK;
			}
			else if(pprop->vt & VT_ARRAY)
			{

				SAFEARRAY **pparray = &pprop->parray, *parray_rhs = prhs->parray;
				retrtpv(g_tblVariantEntry[idEntry].pfn_safearray_construct_with, E_NOTIMPL);
				size_t cb = sizeof(SAFEARRAY);
				if(parray_rhs->cDims > 1) { cb += sizeof(SAFEARRAYBOUND)*(parray_rhs->cDims-1); }
				retrtp(*pparray = (SAFEARRAY*)(new BYTE[cb]), E_OUTOFMEMORY);
				HRESULT hr = g_tblVariantEntry[idEntry].pfn_safearray_construct_with(*pparray, parray_rhs);
				if(FAILED(hr)) { delete *pparray; }
				return hr;
			}
			else if(pprop->vt & VT_VECTOR)
			{
				retrtpv(g_tblVariantEntry[idEntry].pfn_vector_construct_with, E_NOTIMPL);
				return g_tblVariantEntry[idEntry].pfn_vector_construct_with(&pprop->cai, &prhs->cai);
			}
			else
			{
				retrtpv(g_tblVariantEntry[idEntry].pfn_construct_with, E_NOTIMPL);
				return g_tblVariantEntry[idEntry].pfn_construct_with(&pprop->iVal, &prhs->iVal);
			}
		}

		HRESULT variant_destroy(PROPVARIANT *pprop)
		{
			retrtpv(!(pprop->vt & VT_BYREF), S_OK);
			VARTYPE idEntry = (VARTYPE)(pprop->vt & VT_TYPEMASK);
			retrtpv(idEntry < sizeof(g_tblVariantEntry)/sizeof(g_tblVariantEntry[0]), E_UNEXPECTED);
			if(pprop->vt == VT_NULL) 
			{
				return S_OK;
			}
			else if(pprop->vt & VT_ARRAY)
			{
				SAFEARRAY *parray = pprop->parray;
				retrtpv(g_tblVariantEntry[idEntry].pfn_safearray_destroy, E_UNEXPECTED);
				HRESULT hr = g_tblVariantEntry[idEntry].pfn_safearray_destroy(parray);
				delete parray;
				return hr;
			}
			else if(pprop->vt & VT_VECTOR)
			{
				retrtpv(g_tblVariantEntry[idEntry].pfn_vector_destroy, E_UNEXPECTED);
				return g_tblVariantEntry[idEntry].pfn_vector_destroy(&pprop->cai);
			}
			else
			{
				retrtpv(g_tblVariantEntry[idEntry].pfn_destroy, E_UNEXPECTED);
				return g_tblVariantEntry[idEntry].pfn_destroy(&pprop->iVal);
			}
		}
	};

	template<class IFace,	class LockType = CNullCriticalSection, 
							class KeyLess = std::less<typename IFace::KeyType>, 
							class T = typename IFace::KeyType >

	class TProperty : public IFace
		, public IUnknown_Nondelegate
		, private TProperty_Impl<T, LockType, KeyLess>
		, private CUnknownImp_Inner
	{
		typedef	TProperty_Impl<T,LockType, KeyLess>	Impl;
	public: // IUnknown:
		UNKNOWN_INNER_IMP1(IFace);
	public: // std factory invoke:
		std_method(init_class)(IModuleBase* prot, IModuleBase *punkOuter)
		{
			return init_class_inner(punkOuter);
		}
	public:
		std_method(SetProperty)(const T& rpid, const PROPVARIANT *pv) 
		{ 
			return Impl::set_property(rpid, pv); 
		}
		std_method(GetProperty)(const T& rpid, const PROPVARIANT **ppv) 
		{ 
			return Impl::get_property(rpid, ppv);
		}
		std_method(DeleteProperty)(const T& rpid) 
		{ 
			return Impl::delete_property(rpid); 
		}
		std_method(Clear)() 
		{ 
			return Impl::clear(); 
		}
	public:
		virtual ~TProperty() 
		{

		}
	};

} 
#endif 