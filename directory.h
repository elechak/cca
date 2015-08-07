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

#ifndef _DIRECTORY_
#define _DIRECTORY_

#include <stdlib.h>
#include "comparison.h"
#include "splaytree.h"
#include "skiparray.h"
#include "directory.h"


struct Directory{
    SkipArray array;
    SplayTree tree;
};

typedef struct Directory * Directory;

Directory directory_new(Comparator c);
void directory_free(Directory self);
void directory_add(Directory self , void * data);
void * directory_deleteIndex(Directory self, size_t index);
void * directory_deleteKey(Directory self , void * key);
void * directory_byKey(Directory self, void * key);
void * directory_byIndex(Directory self, size_t index);
size_t directory_length(Directory self);
void directory_each( Directory self, void(*func)(void*) );
#endif

