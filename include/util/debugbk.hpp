#ifndef _DEBUGBK_H_
#define _DEBUGBK_H_



inline static void WaitDebug() {
    

        #if (TARGET_OS == OS_WINDOWS)
                DebugBreak();
        #elif (TARGET_OS == OS_POSIX)
	        asm("int3");
        #endif
        
}


#endif