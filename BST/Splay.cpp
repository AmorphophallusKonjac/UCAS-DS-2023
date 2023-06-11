//
// Created by hp on 2023/6/7.
//

#include "Splay.h"

void Splay_Tree::insert(TreeLink &p, int x, int Root_w) {
    TreeLink tempRoot = Root;
    if(isSplit){
        Root = p;
        if(Root) Root->father = nullptr;
    }
    if(Root == nullptr){
        Root = (TreeLink)malloc(sizeof(TreeNode));
        Root->lch = Root->rch = Root->father = nullptr;
        Root->value = x;
        Root->cnt = 1;
    }
    else {
        TreeLink now = Root, fa = nullptr;
        while (1) {
            if (x == now->value) {
                now->cnt++;
                Splay(now);
                break;
            }
            fa = now;
            now = (x > now->value) ? now->rch : now->lch;
            if (now == nullptr) {
                now = (TreeLink) malloc(sizeof(TreeNode));
                now->value = x;
                now->cnt = 1;
                now->father = fa;
                now->lch = now->rch = nullptr;
                if (x > fa->value) fa->rch = now;
                else fa->lch = now;
                Splay(now);
                break;
            }
        }
    }
    if(isSplit){
        if(Root_w) tempRoot->rch = Root;
        else tempRoot->lch = Root;
        if(Root) Root->father = tempRoot;
        Root = tempRoot;
    }
}

int Splay_Tree::del(TreeLink &p, int x, int Root_w) {
    int rtn;
    if(!find_rank(p, x, Root_w)) return 0;
    TreeLink tempRoot = Root;
    if(isSplit){
        Root = p;
        if(Root) Root->father = nullptr;
    }
    if(Root->cnt > 1) {
        Root->cnt--;
        push_up(Root);
        rtn = 1;
    }
    else if(Root->lch == nullptr && Root->rch == nullptr){
        Root = nullptr;
        rtn = 2;
    }
    else if(Root->rch == nullptr){
        Root = Root->lch;
        Root->father = nullptr;
        rtn = 2;
    }
    else if(Root->lch == nullptr){
        Root = Root->rch;
        Root->father = nullptr;
        rtn = 2;
    }
    else {
        TreeLink left = find_pre(p);
        Splay(left);
        Root->rch = Root->rch->rch;
        Root->rch->father = p;
        push_up(p);
        rtn = 2;
    }
    if(isSplit){
        if(Root_w) tempRoot->rch = Root;
        else tempRoot->lch = Root;
        if(Root) Root->father = tempRoot;
        Root = tempRoot;
    }
    return rtn;
}

TreeLink Splay_Tree::find_pre(TreeLink p) {
    TreeLink now = p->lch;
    while(now->rch != nullptr) now = now->rch;
    return now;
}

TreeLink Splay_Tree::find_suf(TreeLink p) {
    TreeLink now = p->rch;
    while(now->lch != nullptr) now = now->lch;
    return now;
}

TreeLink Splay_Tree::find_kth(TreeLink p, int k) {
    TreeLink now = p;
    while(1) {
        if (now->lch != nullptr && k <= now->lch->size) now = now->lch;
        else {
            int lsize = ((now->lch) ? now->lch->size : 0) + now->cnt;
            if (k <= lsize) return now;
            k -= lsize;
            now = now->rch;
        }
    }
}

int Splay_Tree::find_rank(TreeLink p, int x,int Root_w) {
    TreeLink tempRoot = Root;
    if(isSplit){
        Root = p;
        if(Root) Root->father = nullptr;
    }
    int rtn;
    if(p == nullptr) rtn = 0;
    else {
        TreeLink now = p;
        int ans = 1;
        while (1) {
            if (now->lch != nullptr && x < now->value) now = now->lch;
            else {
                ans += (now->lch) ? now->lch->size : 0;
                if (x == now->value) {
                    Splay(now);
                    rtn = ans;
                    break;
                }
                ans += now->cnt;
                now = now->rch;
            }
            if (now == nullptr){
                rtn = 0;
                break;
            }
        }
    }
    if(isSplit){
        if(Root_w) tempRoot->rch = Root;
        else tempRoot->lch = Root;
        if(Root) Root->father = tempRoot;
        Root = tempRoot;
    }
    return rtn;
}

void Splay_Tree::push_up(TreeLink x) {
    if(x!=nullptr)
        x->size = (x->lch ? x->lch->size : 0)
                + (x->rch ? x->rch->size : 0) + x->cnt;
}

