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

struct SplayNode{
    void *             key;
    void *             value;
    struct SplayNode *   right;
    struct SplayNode *   left;
    struct SplayNode *   center;
};
typedef struct SplayNode * SplayNode;

static SplayNode splaynode_new(){
    SplayNode n = malloc(sizeof(struct SplayNode));
    if (! n ){
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    n->left     = NULL;
    n->right    = NULL;
    n->center   = NULL;
    n->value    = NULL;
    n->key      = NULL;
    return n;
}

SplayTree splaytree_new(Comparator cmp){
    SplayTree st = malloc(sizeof(struct SplayTree));
    if (! st ) return NULL;
    st->cmp = cmp;
    st->root = NULL;
    return st;
}

void splaytree_splay(SplayTree tree, void * key){
    struct SplayNode store;
    SplayNode left   = &store;
    SplayNode right  = &store;
    SplayNode temp   = NULL;
    int comp;
    int hits = 0;

    if (! tree->root) return;
    while(1){

        comp = tree->cmp(key, tree->root->key);

        if (comp < 0){
            if (! tree->root->left) break;
            temp = tree->root->left;
            tree->root->left = temp->right;
            temp->right = tree->root;
            tree->root = temp;

            if (! tree->root->left) break;
            right->left = tree->root;
            right = tree->root;
            tree->root = tree->root->left;

        }else if (comp > 0){
            if (! tree->root->right) break;
            temp = tree->root->right;
            tree->root->right = temp->left;
            temp->left = tree->root;
            tree->root = temp;


            if (! tree->root->right) break;
            left->right = tree->root;
            left = tree->root;
            tree->root = tree->root->right;

        }else{
            break;
        }
    }



    left->right = tree->root->left;
    right->left = tree->root->right;
    tree->root->left = store.right;
    tree->root->right = store.left;

    return;
}


void splaytree_insert(SplayTree tree, void *key, void *value){
    SplayNode new_node = splaynode_new();
    SplayNode temp = NULL;
    int comp;

    new_node->key   = key
    new_node->value = value;

    // Empty tree so just make the new node the root
    if (! tree->root) {
        tree->root = new_node;
        return;
    }

    splaytree_splay(tree, key);

    comp = tree->cmp(key, tree->root->key);

    if (comp < 0){
        temp=tree->root;
        tree->root = new_node;
        tree->root->left = temp->left;
        temp->left = NULL;
        tree->root->right = temp;
    }else if (comp > 0){
        temp=tree->root;
        tree->root = new_node;
        tree->root->right = temp->right;
        temp->right = NULL;
        tree->root->left = temp;
    }else{
        temp = tree->root;
        new_node->left = temp->left;
        new_node->right = temp->right;
        temp->left = NULL;
        temp->right = NULL;
        tree->root = new_node;
        new_node->center = temp;
    }

    return;
}


void splaytree_remove(SplayTree tree, void *key){

    SplayNode temp = NULL;
    if (( ! tree ) || ( ! key ) || (! tree->root)) return;

    splaytree_splay(tree, key);
    if (tree->cmp(key, tree->root->key)) return;
    // found exact match

    temp = tree->root;

    if (temp->center){
        tree->root = temp->center;
        tree->root->left = temp->left;
        tree->root->right= temp->right;

    }else if (temp->left == NULL){
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
        splaytree_splay(tree, key);
        tree->root->right = temp->right;
    }

    free(temp);
}












