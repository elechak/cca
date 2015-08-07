/*
The blue programming language ("blue")
Copyright (C) 2007  Erik R Lechak

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
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "cca/splaytree.c"

struct MemoryManager{
    SplayTree store;
};
typedef struct MemoryManager * MemoryManager;

struct MemoryChunk{
    size_t size;
    MemoryManager mman;
    unsigned char data[];
};
typedef struct MemoryChunk * MemoryChunk;

MemoryChunk native_allocate(MemoryManager mman, size_t size){
    MemoryChunk self = malloc(sizeof(*self) + size);
    self->size = size;
    self->mman = mman;
    return self;
}

int comp(MemoryChunk a, MemoryChunk b){
    return b->size - a->size;
}

MemoryManager memorymanager(){
    MemoryManager self = malloc(sizeof(*self));
    self->store = splaytree_new((Comparator)comp);
    return self;
}

void * alloc(MemoryManager self, size_t size){
    MemoryChunk mc = NULL;
    if (self->store->size){
        mc = splaytree_get(self->store, &size);
        if (mc)return mc->data;
    }

    //printf("Native allocate\n");

    mc = native_allocate(self, size);
    return mc->data;
}

void dealloc(void * mem){
    MemoryChunk mc = NULL;
    mc = (MemoryChunk)(((char *)(mem)) - offsetof(struct MemoryChunk, data));
    splaytree_insert(mc->mman->store, mc);
    //printf( "freeing memory size %i\n",mc->size);
}





int main(int argc, char **argv){
    char * p;
    //MemoryManager mm = memorymanager();
    int c;

    for (c=0; c<10000000; c++){

        p = malloc(512);
        free(p);

        //p = alloc(mm, 512);
        //strcpy(p, "erik");
        //printf( " %i   %s\n", offsetof(struct MemoryChunk, data), p);
        //dealloc(p);
    }

    return 0;
}








