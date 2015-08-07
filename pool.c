/*
The blue programming language ("blue")
Copyright (C) 2007-2008  Erik R Lechak

email: erik@lechak.info
web: www.lechak.info

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "pool.h"
#include "stdio.h"

Pool pool_new(size_t size, void* (*alloc) () , void (*dealloc) (void *) ){
    Pool self = malloc(sizeof (*self));
    self->capacity = size;
    self->top = 0;
    self->alloc = alloc;
    self->dealloc = dealloc;
    self->entries = malloc(sizeof(*(self->entries)) * size);
    #ifdef REENTRANT
        self->mutex = mutex_new();
    #endif
    return self;
}

void pool_free(Pool self){
    
    #ifdef REENTRANT
    mutex_lock(self->mutex);
    #endif
    
    size_t c;
    if (self->dealloc){
        for(c=0; c<self->top; c++){
            self->dealloc(self->entries[c]);
        }
    }
    
    free(self->entries);
    
    #ifdef REENTRANT
    mutex_unlock(self->mutex);
    free(self->mutex);
    #endif

    free(self);
}



void * pool_get(Pool self){
    void * ret = NULL;
    
    #ifdef REENTRANT
    mutex_lock(self->mutex);
    #endif

    if (self->top){
        ret = self->entries[--self->top];
    }else{
        if(self->alloc) ret = self->alloc();
    }
    
    #ifdef REENTRANT
    mutex_unlock(self->mutex);
    #endif
    
    return ret;
}

void * pool_try_store(Pool self, void * obj){
    
    #ifdef REENTRANT
    mutex_lock(self->mutex);
    #endif

    if (self->top < self->capacity){
        self->entries[self->top++] = obj;
        #ifdef REENTRANT
        mutex_unlock(self->mutex);
        #endif
        return NULL;
    }

    #ifdef REENTRANT
     mutex_unlock(self->mutex);
    #endif
    
    /* can't fit object into pool so return it */

    return obj;
}



void pool_store(Pool self, void * obj){
    
    void * ret = pool_try_store( self , obj);
    
    if (ret){        
        if (self->dealloc){
            self->dealloc(obj);
        }
    }
}


/* NO-THREAD VERSION */

Pool pool_new_nt(size_t size, void* (*alloc) () , void (*dealloc) (void *) ){
    Pool self = malloc(sizeof (*self));
    self->capacity = size;
    self->top = 0;
    self->alloc = alloc;
    self->dealloc = dealloc;
    self->entries = malloc(sizeof(*(self->entries)) * size);
    #ifdef REENTRANT
        self->mutex = NULL;
    #endif
    return self;
}

void pool_free_nt(Pool self){
    size_t c;
    if (self->dealloc){
        for(c=0; c<self->top; c++){
            self->dealloc(self->entries[c]);
        }
    }
    
    free(self->entries);
    if (self->mutex) free(self->mutex);
    free(self);
}



void * pool_get_nt(Pool self){
    void * ret = NULL;
    
    if (self->top){
        ret = self->entries[--self->top];
    }else{
        if(self->alloc) ret = self->alloc();
    }
        
    return ret;
}


void pool_store_nt(Pool self, void * obj){
    
    if (self->top < self->capacity){
        self->entries[self->top++] = obj;

        return;
    }
    
    if (self->dealloc){
        self->dealloc(obj);
    }
}


















