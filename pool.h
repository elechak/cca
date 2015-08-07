


#ifndef _POOL
#define _POOL

#include <stdlib.h>

#ifdef REENTRANT
    #include "threading.h"
#endif

struct Pool{
    size_t capacity;
    size_t top;
    void ** entries;
    void * (*alloc) ();
    void (*dealloc) (void *);
    #ifdef REENTRANT
        Mutex mutex;
    #endif
};
typedef struct Pool * Pool;

Pool pool_new(size_t size, void* (*alloc) () , void (*dealloc) (void *) );
void pool_free(Pool self);
void * pool_get(Pool self);
void pool_store(Pool self, void * obj);
void * pool_try_store(Pool self, void * obj);

Pool pool_new_nt(size_t size, void* (*alloc) () , void (*dealloc) (void *) );
void pool_free_nt(Pool self);
void * pool_get_nt(Pool self);
void pool_store_nt(Pool self, void * obj);


#endif

