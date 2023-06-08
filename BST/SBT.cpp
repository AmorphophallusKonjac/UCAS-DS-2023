//
// Created by wangm on 2023/6/4.
//

#include <cstring>
#include "SBT.h"

SBT::SBT() {
    root = nullptr;
    isSplit = false;
}

SBT::~SBT() {
    rel(root);
}

void SBT::LeftRotate(TreeLink &x) {
    TreeLink k = x->rch;
    x->rch = k->lch;
    k->lch = x;
    k->size = x->size;
    x->size = ((x->lch != nullptr) ? x->lch->size : 0) + ((x->rch != nullptr) ? x->rch->size : 0) + 1;
    x = k;
}

void SBT::RightRotate(TreeLink &x) {
    TreeLink k = x->lch;
    x->lch = k->rch;
    k->rch = x;
    k->size = x->size;
    x->size = ((x->lch != nullptr) ? x->lch->size : 0) + ((x->rch != nullptr) ? x->rch->size : 0) + 1;
    x = k;
}

void SBT::maintain(TreeLink &x, bool t) {
    if (x == nullptr) return;
    int llsize, lrsize, rlsize, rrsize, lsize, rsize;
    lsize = (x->lch != nullptr) ? x->lch->size : 0;
    rsize = (x->rch != nullptr) ? x->rch->size : 0;
    if (lsize) {
        llsize = (x->lch->lch != nullptr) ? x->lch->lch->size : 0;
        lrsize = (x->lch->rch != nullptr) ? x->lch->rch->size : 0;
    }
    else {
        llsize = 0;
        lrsize = 0;
    }
    if (rsize) {
        rlsize = (x->rch->lch != nullptr) ? x->rch->lch->size : 0;
        rrsize = (x->rch->rch != nullptr) ? x->rch->rch->size : 0;
    }
    else {
        rlsize = 0;
        rrsize = 0;
    }
    if (!t) {
        //if (x->lch->lch->size > x->rch->size)
        if (llsize > rsize)
            RightRotate(x);
        else
            //if (x->lch->rch->size > x->rch->size) {
            if (lrsize > rsize) {
                LeftRotate(x->lch);
                RightRotate(x);
            }
            else
                return;
    }
    else {
        //if (x->rch->rch->size > x->lch->size)
        if (rrsize > lsize)
            LeftRotate(x);
        else
            //if (x->rch->lch->size > x->rch->size) {
            if (rlsize > rsize) {
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
    auto p = (TreeLink)malloc(sizeof(TreeNode));
    p->lch = nullptr;
    p->rch = nullptr;
    p->cnt = 1;
    p->size = 1;
    p->value = v;
    return p;
}

TreeLink SBT::ins(TreeLink &x, int v) {
    TreeLink p = fnd(root, v);
    if (p == nullptr)
        p = insrt(x, v);
    else
        p->cnt += 1;
    return p;
}

// 0 fail
// 1 success and left
// 2 success and no left
int SBT::del(TreeLink &x, int v) {
    int rlt;
    TreeLink p = fnd(x, v);
    if (p == nullptr)
        return 0;
    if (p->cnt > 1) {
        rlt = 1;
        p->cnt -= 1;
    }
    else {
        rlt = 2;
        delet(x, v);
    }
    return rlt;
}

TreeLink SBT::fnd(TreeLink &x, int v) {
    if (x == nullptr) return x;
    if (x->value == v) return x;
    if (v < x->value)
        return fnd(x->lch, v);
    else
        return fnd(x->rch, v);
}

TreeLink SBT::insrt(TreeLink &x, int v) {
    TreeLink p;
    if (x == nullptr) {
        x = newnode(v);
        return x;
    }
    x->size += 1;
    if (v <= x->value)
        p = insrt(x->lch, v);
    else
        p = insrt(x->rch, v);
    maintain(x, v > x->value);
    return p;
}

retdata SBT::delet(TreeLink &x, int v) {
    retdata ret = {0, 0};
    retdata y;
    x->size -= 1;
    if (x->value == v || v < x->value && x->lch == nullptr || v > x->value && x->rch == nullptr) {
        ret = (retdata){x->cnt, x->value};
        if (x->lch == nullptr && x->rch == nullptr) {
            free(x);
            x = nullptr;
        }
        else if (x->lch == nullptr && x->rch != nullptr) {
            TreeLink p = x->rch;
            free(x);
            x = p;
        }
        else if (x->lch != nullptr && x->rch == nullptr) {
            TreeLink p = x->lch;
            free(x);
            x = p;
        }
        else {
            y = delet(x->lch, x->value + 1);
            x->value = y.value;
            x->cnt = y.cnt;
        }
        return ret;
    }
    if (v < x->value)
        return delet(x->lch, v);
    else
        return delet(x->rch, v);
}

int SBT::rank(TreeLink &x, int v) {
    if (x == nullptr)
        return 1;
    if (v <= x->value)
        return rank(x->lch, v);
    else
        return ((x->lch != nullptr) ? x->lch->size : 0) + 1 + rank(x->rch, v);
}

int SBT::sel(TreeLink &x, int v) {
    if (((x->lch != nullptr) ? x->lch->size : 0) + 1 == v)
        return x->value;
    if (((x->lch != nullptr) ? x->lch->size : 0) + 1 < v)
        return sel(x->rch, v - ((x->lch != nullptr) ? x->lch->size : 0) - 1);
    else
        return sel(x->lch, v);
}

int SBT::pre(TreeLink &x, int v) {
    if (x == nullptr) return INT_MIN;
    if (x->value >= v)
        return pre(x->lch, v);
    else
        return std::max(x->value, pre(x->rch, v));
}

int SBT::suc(TreeLink &x, int v) {
    if (x == nullptr) return INT_MAX;
    if (x->value <= v)
        return suc(x->rch, v);
    else
        return std::min(x->value, suc(x->lch, v));
}

void SBT::rel(TreeLink &x) {
    if (x == nullptr)
        return;
    rel(x->lch);
    rel(x->rch);
    free(x);
}

void SBT::split(int v) {
    isSplit = true;
    auto p = newnode(0);
    Split_Tree(root, p->lch, p->rch, v);
    root = p;
}

void SBT::Split_Tree(TreeLink x, TreeLink &y, TreeLink &z, int v) {
    if (x == nullptr)
        return;
    if (x->value <= v) {
        y = x;
        y->rch = nullptr;
        Split_Tree(x->rch, y->rch, z, v);
    }
    else {
        z = x;
        z->lch = nullptr;
        Split_Tree(x->lch, y, z->lch, v);
    }
}

void SBT::merge(int v) {
    isSplit = false;
    TreeLink p = nullptr;
    retdata a[100], b[100], c[200];
    int alen = 0, blen = 0, clen = 0;
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    Tree2List(root->lch, a, alen);
    Tree2List(root->rch, b, blen);
    for (int i = 0, j = 0; i < alen || j < blen; ) {
        if (i == alen) {
            c[clen++] = b[j++];
            continue;
        }
        if (j == blen) {
            c[clen++] = a[i++];
            continue;
        }
        if (a[i].value == b[j].value) {
            c[clen++] = {a[i].cnt + b[j].cnt, a[i].value};
            ++i; ++j;
            continue;
        }
        if (a[i].value < b[j].value) {
            c[clen++] = a[i++];
            continue;
        }
        if (a[i].value > b[j].value) {
            c[clen++] = b[j++];
            continue;
        }
    }
    root = List2Tree(c, 0, clen);
}

void SBT::Tree2List(TreeLink x, retdata *a, int &i) {
    if (x == nullptr)
        return;
    Tree2List(x->lch, a, i);
    a[i++] = {x->cnt, x->value};
    Tree2List(x->rch, a, i);
    free(x);
}

TreeLink SBT::List2Tree(retdata *a, int l, int r) {
    int mid = (l + r) / 2;
    if (l >= r)
        return nullptr;
    auto p = newnode(a[mid].value);
    p->cnt = a[mid].cnt;
    p->lch = List2Tree(a, l, mid);
    p->rch = List2Tree(a, mid + 1, r);
    p->size = ((p->lch != nullptr) ? p->lch->size : 0) + 1 + ((p->rch != nullptr) ? p->rch->size : 0);
    return p;
}