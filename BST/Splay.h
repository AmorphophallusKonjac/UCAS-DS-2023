//
// Created by hp on 2023/6/7.
//


#ifndef BST_SPLAY_H
#define BST_SPLAY_H
#define MAXN 100

#include <iostream>
#include <cstring>
#include <cstdio>
#include "node.h"

class Splay_Tree {
public:
    Splay_Tree();
    ~Splay_Tree();
    TreeLink Root = nullptr;
    int isSplit = 0;
    void insert(TreeLink &p, int x, int Root_w = 0);    //Root_w用于区分分裂后的树的左右子树，当对左树进行插入时，Root_w=0
    int del(TreeLink &p, int x, int Root_w = 0);
    TreeLink find_pre(TreeLink p);
    TreeLink find_suf(TreeLink p);
    TreeLink find_kth(TreeLink p, int k);   //查找第k大的结点
    int find_rank(TreeLink p, int x, int Root_w = 0);       //查找值为x的结点的rank,当返回值rank非0时查找成功,并把它Splay到Root
    void split(int x);      //把两棵分裂的树作为一个虚根的左右子树
    void merge();       //把虚根的两棵子树合并
    TreeLink Build_Tree(TreeNode *t, TreeLink fa, int l, int r);
    void rel(TreeLink &p);
private:
    TreeNode temp1[MAXN], temp2[MAXN], temp3[MAXN];
    int temp_cnt[4];
    void push_up(TreeLink x);
    void rotate(TreeLink x);
    void Splay(TreeLink x);
    int get_w(TreeLink x);
    TreeLink SPLIT(int x);      //小于等于x的点保留在当前树中,大于x的点在返回值中
    void Get_inorder_traversal(TreeLink p, TreeNode *t, int i);
};


#endif //BST_SPLAY_H
