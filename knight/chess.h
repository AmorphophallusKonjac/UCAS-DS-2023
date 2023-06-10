//
// Created by wangm on 2023/6/9.
//

#ifndef KNIGHT_CHESS_H
#define KNIGHT_CHESS_H

#include <cstdlib>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>

typedef struct TreeNode {
    int x, y;
    TreeNode *lch, *rch, *fa;
} TreeNode, *TreeLink;

typedef struct dir {
    int dir, cnt;
} dir;

typedef std::queue <dir> DIR;

typedef struct Pos {
    int x, y;
    DIR direction;
    TreeLink p;
} Pos;


class chess {
public:
    chess();
    int result[8][8]{0};
    int x0, y0;
    TreeLink root;
    void reset();
    bool calc();
private:
    void rel(TreeLink x);
    static TreeLink NewNode(int x, int y);
    DIR GenNext(int x, int y);
    static bool cmp(dir a, dir b);
    int dx[8] = {-2, -1, 1, 2, -2, -1, 1, 2};
    int dy[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
    static bool InRange(int x, int y);
    int vis[8][8]{0};
};


#endif //KNIGHT_CHESS_H
