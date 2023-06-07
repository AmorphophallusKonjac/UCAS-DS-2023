//
// Created by wangm on 2023/6/4.
//

#ifndef BST_NODE_H
#define BST_NODE_H

typedef struct TreeNode{
    int value, size, depth, key, cnt, bf;
    double width, x, y;                             // gui使用，注意不要占用
    struct TreeNode *lch, *rch, *fa;
} TreeNode, *TreeLink;

#endif //BST_NODE_H