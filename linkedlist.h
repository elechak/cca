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
#ifndef _LINKEDLISTS_
#define _LINKEDLISTS_

#include <stdlib.h>

/* Define the singly linked list node and container */
#define sllist_define(ID, TYPE)\
struct TYPE##_sllist_node{\
    TYPE value;\
    TYPE##_llist_node * next;\
};\
typedef struct TYPE##_sllist_struct{\
    size_t length;\
    TYPE##_sllist_node *  root;\
    TYPE##_sllist_node *  last;\
    TYPE##_sllist_node *  prev;\
    TYPE##_sllist_node *  current;\
    TYPE##_sllist_node *  temp;\
} * ID;


/* Create a new singly linked list */
#define sllist_init(VAR, ID)\
ID VAR        = malloc( sizeof(*VAR));\
VAR->root     = NULL;\
VAR->last     = NULL;\
VAR->prev     = NULL;\
VAR->current  = NULL;\
VAR->temp     = NULL;\
VAR->length   = 0;


#define sllist_pushfront(SLLIST , VAL)\
    SLLIST->temp = malloc(sizeof( *(SLLIST->temp) ) );\
    SLLIST->temp->value = VAL;\
    SLLIST->temp->next = SLLIST->root;\
    SLLIST->root = SLLIST->temp;\


#define sllist_getnext(SLLIST)
    SLLIST->curent ? SLLIST->current->next : SLLIST


#define sllist_delete(SLLIST)\


                if (string_backpatch_last){
                    string_backpatch_last->next = string_backpatch_temp->next;
                    free(string_backpatch_temp);
                    string_backpatch_temp = string_backpatch_last->next;

                }else{
                    string_backpatch = string_backpatch_temp->next;
                    free(string_backpatch_temp);
                    if (string_backpatch){
                        string_backpatch_temp = string_backpatch->next;
                    }else{
                        break;
                    }
                }





llist_define(int_linked_list, int);
llist_init(int_linked_list, ll_x);












