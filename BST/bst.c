//
//  bst.c
//  BST
//
//  Created by 李欣达 on 16/10/4.
//  Copyright © 2016年 李欣达. All rights reserved.
//

#include "bst.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"


// IMPORTANT: DO NOT CHANGE THESE VALUES
const int PRE_ORDER = 0;
const int IN_ORDER = 1;
const int POST_ORDER = 2;

// IMPORTANT: DO NOT CHANGE THESE DEFINITIONS
struct bstnode {
    int item;
    struct bstnode *left;
    struct bstnode *right;
    int size;
};

struct bst {
    struct bstnode *root;
};

// see details in "bst.h" file.
Bst bst_create(void) {
    Bst t=malloc(sizeof(Bst));
    t->root=NULL;
    return t;
}

// destroy_node(n) frees allocated memories of every nodes.
// effect: the memory inside t is invalid (freed)
// time: O(n).
static void destroy_node(struct bstnode *n){
    if(n==NULL)
        return;
    else{
        destroy_node(n->left);
        destroy_node(n->right);
        free(n);
    }
}


// see details in "bst.h" file.
void bst_destroy(Bst t) {
    assert(t);
    destroy_node(t->root);
    free(t);
}


// see details in "bst.h" file.
int bst_size(Bst t) {
    assert(t);
    if(t->root==NULL)
        return 0;
    else
        return t->root->size;
}


// see details in "bst.h" file.
void bst_insert(int i, Bst t) {
    struct bstnode *p=t->root;
    struct bstnode *prev=NULL;
    if(bst_find(i,t))
        return;
    struct bstnode *new=malloc(sizeof(struct bstnode));
    new->item=i;
    new->left=NULL;
    new->right=NULL;
    new->size=1;
    if(p==NULL){
        t->root=new;
        return;
    }
    while(1){
        if(p==NULL){
            if(i>prev->item)
                prev->right=new;
            else
                prev->left=new;
            break;
        }
        if(i>p->item){
            prev=p;
            p->size++;
            p=p->right;
        }
        else{
            prev=p;
            p->size++;
            p=p->left;
        }
    }
}


// see details in "bst.h" file.
bool bst_find(int i, Bst t) {
    assert(t);
    struct bstnode *p=t->root;
    while(1){
        if(p==NULL)
            return false;
        else if(i>p->item)
            p=p->right;
        else if(i<p->item)
            p=p->left;
        else
            return true;
    }
}


// see details in "bst.h" file.
int bst_select(int k, Bst t) {
    assert(t);
    struct bstnode *p=t->root;
    while(1){
        if(p->left==NULL){
            if(k==0)
                return p->item;
            else{
                k-=1;
                p=p->right;
            }
        }
        if(k==p->left->size)
            return p->item;
        else if(k<p->left->size)
            p=p->left;
        else{
            k-=p->left->size+1;
            p=p->right;
        }
    }
}


// remove_node(i,n) removes the node with item i.
// require: i is in the Bst;
// effect: mutates t to no longer contain i.
// time : O(h).
static struct bstnode *remove_node(int i,struct bstnode *n){
    if(i>n->item){
        n->size--;
        n->right=remove_node(i,n->right);
    }
    else if(i<n->item){
        n->size--;
        n->left=remove_node(i,n->left);;
    }
    else{
        if(n->left==NULL){
            struct bstnode *backup=n->right;
            free(n);
            return backup;
        }
        else if(n->right==NULL){
            struct bstnode *backup=n->left;
            free(n);
            return backup;
        }
        else{
            struct bstnode *pt=n->right;
            while(pt->left){
                pt=pt->left;
            }
            n->item=pt->item;
            n->size--;
            n->right=remove_node(pt->item,n->right);
        }
    }
    return n;
}


// see details in "bst.h" file.
void bst_remove (int i, Bst t) {
    assert(t);
    assert(bst_find(i,t));
    t->root=remove_node(i,t->root);
}


