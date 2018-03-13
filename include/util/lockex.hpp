#ifndef _lockex_H_
#define _lockex_H_

#include <util/core.hpp>


inline static  long lockadd(long* lpAddend){
    #if (TARGET_OS == OS_WINDOWS)
        return InterlockedIncrement(lpAddend);
    #elif (TARGET_OS == OS_POSIX)
        return __sync_add_and_fetch(lpAddend,1);
    #endif    
}

inline static  long lockdel(long* lpAddend){
    #if (TARGET_OS == OS_WINDOWS)
		return InterlockedDecrement(lpAddend);
    #elif (TARGET_OS == OS_POSIX)
        return __sync_sub_and_fetch(lpAddend,1);
    #endif
}

inline static  void lockinit(long* lpAddend) {
	*lpAddend = 0;
}

inline static  void lockuninit(long* lpAddend) {
	*lpAddend = 0;
}



#endif