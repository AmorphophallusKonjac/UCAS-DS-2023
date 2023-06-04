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

void SBT::ins(TreeLink &x, int v) {
        insrt(x, v);
}

int SBT::del(TreeLink &x, int v) {
    TreeLink p = fnd(x, v);
    if (p == zero)
        return 1;
    delet(x, v);
    return 0;
}

TreeLink SBT::fnd(TreeLink &x, int v) {
    if (x == zero) return x;
    if (x->value == v) return x;
    if (v < x->value)
        return fnd(x->lch, v);
    else
        return fnd(x->rch, v);
}

void SBT::insrt(TreeLink &x, int v) {
    if (x == zero) {
        x = newnode(v);
        return;
    }
    x->size += 1;
    if (v <= x->value)
        insrt(x->lch, v);
    else
        insrt(x->rch, v);
    maintain(x, v > x->value);
}

int SBT::delet(TreeLink &x, int v) {
    int ret = 0;
    x->size -= 1;
    if (x->value == v || v < x->value && x->lch == zero || v > x->value && x->rch == zero) {
        ret = x->value;
        if (x->lch == zero && x->rch == zero)
            x = zero;
        else if (x->lch == zero && x->rch != zero)
            x = x->rch;
        else if (x->lch != zero && x->rch == zero)
            x = x->lch;
        else
            x->value = delet(x->lch, x->value + 1);
        return ret;
    }
    if (v < x->value)
        return delet(x->lch, v);
    else
        return delet(x->rch, v);
}

int SBT::rank(TreeLink &x, int v) {
    if (x == zero)
        return 1;
    if (v <= x->value)
        return rank(x->lch, v);
    else
        return x->lch->size + 1 + rank(x->rch, v);
}

int SBT::sel(TreeLink &x, int v) {
    if (x->lch->size + 1 == v)
        return x->value;
    if (x->lch->size + 1 < v)
        return sel(x->rch, v - x->lch->size - 1);
    else
        return sel(x->lch, v);
}

int SBT::pre(TreeLink &x, int v) {
    if (x == zero) return INT_MIN;
    if (x->value >= v)
        return pre(x->lch, v);
    else
        return std::max(x->value, pre(x->rch, v));
}

int SBT::suc(TreeLink &x, int v) {
    if (x == zero) return INT_MAX;
    if (x->value <= v)
        return suc(x->rch, v);
    else
        return std::min(x->value, suc(x->lch, v));
}
