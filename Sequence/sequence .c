//
//  sequence .c
//  Sequence ADT
//
//  Created by 李欣达 on 16/9/29.
//  Copyright © 2016年 李欣达. All rights reserved.
//

#include "sequence .h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


struct Node{
    int item;
    struct Node *next;
};

struct Sequence{
    struct Node *front;
    int len;
};

// see details in "sequence.h" file.
struct Sequence *Sequence_create(void){
    struct Sequence *s=malloc(sizeof(struct Sequence));
    s->front=NULL;
    s->len=0;
    return s;
}

// see details in "sequence.h" file.
void Sequence_print(const struct Sequence *seq){
    if(seq->len==0)
        printf("[empty]\n");
    else{
        struct Node *p=seq->front;
        printf("[%d]",seq->len);
        for(int i=0;i<seq->len;++i){
            printf(" %d",p->item);
            p=p->next;
        }
        printf("\n");
    }
}



// see details in "sequence.h" file.
int Sequence_length(const struct Sequence *seq){
    return seq->len;
}


// see details in "sequence.h" file.
int Sequence_item_at(const struct Sequence *seq, int pos){
    assert(pos>=0&&pos<seq->len);
    struct Node *p=seq->front;
    for(int i=0;i<pos;++i){
        p=p->next;
    }
    return p->item;
}


// see details in "sequence.h" file.
void Sequence_destroy(struct Sequence *seq){
    struct Node *p=seq->front;
    for(int i=0;i<seq->len;++i){
        struct Node *backup=p->next;
        free(p);
        p=backup;
    }
    free(seq);
}



// see details in "sequence.h" file.
void Sequence_insert_at(struct Sequence *seq, int pos, int val){
    assert(pos>=0&&pos<=seq->len);
    struct Node *p=seq->front;
    struct Node *new=malloc(sizeof(struct Node));
    new->item=val;
    if(pos==0){
        new->next=p;
        seq->front=new;
    }
    else{
        for(int i=0;i<pos-1;++i){
            p=p->next;
        }
        new->next=p->next;
        p->next=new;
    }
    seq->len++;
}


// see details in "sequence.h" file.
int Sequence_remove_at(struct Sequence *seq,int pos){
    assert(pos>=0&&pos<seq->len);
    struct Node *p=seq->front;
    int val;
    if(pos==0){
        val=p->item;
        seq->front=p->next;
        free(p);
    }
    else{
        for(int i=0;i<pos-1;++i){
            p=p->next;
        }
        struct Node *backup=p->next;
        val=backup->item;
        p->next=backup->next;
        free(backup);
    }
    seq->len--;
    return val;
}


