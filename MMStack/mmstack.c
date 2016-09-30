//
//  mmstack.c
//  MMStack
//
//  Created by 李欣达 on 16/9/29.
//  Copyright © 2016年 李欣达. All rights reserved.
//

// a MMStack (Min/Max Stack)
// is a Stack ADT for storing integers
// that can return the Min/Max items in the stack
// all operations (except, perhaps, destroy) are O(1)

#include <stdlib.h>
#include <assert.h>
#include "mmstack.h"

struct Node{
    int item;
    int part_min;
    int part_max;
    struct Node *next;
};

struct mmstack {
    struct Node *front;
    int len;
};

// see details in "mmstack.h" file.
MMStack create_MMStack(void){
    MMStack mms=malloc(sizeof(struct mmstack));
    mms->front=NULL;
    mms->len=0;
    return mms;
}

// see details in "mmstack.h" file.
void destroy_MMStack(MMStack mms){
    struct Node *p=mms->front;
    while(p!=NULL){
        struct Node *backup=p->next;
        free(p);
        p=backup;
    }
    free(mms);
}

// see details in "mmstack.h" file.
int mms_length(MMStack mms){
    return mms->len;
}

// see details in "mmstack.h" file.
void mms_push(MMStack mms, int i){
    struct Node *new=malloc(sizeof(struct Node));
    new->next=mms->front;
    mms->front=new;
    new->item=i;
    if(mms->len==0){
        new->part_min=new->part_max=i;
        mms->len++;
        return;
    }
    if(i<new->next->part_min)
        new->part_min=i;
    else
        new->part_min=new->next->part_min;
    if(i>new->next->part_max)
        new->part_max=i;
    else
        new->part_max=new->next->part_max;
    mms->len++;
}

// see details in "mmstack.h" file.
int mms_pop(MMStack mms) {
    struct Node *backup=mms->front;
    int value=backup->item;
    mms->front=mms->front->next;
    free(backup);
    mms->len--;
    return value;
}

// see details in "mmstack.h" file.
int mms_min(MMStack mms) {
    return mms->front->part_min;
}

// see details in "mmstack.h" file.
int mms_max(MMStack mms) {
    return mms->front->part_max;
}


