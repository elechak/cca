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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "directory.h"

Directory directory_new(Comparator c){
    Directory self = malloc(sizeof(*self));
    self->array = skiparray_new();
    self->tree  = splaytree_new(c);
    return self;
}


void directory_free(Directory self){
    if (self->tree) splaytree_free(self->tree);
    if (self->array)skiparray_free(self->array);
    free(self);
}


void directory_add(Directory self , void * data){
    skiparray_append(self->array, data);
    splaytree_insert(self->tree, data);
}

void * directory_deleteIndex(Directory self, size_t index){
    void * element = skiparray_delete(self->array , index);
    if ( ! element) return NULL;
    splaytree_delete(self->tree, element);
    return element;
}

void * directory_deleteKey(Directory self , void * key){
    int  c;
    void * element = splaytree_delete(self->tree, key);

    if ( ! element) return NULL;

    c = skiparray_find(self->array, element, self->tree->cmp);
    skiparray_delete(self->array , c);

    return element;
}

void * directory_byKey(Directory self, void * key){
    return splaytree_get(self->tree, key);
}

void * directory_byIndex(Directory self, size_t index){
    return skiparray_get(self->array, index);
}

size_t directory_length(Directory self){
    return self->array->length;
}

void directory_each( Directory self, void(*func)(void*) ){
    size_t length = self->array->length;
    size_t c;
    for( c=0; c< length; c++) func(directory_byIndex(self,c));
}







