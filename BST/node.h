//
// Created by wangm on 2023/6/4.
//

#ifndef BST_NODE_H
#define BST_NODE_H

typedef struct TreeNode{
    int value, size, depth, father, key, cnt, bf;
    struct TreeNode *lch, *rch;
} TreeNode, *TreeLink;

#endif //BST_NODE_H