void Splay_Tree::rotate(TreeLink x) {
    TreeLink y = x->father, z = y->father;
    int w = get_w(x), w1 = get_w(y);
    if(w==0) {  //左子树右旋
        y->lch = x->rch; if(y->lch) y->lch->father = y;
        x->rch = y; y->father = x;
        x->father = z;
        if(z != nullptr){
            if(w1 == 0) z->lch = x;
            else z->rch = x;
        }
    }
    else {      //右子树左旋
        y->rch = x->lch; if(y->rch) y->rch->father = y;
        x->lch = y; y->father = x;
        x->father = z;
        if (z != nullptr) {
            if (w1 == 0) z->lch = x;
            else z->rch = x;
        }
    }
    push_up(y);
    push_up(x);
}

void Splay_Tree::Splay(TreeLink x) {
        for (TreeLink fa = nullptr; (fa = x->father) != nullptr; rotate(x))
            if (fa->father != nullptr)
                rotate((get_w(fa) == get_w(x)) ? fa : x);
        Root = x;
}

int Splay_Tree::get_w(TreeLink x) {
    if(x->father)
        return x->father->rch == x;
    else return 0;
}

void Splay_Tree::Get_inorder_traversal(TreeLink p, TreeNode *t, int i) {
    if(p == nullptr) return;
    if(p->lch) Get_inorder_traversal(p->lch, t, i);
    t[++temp_cnt[i]] = *p;
    if(p->rch) Get_inorder_traversal(p->rch, t, i);
}

TreeLink Splay_Tree::Build_Tree(TreeNode *t, TreeLink fa, int l, int r) {
    if(l > r) return nullptr;
    int mid = (l + r + 1) / 2;
    TreeLink newNode = (TreeLink)malloc(sizeof(TreeNode));
    newNode->value = t[mid].value;
    newNode->cnt = t[mid].cnt;
    newNode->lch = newNode->rch = nullptr;
    newNode->father = fa;
    if(l < mid) newNode->lch = Build_Tree(t, newNode, l, mid-1);
    if(mid < r) newNode->rch = Build_Tree(t, newNode, mid+1, r);
    push_up(newNode);
    return newNode;
}

void Splay_Tree::merge(){
    temp_cnt[1] = temp_cnt[2] = temp_cnt[3] = 0;
    Get_inorder_traversal(Root->lch, temp1, 1);
    Get_inorder_traversal(Root->rch, temp2, 2);
    int i = 1, j = 1;
    while(i <= temp_cnt[1] && j <= temp_cnt[2]){
        if(temp1[i].value < temp2[j].value) {
            temp3[++temp_cnt[3]] = temp1[i]; ++i;
        }
        else if(temp1[i].value > temp2[j].value){
            temp3[++temp_cnt[3]] = temp2[j]; ++j;
        }
        else{
            temp3[++temp_cnt[3]].value = temp1[i].value;
            temp3[temp_cnt[3]].cnt = temp1[i].cnt + temp2[j].cnt;
            ++i; ++j;
        }
    }
    while(i <= temp_cnt[1]) {
        temp3[++temp_cnt[3]] = temp1[i]; ++i;
    }
    while(j <= temp_cnt[2]) {
        temp3[++temp_cnt[3]] = temp2[j]; ++j;
    }
//    for(int i=1; i<=temp_cnt[3]; ++i)
//        printf("%d ",temp3[i].value);
//    puts("");
    Root = Build_Tree(temp3, nullptr, 1, temp_cnt[3]);
    isSplit = 0;
}


TreeLink Splay_Tree::SPLIT(int x) {
    insert(Root, x);
    TreeLink ans = Root->rch;
    Root->rch = nullptr;
    push_up(Root);
    del(Root, x);
    return ans;
}

void Splay_Tree::split(int x){
    TreeLink newRoot = (TreeLink)malloc(sizeof(TreeNode));
    newRoot->father = nullptr;
    newRoot->value = newRoot->cnt = 0;
    newRoot->rch = SPLIT(x);
    newRoot->lch = Root;
    if(newRoot->lch) newRoot->lch->father = newRoot;
    if(newRoot->rch) newRoot->rch->father = newRoot;
    Root = newRoot;
    push_up(Root);
    isSplit = 1;
}

void Splay_Tree::rel(TreeLink &p) {
    if (p == nullptr) return;
    if(p->lch) rel(p->lch);
    if(p->rch) rel(p->rch);
    free(p);
    p= nullptr;
}

Splay_Tree::Splay_Tree() {
    Root = nullptr;
    isSplit = 0;
}

Splay_Tree::~Splay_Tree() {
    rel(Root);
    Root = nullptr;
}
