//
// Created by hp on 2023/6/12.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "node.h"

#ifndef BST_AVL_H
#define BST_AVL_H
#define MAXN 100

class AVL {
public:
    TreeLink Root = nullptr;
    int isSplit;
    TreeLink insert(TreeLink &p, int x, int Root_w = 0);
    int del(TreeLink &p, int x, int Root_w = 0);
    TreeLink find_pre(TreeLink p, int x);
    TreeLink find_suf(TreeLink p, int x);
    TreeLink find_kth(TreeLink p, int k);    //查找第k大的结点
    TreeLink find_rank(TreeLink p, int x, int &ans);   //查找值为x的结点的rank,把rank值存入ans中,返回查找到的结点
    void split(int x);  //将当前树分裂,小于等于x的点在左子树,大于x的点在右子树
    void merge();   //把虚根的左右子树合并
    TreeLink Build_Tree(TreeNode *t, TreeLink fa, int l, int r, int &dep);  //dep用于传递深度值,以计算bf
    void rel(TreeLink &p);
private:
    TreeNode temp1[MAXN], temp2[MAXN], temp3[MAXN];
    int temp_cnt[4];
    void push_up(TreeLink p);
    int get_w(TreeLink x);
    void left_rotate(TreeLink &p);
    void right_rotate(TreeLink &p);
    void Get_inorder_traversal(TreeLink p, TreeNode *t, int i);
};

#endif //BST_AVL_H
