
#include "alloc.h"

void* by_alloc(size_t size, ngx_log_t *log)
{
    void  *p = NULL;
    p = malloc(size);
    if (p == NULL) {

    }
    return p;
}

void* by_calloc(size_t size)
{
    void  *p = NULL;

    p = by_alloc(size);

    if (p) {
        by_memzero(p, size);
    }
    return p;
}
