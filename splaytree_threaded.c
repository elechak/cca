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
#include "splaytree.h"
#include <stdio.h>

static SplayNode splaynode_new(void *data){
    SplayNode n = malloc(sizeof(struct SplayNode));
    if (! n ){
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    n->left     = NULL;
    n->right    = NULL;
    n->data     = data;
    return n;
}


SplayTree splaytree_new(Comparator cmp){
    SplayTree st = malloc(sizeof(struct SplayTree));
    if (! st ) return NULL;
    st->size = 0;
    st->cmp = cmp;
    st->root = NULL;
    st->destroyer=NULL;
    #ifdef REENTRANT
        st->mutex = mutex_new();
    #endif
    return st;
}


void splaytree_setDestroyer(SplayTree tree , Destroyer d){
    tree->destroyer = d;
}


static int splaytree_splay(SplayTree tree, void * key){
    struct SplayNode store;
    int comp;

    if (! tree->root) return 1;

    if ( (comp = tree->cmp(key, tree->root->data)) == 0 ) return 0;

    store.left = NULL;
    store.right = NULL;
    SplayNode left   = &store;
    SplayNode right  = &store;
    SplayNode temp   = NULL;

    do{

        if (comp < 0){
            if (! tree->root->left) break;

            // Right rotate
            if ( (comp = tree->cmp(key, tree->root->left->data)) < 0 ){
                temp = tree->root->left;
                tree->root->left = temp->right;
                temp->right = tree->root;
                tree->root = temp;
                if (! tree->root->left) break;
            }

            right->left = tree->root;
            right = tree->root;
            tree->root = tree->root->left;

        }else if (comp > 0){
            if (! tree->root->right) break;

            // Left rotate
            if ( (comp = tree->cmp(key, tree->root->right->data)) > 0 ){
                temp = tree->root->right;
                tree->root->right = temp->left;
                temp->left = tree->root;
                tree->root = temp;
                if (! tree->root->right) break;
            }

            left->right = tree->root;
            left = tree->root;
            tree->root = tree->root->right;
        }

    }while( (comp = tree->cmp(key, tree->root->data)) );

    left->right = tree->root->left;
    right->left = tree->root->right;
    tree->root->left = store.right;
    tree->root->right = store.left;
    return comp;
}


/* Get the splaytree node that corresponds to the key */
void * splaytree_get(SplayTree tree, void * key){
    void * ret = NULL;

    #ifdef REENTRANT
        mutex_lock(tree->mutex);
    #endif

    int c = splaytree_splay(tree, key);
    if (c==0) ret = tree->root->data;

    #ifdef REENTRANT
        mutex_unlock(tree->mutex);
    #endif

    return ret;
}


void * splaytree_insert(SplayTree tree, void *data){
    SplayNode temp = NULL;
    void * tempvalue = NULL;
    int comp;

    #ifdef REENTRANT
        mutex_lock(tree->mutex);
    #endif

    // Empty tree so just make the new node the root
    if (! tree->root) {
        tree->root = splaynode_new(data);
        tree->size++;
        #ifdef REENTRANT
            mutex_unlock(tree->mutex);
        #endif
        return NULL;
    }

    comp = splaytree_splay(tree, data);

    if (comp < 0){
        temp=tree->root;
        tree->root = splaynode_new(data);
        tree->root->left = temp->left;
        temp->left = NULL;
        tree->root->right = temp;
        tree->size++;
    }else if (comp > 0){
        temp=tree->root;
        tree->root = splaynode_new(data);
        tree->root->right = temp->right;
        temp->right = NULL;
        tree->root->left = temp;
        tree->size++;
    }else{
        tempvalue = tree->root->data;
        tree->root->data = data;
        return tempvalue;
    }

    #ifdef REENTRANT
        mutex_unlock(tree->mutex);
    #endif

    return NULL;
}

void * splaytree_delete(SplayTree tree, void *data){
    SplayNode temp = NULL;
    void * value = NULL;
    
    #ifdef REENTRANT
        mutex_lock(tree->mutex);
    #endif
    
    if ( ( ! tree ) || (! tree->root) ){
        // empty tree
        #ifdef REENTRANT
            mutex_unlock(tree->mutex);
        #endif
        return NULL;
    }

    if ( ! data ) data = tree->root->data;
    
    if ( splaytree_splay(tree, data) ){
        // no exact match found
        #ifdef REENTRANT
            mutex_unlock(tree->mutex);
        #endif
        return NULL;
    } 

    // found exact match
    temp = tree->root;
    value = tree->root->data;

    if (temp->left == NULL){
        if (temp->right){
            tree->root = temp->right;
        }else{
            tree->root = NULL;
        }
    }else if (temp->right == NULL){
        if (temp->left){
            tree->root = temp->left;
        }else{
            tree->root = NULL;
        }
    }else{
        tree->root = temp->left;
        splaytree_splay(tree, data);
        tree->root->right = temp->right;
    }
    tree->size--;

    free(temp);
    
    #ifdef REENTRANT
        mutex_unlock(tree->mutex);
    #endif
    return value;
}


void splaytree_clear(SplayTree tree){
    void * data = NULL;

    if (tree->destroyer){
        while( tree->size){
            data = splaytree_delete(tree, NULL); 
            if (data) tree->destroyer(data);
        }

    }else{

        while( tree->size){
            splaytree_delete(tree, tree->root->data);
        }

    }
}


void splaytree_totalFree(SplayTree tree){
    
    void * data = NULL;
    while( tree->size){
        data = splaytree_delete(tree, NULL);
        if (data) free(data);
    }
    
    #ifdef REENTRANT
        mutex_free(tree->mutex);
    #endif
    free(tree);
}


void splaytree_free(SplayTree tree){

    void * data = NULL;

    if (tree->destroyer){
        while( tree->size){
            data = splaytree_delete(tree, NULL);
            if (data) tree->destroyer(data);
        }

    }else{

        while( tree->size){
            splaytree_delete(tree, NULL);
        }

    }
    #ifdef REENTRANT
        mutex_free(tree->mutex);
    #endif
    free(tree);
}


static void _each( SplayTree tree, SplayNode n, void(*func)(void*) ){
    if (! n) n = tree->root;

    if( n ){
        func(n->data);
        if (n->left)  _each( tree, n->left , func );
        if (n->right) _each( tree, n->right , func );
    }
}


void splaytree_each( SplayTree tree, void(*func)(void*) ){
    #ifdef REENTRANT
        mutex_lock(tree->mutex);
    #endif
    _each(tree, NULL, func);
    #ifdef REENTRANT
        mutex_unlock(tree->mutex);
    #endif
}







