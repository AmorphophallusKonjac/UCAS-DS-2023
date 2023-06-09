//
// Created by hp on 2023/6/8.
//


#ifndef BST_TREAP_H
#define BST_TREAP_H
#define MAXN 100

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "node.h"

class TREAP {
public:
    TREAP();
    ~TREAP();
    TreeLink Root;
    int isSplit;
    void insert(TreeLink &p, int x);
    int del(TreeLink &p, int x);
    TreeLink find_pre(TreeLink p, int x);
    TreeLink find_suf(TreeLink p, int x);
    TreeLink find_kth(TreeLink p, int k);    //查找第k大的结点
    int find_rank(TreeLink p, int x);   //查找值为x的结点的rank,当返回值rank非0时查找成功,并把它Splay到Root
    void split(int x);  //将当前树分裂,小于等于x的点在左子树,大于x的点在右子树
    void merge();   //把虚根的左右子树合并
    void rel(TreeLink &p);
private:
    void push_up(TreeLink p);
    void left_rotate(TreeLink &p);
    void right_rotate(TreeLink &p);
    void MERGE(TreeLink a); //把a子树合并到当前树中
    void SPLIT(TreeLink p, TreeLink &T1, TreeLink &T2, int x);  //把树p分裂到T1和T2中
};


#endif //BST_TREAP_H
