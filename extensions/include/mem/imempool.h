#ifndef _IMEMPOOL_H
#define _IMEMPOOL_H

enum MemPoolType{
	MEMPOOL_MEMORY 	= 1,
	MEMPOOL_FILE 	= 2
};

interface IMemPool: public IModuleBase
{	
	std_method(MemPool)(MemPoolType type,const char* memfile)			= 0;
	std_method_(void*, Memalloc)(size_t size)							= 0;
	std_method_(void*, MemNalloc)(size_t size)							= 0;
	std_method_(void*, MemNallocalign)(size_t size,size_t alignment)	= 0;
	std_method_(uintptr_t, GetPageSize)()	   	 						= 0;
	std_method(MemPoolFree)()	    									= 0;
	std_method(MemPoolRest)()	    									= 0;
};
MD_DEFINE_IID(IMemPool, "{3B02F308-DBF0-45F2-8302-16E9C9C51FD2}");

// {D1C10177-9BA2-4586-AB8C-0867CAAA7EA1}
MD_DEFINE_GUID(CLSID_IMemPool, 
    0xd1c10177, 0x9ba2, 0x4586, 0xab, 0x8c, 0x8, 0x67, 0xca, 0xaa, 0x7e, 0xa1);













#endif