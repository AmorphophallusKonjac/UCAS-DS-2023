//
// Created by wangm on 2023/6/9.
//

#ifndef KNIGHT_CHESS_H
#define KNIGHT_CHESS_H

typedef struct TreeNode {
    int x, y;
    TreeNode *lch, *rch, *fa;
} TreeNode, *TreeLink;

class chess {
public:
    chess();
    int result[8][8]{0};
    int x0, y0;
    TreeLink root;
    void reset();
    void calc();
private:
    void rel(TreeLink x);
    void dfs();
    static TreeLink newnode(int x, int y);
};


#endif //KNIGHT_CHESS_H
