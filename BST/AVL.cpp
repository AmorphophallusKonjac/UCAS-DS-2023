//
// Created by hp on 2023/6/12.
//

#include "AVL.h"

void AVL::push_up(TreeLink x) {
    if(x!=nullptr)
        x->size = (x->lch ? x->lch->size : 0)
                  + (x->rch ? x->rch->size : 0) + x->cnt;
}

int AVL::get_w(TreeLink x) {
    if(x->father)
        return x->father->rch == x;
    else return 0;
}

void AVL::left_rotate(TreeLink &x) {
    TreeLink y = x->father, z = y->father;
    int w1 = get_w(y);
    y->rch = x->lch; if(y->rch) y->rch->father = y;
    x->lch = y; y->father = x;
    x->father = z;
    if (z != nullptr) {
        if (w1 == 0) z->lch = x;
        else z->rch = x;
    }
    push_up(y);
    push_up(x);
}

void AVL::right_rotate(TreeLink &x) {
    TreeLink y = x->father, z = y->father;
    int w1 = get_w(y);
    y->lch = x->rch; if(y->lch) y->lch->father = y;
    x->rch = y; y->father = x;
    x->father = z;
    if(z != nullptr){
        if(w1 == 0) z->lch = x;
        else z->rch = x;
    }
    push_up(y);
    push_up(x);
}

TreeLink AVL::find_pre(TreeLink p, int x) {
    if(p == nullptr) return p;
    if(p->value < x) {
        TreeLink find_rch = find_pre(p->rch, x);
        return find_rch ? find_rch : p;
    }
    else return find_pre(p->lch, x);
}

TreeLink AVL::find_suf(TreeLink p, int x) {
    if(p == nullptr) return nullptr;
    if(p->value > x) {
        TreeLink find_lch = find_suf(p->lch, x);
        return find_lch ? find_lch : p;
    }
    else return find_suf(p->rch, x);
}

TreeLink AVL::find_kth(TreeLink p, int k) {
    if (p == nullptr) { return nullptr; }
    int lsize = p->lch ? p->lch->size : 0;
    if (k <= lsize)
        return find_kth(p->lch, k);
    else if (k > lsize + p->cnt)
        return find_kth(p->rch, k - lsize - p->cnt);
    else return p;
}

TreeLink AVL::find_rank(TreeLink p, int x, int &ans) {
    if(p == nullptr){
        ans = 0;
        return nullptr;
    }
    if(p->value == x){
        ans = (p->lch ? p->lch->size : 0) + 1;
        return p;
    }
    else if(x < p->value)
        return find_rank(p->lch, x, ans);
    else {
        TreeLink rtn = find_rank(p->rch, x, ans);
        ans += (p->lch ? p->lch->size : 0) + p->cnt;
        return rtn;
    }
}

