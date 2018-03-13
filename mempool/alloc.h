#ifndef _PALLOC_H_
#define _PALLOC_H_

#include "stdafx.h"

#define by_memzero(buf, n)       (void) memset(buf, 0, n)
#define by_memset(buf, c, n)     (void) memset(buf, c, n)
#define by_free          free

void* by_alloc(size_t size);
void* by_calloc(size_t size);

#endif /* _PALLOC_H_ */
