//
// Created by wangm on 2023/6/4.
//

#ifndef BST_SBT_H
#define BST_SBT_H

#include "node.h"

namespace SBT {

    class SBT {
    public:
        TreeLink root;
        void init();            //初始化SBT
    private:
        void LeftRotate(TreeLink);      //左旋
        void RightRotate(TreeLink);     //右旋
    };

} // SBT

#endif //BST_SBT_H
