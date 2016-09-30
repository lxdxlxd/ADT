//
//  pq.c
//  Priority Queue
//
//  Created by 李欣达 on 16/9/29.
//  Copyright © 2016年 李欣达. All rights reserved.
//

#include "pq.h"
#include <stdlib.h>
#include <stdio.h>

struct Node{
    int item;
    int pri;
    struct Node *next;
};

struct pq{
    struct Node *front;
    struct Node *back;
    int len;
};


// see details in "pq.h" file.
struct pq *pq_create(void){
    struct pq *pqueue=malloc(sizeof(struct pq));
    pqueue->front=NULL;
    pqueue->back=NULL;
    pqueue->len=0;
    return pqueue;
}

// see details in "pq.h" file.
void pq_destroy(struct pq *pqueue){
    struct Node *p=pqueue->front;
    while(p!=NULL){
        struct Node *backup=p;
        p=backup->next;
        free(backup);
    }
    free(pqueue);
}


// see details in "pq.h" file.
void pq_add(struct pq *pqueue,int item, int priority){
    struct Node *p=pqueue->front;
    struct Node *new=malloc(sizeof(struct pq));
    new->item=item;
    new->pri=priority;
    if(p==NULL||p->pri>priority){
        new->next=p;
        pqueue->front=new;
        pqueue->len++;
        if(p==NULL)
            pqueue->back=new;
        return;
    }
    if(priority>=pqueue->back->pri){
        pqueue->back->next=new;
        new->next=NULL;
        pqueue->back=new;
        pqueue->len++;
        return;
    }
    while(p->next!=NULL&&p->next->pri<=priority){
        p=p->next;
    }
    new->next=p->next;
    p->next=new;
    pqueue->len++;
}

// see details in "pq.h" file.
int pq_remove(struct pq *pqueue){
    struct Node *backup=pqueue->front;
    int temp=backup->item;
    pqueue->front=pqueue->front->next;
    free(backup);
    pqueue->len--;
    return temp;
}

// see details in "pq.h" file.
bool pq_is_empty(const struct pq *pqueue){
    return(pqueue->len==0);
}

// see details in "pq.h" file.
void pq_print(const struct pq *pqueue){
    if(pqueue->len==0)
        return;
    int temp_pri=pqueue->front->pri;
    struct Node *p=pqueue->front;
    printf("[%d]",temp_pri);
    while(p!=NULL){
        if(p->pri!=temp_pri){
            temp_pri=p->pri;
            printf("\n");
            printf("[%d]",temp_pri);
            continue;
        }
        printf(" %d",p->item);
        p=p->next;
    }
    printf("\n");
}

// see details in "pq.h" file.
int pq_length(const struct pq *pqueue){
    return pqueue->len;
}

// see details in "pq.h" file.
int pq_front_priority(const struct pq *pqueue){
    return pqueue->front->pri;
}

// see details in "pq.h" file.
int pq_front_item(const struct pq *pqueue){
    return pqueue->front->item;
}









