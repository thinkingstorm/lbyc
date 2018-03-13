#ifndef _SOCKETDEF_H_
#define _SOCKETDEF_H_

        #if (TARGET_OS == OS_WINDOWS)
        
            typedef SSIZE_T     ssize_t;

        #elif (TARGET_OS == OS_POSIX)
            #define	SOCKET		    int
            #define INVALID_SOCKET   -1
        #endif

#endif