TreeLink AVL::insert(TreeLink &p, int x, int Root_w) {
    TreeLink tempRoot = Root;
    if(isSplit){
        Root = p;
        if(Root) Root->father = nullptr;
    }
    TreeLink rtn;
    if(Root == nullptr){
        Root = (TreeLink) malloc(sizeof (TreeNode));
        Root->lch = Root->rch = Root->father = nullptr;
        Root->value = x;
        Root->cnt = Root->size = 1;
        Root->bf = 0;
        rtn = Root;
    }
    else {
        TreeLink now = p;
        TreeLink fa = nullptr;
        while (now) {
            if (x == now->value) {
                now->cnt++;
                push_up(now);
                return now;
            }
            now->size++;
            fa = now;
            now = (x > now->value) ? now->rch : now->lch;
        }
        now = (TreeLink) malloc(sizeof(TreeNode));
        now->value = x;
        now->cnt = now->size = 1;
        now->bf = 0;
        now->father = fa;
        now->lch = now->rch = nullptr;
        if (x > fa->value) fa->rch = now;
        else fa->lch = now;
        rtn = now;

        while (fa) {
            if (now == fa->lch) fa->bf--;
            else fa->bf++;
            if (fa->bf == 0) break;
            else if (fa->bf == 1 || fa->bf == -1) {
                now = fa;
                fa = now->father;
            } else if (fa->bf == 2 || fa->bf == -2) {
                if (fa->bf == -2 && now->bf == -1) {    //LL型
                    right_rotate(now);
                    now->bf = fa->bf = 0;
                    if (!now->father) Root = now;
                    break;
                } else if (fa->bf == 2 && now->bf == 1) {  //RR型
                    left_rotate(now);
                    now->bf = fa->bf = 0;
                    if (!now->father) Root = now;
                    break;
                } else if (fa->bf == -2 && now->bf == 1) { //LR型
                    TreeLink temp = now->rch;
                    left_rotate(temp);
                    right_rotate(temp);
                    now->bf = fa->bf = temp->bf = 0;
                    if (!temp->father) Root = temp;
                    break;
                } else if (fa->bf == 2 && now->bf == -1) { //RL型
                    TreeLink temp = now->lch;
                    right_rotate(temp);
                    left_rotate(temp);
                    now->bf = fa->bf = temp->bf = 0;
                    if (!temp->father) Root = temp;
                    break;
                } else {
                    printf("ERROR %d %d %d\n", x, fa->bf, now->bf);
                    break;
                }
            } else {
                printf("ERROR %d %d %d\n", x, fa->bf, now->bf);
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

int AVL::del(TreeLink &p, int x, int Root_w){
    if(Root == nullptr) return 0;

    TreeLink tempRoot = Root;
    if(isSplit){
        Root = p;
        if(Root) Root->father = nullptr;
    }

    TreeLink now = Root;
    TreeLink fa = nullptr;
    TreeLink Del_Node = nullptr;
    int rtn = 2;
    while(1){
        if(x == now->value){
            if(now->cnt > 1){
                now->cnt --;
                while(fa){
                    --fa->size;
                    fa = fa->father;
                }
                rtn = 1;
                break;
            }
            if(now->rch == nullptr){
                if(get_w(now)){
                    Del_Node = now;
                    break;
                }
                else{
                    Del_Node = now;
                    break;
                }
            }
            else{
                TreeLink suf = find_suf(now, now->value);
                now->value = suf->value;
                now->cnt = suf->cnt;
                Del_Node = suf;
                now = suf;
                fa = now->father;
                break;
            }
        }
        fa = now;
        now = (x > now->value) ? now->rch : now->lch;
        if(now == nullptr){
            rtn = 0;
            break;
        }
    }
    while(fa){
        if(now == fa->lch) fa->bf ++;
        else fa->bf --;
        if(fa->bf == 0){
            now = fa;
            fa = now->father;
        }
        else if(fa->bf == 2 || fa->bf == -2) {
            TreeLink sibling = (get_w(now)) ? fa->lch : fa->rch;
            if (fa->bf == -2 && (sibling->bf == -1 || sibling->bf == 0) ) {    //LL型
                right_rotate(sibling);
                if(sibling->bf) sibling->bf = fa->bf = 0;
                else sibling->bf = 1, fa->bf = -1;
                if(!sibling->father) Root = sibling;
                break;
            }
            else if(fa->bf == 2 && (sibling->bf == 1 || sibling->bf == 0) ) {  //RR型
                left_rotate(sibling);
                if(sibling->bf) sibling->bf = fa->bf = 0;
                else sibling->bf = -1, fa->bf = 1;
                if(!sibling->father) Root = sibling;
                break;
            }
            else if(fa->bf == -2 && sibling->bf == 1) { //LR型
                TreeLink temp = sibling->rch;
                left_rotate(temp);
                right_rotate(temp);
                sibling->bf = fa->bf = temp->bf = 0;
                if(!temp->father) Root = temp;
                break;
            }
            else if(fa->bf == 2 && sibling->bf == -1){ //RL型
                TreeLink temp = sibling->lch;
                right_rotate(temp);
                left_rotate(temp);
                sibling->bf = fa->bf = temp->bf = 0;
                if(!temp->father) Root = temp;
                break;
            }
            else{
                printf("ERROR %d %d %d\n", x, fa->bf, now->bf);
                break;
            }
        }
        else break;
    }
    if(Del_Node->rch){
        if(Del_Node->father){
            if(get_w(Del_Node))
                Del_Node->father->rch = Del_Node->rch;
            else
                Del_Node->father->lch = Del_Node->rch;
        }
        else Root = Del_Node->rch;
    }
    else{
        if(Del_Node->father){
            if(get_w(Del_Node))
                Del_Node->father->rch = Del_Node->lch;
            else
                Del_Node->father->lch = Del_Node->lch;
        }
        else Root = Del_Node->lch;
    }
    if(isSplit){
        if(Root_w) tempRoot->rch = Root;
        else tempRoot->lch = Root;
        if(Root) Root->father = tempRoot;
        Root = tempRoot;
    }
    return rtn;
}

void AVL::Get_inorder_traversal(TreeLink p, TreeNode *t, int i) {
    if(p == nullptr) return;
    if(p->lch) Get_inorder_traversal(p->lch, t, i);
    t[++temp_cnt[i]] = *p;
    if(p->rch) Get_inorder_traversal(p->rch, t, i);
}

TreeLink AVL::Build_Tree(TreeNode *t, TreeLink fa, int l, int r, int &dep) {
    if(l > r) return nullptr;
    int mid = (l + r + 1) / 2;
    TreeLink newNode = (TreeLink)malloc(sizeof(TreeNode));
    newNode->value = t[mid].value;
    newNode->cnt = t[mid].cnt;
    newNode->lch = newNode->rch = nullptr;
    newNode->father = fa;
    int depl = 0 ,depr = 0;
    if(l < mid) newNode->lch = Build_Tree(t, newNode, l, mid-1, depl);
    if(mid < r) newNode->rch = Build_Tree(t, newNode, mid+1, r, depr);
    newNode->bf = depr - depl;
    dep = (depl > depr) ? depl + 1 : depr + 1;
    push_up(newNode);
    return newNode;
}

void AVL::merge(){
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
    int dep = 0;
    Root = Build_Tree(temp3, nullptr, 1, temp_cnt[3], dep);
    isSplit = 0;
}

void AVL::split(int x){
    temp_cnt[1] = temp_cnt[2] = temp_cnt[3] = 0;
    Get_inorder_traversal(Root, temp3, 3);
    for(int i = 1; i <= temp_cnt[3]; ++i){
        if(temp3[i].value <= x)
            temp1[++temp_cnt[1]] = temp3[i];
        else
            temp2[++temp_cnt[2]] = temp3[i];
    }
//    for(int i=1; i<=temp_cnt[3]; ++i)
//        printf("%d ",temp3[i].value);
//    puts("");
    Root = (TreeLink) malloc(sizeof (TreeNode));
    Root->lch = Root->rch = Root->father = nullptr;
    Root->size = Root->cnt = Root->value = Root->bf = 0;
    int dep = 0;
    Root->lch = Build_Tree(temp1, Root, 1, temp_cnt[1], dep);
    dep = 0;
    Root->rch = Build_Tree(temp2, Root, 1, temp_cnt[2], dep);
    isSplit = 1;
}

void AVL::rel(TreeLink &p) {
    if (p == nullptr) return;
    if(p->lch) rel(p->lch);
    if(p->rch) rel(p->rch);
    free(p);
    p= nullptr;
}