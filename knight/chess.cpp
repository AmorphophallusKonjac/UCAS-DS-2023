//
// Created by wangm on 2023/6/9.
//

#include <cstdlib>
#include <stack>
#include "chess.h"

typedef struct Pos {
    int x, y, DIR;
} Pos;

chess::chess() {
    x0 = y0 = 0;
    root = nullptr;
}

void chess::reset() {
    x0 = y0 = 0;
    rel(root);
    root = nullptr;
    for (auto & i : result)
        for (int & j : i)
            j = 0;
}

void chess::rel(TreeLink x) {
    if (x == nullptr) return;
    rel(x->lch);
    rel(x->rch);
    free(x);
}

void chess::calc() {

}

void chess::dfs() {
    std::stack<Pos> stack;
    int vis[8][8]{0};
    int cnt = 1;
    vis[x0][y0] = 1;
    stack.push({x0,y0,0});
    while (!stack.empty()) {
        int x = stack.top().x;
        int y = stack.top().y;
        GenNext
    }
}

TreeLink chess::newnode(int x, int y) {
    auto p = (TreeLink) malloc(sizeof(TreeNode));
    p->x = x;
    p->y = y;
    p->lch = p->rch = p->fa = nullptr;
    return p;
}
