//
// Created by wangm on 2023/6/4.
//

#include "SBT.h"

void SBT::LeftRotate(TreeLink &x) {
    TreeLink k = x->rch;
    x->rch = k->lch;
    k->lch = x;
    k->size = x->size;
    x->size = x->lch->size + x->rch->size + 1;
    x = k;
}

void SBT::RightRotate(TreeLink &x) {
    TreeLink k = x->lch;
    x->lch = k->rch;
    k->rch = x;
    k->size = x->size;
    x->size = x->lch->size + x->rch->size + 1;
    x = k;
}

void SBT::init() {
    zero = (TreeLink)malloc(sizeof(TreeNode));
    zero->size = 0;
    zero->cnt = 0;
    zero->lch = zero;
    zero->rch = zero;
    root = zero;
}

void SBT::maintain(TreeLink &x, bool t) {
    if (!t) {
        if (x->lch->lch->size > x->rch->size)
            RightRotate(x);
        else
            if (x->lch->rch->size > x->rch->size) {
                LeftRotate(x->lch);
                RightRotate(x);
            }
            else
                return;
    }
    else {
        if (x->rch->rch->size > x->lch->size)
            LeftRotate(x);
        else
            if (x->rch->lch->size > x->rch->size) {
                RightRotate(x->rch);
                LeftRotate(x);
            }
            else
                return;
    }
    maintain(x->lch, false);
    maintain(x->rch, true);
    maintain(x, false);
    maintain(x, true);
}

TreeLink SBT::newnode(int v) {
    TreeLink p;
    p = (TreeLink)malloc(sizeof(TreeNode));
    p->lch = zero;
    p->rch = zero;
    p->cnt = 1;
    p->size = 1;
    p->value = v;
    return p;
}

