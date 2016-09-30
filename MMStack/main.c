//
//  main.c
//  MMStack
//
//  Created by 李欣达 on 16/9/29.
//  Copyright © 2016年 李欣达. All rights reserved.
//

#include <assert.h>
#include "mmstack.h"
#include <stdio.h>

int main(void) {
    MMStack mms = create_MMStack();
    assert(mms_length(mms) == 0);
    mms_push(mms, 10);
    mms_push(mms, 5);
    mms_push(mms, 20);
    assert(mms_length(mms) == 3);
    assert(mms_max(mms) == 20);
    assert(mms_min(mms) == 5);
    assert(mms_pop(mms) == 20);
    assert(mms_length(mms) == 2);
    assert(mms_max(mms) == 10);
    destroy_MMStack(mms);
    mms = create_MMStack();
    assert(mms_length(mms) == 0);
    mms_push(mms, 4);
    mms_push(mms, 3);
    mms_push(mms, 1);
    mms_push(mms, 10);
    mms_push(mms, 0);
    assert(mms_length(mms) == 5);
    assert(mms_max(mms) == 10);
    assert(mms_min(mms) == 0);
    assert(mms_pop(mms) == 0);
    assert(mms_length(mms) == 4);
    assert(mms_max(mms) == 10);
    assert(mms_min(mms) == 1);
    assert(mms_pop(mms) == 10);
    assert(mms_max(mms) == 4);
    assert(mms_min(mms) == 1);
    assert(mms_pop(mms) == 1);
    assert(mms_max(mms) == 4);
    assert(mms_min(mms) == 3);
    assert(mms_pop(mms) == 3);
    assert(mms_max(mms) == 4);
    assert(mms_min(mms) == 4);
    assert(mms_pop(mms) == 4);
    assert(mms_length(mms) == 0);
    destroy_MMStack(mms);
    printf("All tests passed!\n");
}

