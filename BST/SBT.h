//
// Created by wangm on 2023/6/4.
//

#ifndef BST_SBT_H
#define BST_SBT_H

#include "node.h"
#include <cstdio>
#include <cstdlib>
#include "algorithm"
#include <climits>

class SBT {
    public:
        TreeLink root;
        TreeLink zero;
        void init();                                    //初始化SBT
        TreeLink newnode(int v);                        //新建节点
        int del(TreeLink &x, int v);                    //删除
        void ins(TreeLink &x, int v);                   //插入
        TreeLink fnd(TreeLink &x, int v);               //查找
        int rank(TreeLink &x, int v);                   //排名
        int sel(TreeLink &x, int v);
        int pre(TreeLink &x, int v);
        int suc(TreeLink &x, int v);
    private:
        static void LeftRotate(TreeLink &x);            //左旋
        static void RightRotate(TreeLink &x);           //右旋
        void maintain(TreeLink &x, bool t);             //维持
        void insrt(TreeLink &x, int v);                 //破坏树结构的插入
        int delet(TreeLink &x, int v);             //破坏树结构的删除
};


#endif //BST_SBT_H