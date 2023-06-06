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

typedef struct retdata {
    int cnt, value;
} retdata;

class SBT {
    public:
        SBT();
        ~SBT();
        TreeLink root;
        TreeLink newnode(int v);                        //creat new node
        int del(TreeLink &x, int v);                    //delete node
        TreeLink ins(TreeLink &x, int v);               //insert node
        TreeLink fnd(TreeLink &x, int v);               //find node
        int rank(TreeLink &x, int v);                   //find node of x rank
        int sel(TreeLink &x, int v);
        int pre(TreeLink &x, int v);
        int suc(TreeLink &x, int v);
        void rel(TreeLink &x);                          //reset the SBT
    private:
        static void LeftRotate(TreeLink &x);            //左旋
        static void RightRotate(TreeLink &x);           //右旋
        void maintain(TreeLink &x, bool t);             //维持
        TreeLink insrt(TreeLink &x, int v);             //破坏树结构的插入
        retdata delet(TreeLink &x, int v);              //破坏树结构的删除
};


#endif //BST_SBT_H