#ifndef _CALLFUNC_H_
#define _CALLFUNC_H_


#include <util/core.hpp>

#ifndef RTLD_LAZY
#define RTLD_LAZY 1
#endif 

namespace util {
	
	inline static HMODULE openmd(TCHAR* path,int flag = RTLD_LAZY) {
        #if (TARGET_OS == OS_WINDOWS)
		    return ::LoadLibraryW(path);
        #elif (TARGET_OS == OS_POSIX)
                //init function ???
		    return dlopen(path,flag);
        #endif


    }

	inline static void* openfunc(HMODULE handler,char* sym){
        #if (TARGET_OS == OS_WINDOWS)
            return ::GetProcAddress(handler,sym);
        #elif (TARGET_OS == OS_POSIX)
            void* pFunc = dlsym(handler,sym);
            if (pFunc == NULL){
                char* pszErr = dlerror();
                printf("%s\n",pszErr);
                return pFunc;
            }
            return pFunc;
        #endif
    }
	inline static int closemd(HMODULE handler){
        #if (TARGET_OS == OS_WINDOWS)
            return ::FreeLibrary(handler);
        #elif (TARGET_OS == OS_POSIX)
            return dlclose(handler);
        #endif
    }
}
#endif