// range_node returns the number of nodes which are between start and end in n.
// time: O(n)
static int range_node(int start,int end,struct bstnode *n){
    if(n==NULL)
        return 0;
    if(n->item>end)
        return range_node(start,end,n->right);
    else if(n->item<start)
        return range_node(start,end,n->left);
    else
        return range_node(start,end,n->right)+range_node(start,end,n->left)+1;
}


// see details in "bst.h" file.
int bst_range(int start, int end, Bst t) {
    assert(t);
    return range_node(start,end,t->root);
}


// print_node(o,n) prints the bst in order o.
// effect: print output.
// time: O(n)
static void print_node(int o,struct bstnode *n,int flag){
    if(n==NULL)
        return;
    if(o==0){
        if(flag)
            printf("%d",n->item);
        else
            printf(",%d",n->item);
        print_node(o,n->left,0);
        print_node(o,n->right,0);
    }
    else if(o==1){
        print_node(o,n->left,flag);
        if(flag==n->item)
            printf("%d",n->item);
        else
            printf(",%d",n->item);
        print_node(o,n->right,flag);
    }
    else if(o==2){
        print_node(o,n->left,flag);
        print_node(o,n->right,flag);
        if(flag==n->item)
            printf("%d",n->item);
        else
            printf(",%d",n->item);
    }
    else
        assert(0);
}

// see details in "bst.h" file.
void bst_print (int o, Bst t) {
    assert(t);
    struct bstnode *p=t->root;
    if(p==NULL){
        printf("[]\n");
        return;
    }
    while(p->left){
        p=p->left;
    }
    printf("[");
    print_node(o,t->root,p->item);
    printf("]\n");
}


// to_array(n,arr,flag,size) mutates the dynamically
// allocated array arr into a sorted array.
// effect: mutate arr.
// time: O(n).
static void to_array(struct bstnode *n,int *arr,int index,int flag){
    if(n==NULL)
        return;
    else{
        if(flag==0){
            if(n->right==NULL)
                arr[index]=n->item;
            else{
                index-=n->right->size;
                arr[index]=n->item;
            }
        }
        else{
            if(n->left==NULL)
                arr[index]=n->item;
            else{
                index+=n->left->size;
                arr[index]=n->item;
            }
        }
        to_array(n->left,arr,index-1,0);
        to_array(n->right,arr,index+1,1);
    }
}


// see details in "bst.h" file.
int *bst_to_sorted_array(Bst t) {
    if(t->root==NULL)
        return NULL;
    int *arr=malloc(sizeof(int)*t->root->size);
    to_array(t->root,arr,0,1);
    return arr;
}


// to_bst(arr,n,start,end) returns a pointer to a dynamically allocated
//   node which links all of the items from arr such that the returned bst
//   is balanced.
// effect: allocates memory (caller must free).
// Time: O(n). [O(1)+ 2*T(n/2)].
static struct bstnode *to_bst(int *arr,struct bstnode *n,int start,int end){
    if(start==end){
        n->item=arr[start];
        n->left=n->right=NULL;
        return n;
    }
    else if(start>end){
        free(n);
        return NULL;
    }
    struct bstnode *new1=malloc(sizeof(struct bstnode));
    struct bstnode *new2=malloc(sizeof(struct bstnode));
    int mid=(start+end)/2;
    n->item=arr[mid];
    n->size=end-start+1;
    n->left=to_bst(arr,new1,start,mid-1);
    n->right=to_bst(arr,new2,mid+1,end);
    return n;
}


// see details in "bst.h" file.  
// Time : O(n).
Bst sorted_array_to_bst(int *arr, int len){
    Bst bst0=malloc(sizeof(struct bst));
    struct bstnode *new=malloc(sizeof(struct bstnode));
    bst0->root=to_bst(arr,new,0,len-1);
    return bst0;
}


