//
// Created by hp on 2023/6/8.
//

#include "Treap.h"


void TREAP::push_up(TreeLink x) {
    if(x!=nullptr)
        x->size = (x->lch ? x->lch->size : 0)
                  + (x->rch ? x->rch->size : 0) + x->cnt;
}

void TREAP::left_rotate(TreeLink &x) {
    TreeLink rc = x->rch;
    x->rch = rc->lch;
    rc->lch = x;
    push_up(x);
    x = rc;
    push_up(x);
}

void TREAP::right_rotate(TreeLink &x) {
    TreeLink lc = x->lch;
    x->lch = lc->rch;
    lc->rch = x;
    push_up(x);
    x = lc;
    push_up(x);
}

TreeLink TREAP::insert(TreeLink &p, int x) {
    if(p == nullptr) {
        p = (TreeLink)malloc(sizeof(TreeNode));
        p->size = p->cnt = 1;
        p->value = x; p->key = rand();
        p->lch = p->rch = nullptr;
        return p;
    }
    TreeLink rtn;
    if(p->value == x){
        ++p->cnt;
        return p;
    }
    else if(x < p->value){
        rtn = insert(p->lch, x);
        if(p->lch->key < p->key) right_rotate(p);
    }
    else{
        rtn = insert(p->rch, x);
        if(p->rch->key < p->key) left_rotate(p);
    }
    push_up(p);
    return rtn;
}

int TREAP::del(TreeLink &p, int x) {
    if(p == nullptr) return 0;
    if(p->value == x) {
        if(p->cnt > 1){
            --p->cnt;
            push_up(p);
            return 1;
        } else if(!p->lch && !p->rch){
            p = nullptr; return 2;
        } else if(!p->lch){
            p = p->rch; return 2;
        } else if(!p->rch) {
            p = p->lch; return 2;
        } else if(p->lch->key < p->rch->key){
            right_rotate(p);
            int r = del(p,x);
            push_up(p);
            return r;
        } else {
            left_rotate(p);
            int r = del(p,x);
            push_up(p);
            return r;
        }
    }
    else if(x < p->value) {
        int r = del(p->lch, x);
        push_up(p);
        return r;
    }
    else {
        int r = del(p->rch, x);
        push_up(p);
        return r;
    }
}

TreeLink TREAP::find_pre(TreeLink p, int x) {
    if(p == nullptr) return p;
    if(p->value < x) {
        TreeLink find_rch = find_pre(p->rch, x);
        return find_rch ? find_rch : p;
    }
    else return find_pre(p->lch, x);
}

TreeLink TREAP::find_suf(TreeLink p, int x) {
    if(p == nullptr) return nullptr;
    if(p->value > x) {
        TreeLink find_lch = find_suf(p->lch, x);
        return find_lch ? find_lch : p;
    }
    else return find_suf(p->rch, x);
}

TreeLink TREAP::find_kth(TreeLink p, int k) {
    if (p == nullptr) { return nullptr; }
    int lsize = p->lch ? p->lch->size : 0;
    if (k <= lsize)
        return find_kth(p->lch, k);
    else if (k > lsize + p->cnt)
        return find_kth(p->rch, k - lsize - p->cnt);
    else return p;
}

TreeLink TREAP::find_rank(TreeLink p, int x) {
    if(p == nullptr){
        return nullptr;
    }
    if(p->value == x){
        return p;
    }
    else if(x < p->value)
        return find_rank(p->lch, x);
    else {
        TreeLink rtn = find_rank(p->rch, x);
        return rtn;
    }
}

void TREAP::SPLIT(TreeLink p, TreeLink &T1, TreeLink &T2, int x){
    if(p == nullptr) return;
    if(p->lch) SPLIT(p->lch, T1, T2, x);
    while(p->cnt){
        if(p->value <= x)
            insert(T1, p->value);
        else
            insert(T2, p->value);
        --p->cnt;
    }
    if(p->rch) SPLIT(p->rch, T1, T2, x);
}

void TREAP::split(int x) {
    TreeLink Tree1 = nullptr, Tree2 = nullptr;
    SPLIT(Root, Tree1, Tree2, x);
    if(Root == nullptr)
        Root = (TreeLink)malloc(sizeof(TreeNode));
    Root->cnt = Root->value = 0;
    Root->lch = Tree1;
    Root->rch = Tree2;
    push_up(Root);
    isSplit = 1;
}

void TREAP::MERGE(TreeLink a) {
    if(a == nullptr) return;
    if(a->lch) MERGE(a->lch);
    while(a->cnt){
        insert(Root, a->value);
        --a->cnt;
    }
    if(a->rch) MERGE(a->rch);
}

void TREAP::merge(){
    TreeLink Root2;
    int lsize = Root->lch ? Root->lch->size : 0;
    int rsize = Root->rch ? Root->rch->size : 0;
    if(lsize > rsize) {
        Root2 = Root->rch;
        Root = Root->lch;
    }
    else{
        Root2 = Root->lch;
        Root = Root->rch;
    }
    MERGE(Root2);
    isSplit = 0;
}

void TREAP::rel(TreeLink &p) {
    if (p == nullptr) return;
    if(p->lch) rel(p->lch);
    if(p->rch) rel(p->rch);
    free(p);
    p= nullptr;
}

TREAP::TREAP() {
    Root = nullptr;
    isSplit = 0;
}

TREAP::~TREAP() {
    rel(Root);
    Root = nullptr;
}
