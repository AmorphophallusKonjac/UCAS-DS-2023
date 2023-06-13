//
// Created by wangm on 2023/6/9.
//

#include "chess.h"

chess::chess() {
    x0 = y0 = 0;
    root = nullptr;
}

void chess::reset() {
    x0 = y0 = 0;
    rel(root);
    root = nullptr;
    for (auto & i : result)
        for (auto & j : i)
            for (int & k : j)
                k = 0;
}

void chess::rel(TreeLink x) {
    if (x == nullptr) return;
    for (EdgeLink i = x->h; i != nullptr; i = i->ne) {
        TreeLink y = i->ot;
        rel(y);
    }
    free(x);
}

int chess::calc() {
    std::stack <Pos> stack;
    int cnt = 1, CntAns = 0;
    int rlt_mid[8][8]{0};
    vis[x0][y0] = 1;
    rlt_mid[x0][y0] = cnt;
    root = NewNode(x0, y0);
    stack.push({x0,y0,GenNext(x0, y0), root});
    while (!stack.empty() && CntAns < MAXANS) {
        if (cnt == 64) {
            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 8; ++j)
                        result[CntAns][i][j] = rlt_mid[i][j];
            ++CntAns;
        }
        int x = stack.top().x;
        int y = stack.top().y;
        DIR q = stack.top().direction;
        TreeLink s = stack.top().p;
        if (q.empty()) {
            rlt_mid[x][y] = 0;
            vis[x][y] = 0;
            --cnt;
            stack.pop();
        }
        else {
            int xx = x + dx[q.front().dir], yy = y + dy[q.front().dir];
            if (!q.front().cnt && cnt < 63) {
                rlt_mid[x][y] = 0;
                vis[x][y] = 0;
                --cnt;
                stack.pop();
            }
            else {
                stack.top().direction.pop();
                vis[xx][yy] = 1;
                rlt_mid[xx][yy] = ++cnt;
                TreeLink t = NewNode(xx, yy);
                EdgeLink e = NewEdge(s, t);
                stack.push({xx, yy, GenNext(xx, yy), t});
            }
        }
    }
    for (; !stack.empty(); stack.pop());
    for (auto & i : vis)
        for (int & j : i)
                j = 0;
    return CntAns;
}

TreeLink chess::NewNode(int x, int y) {
    auto p = (TreeLink) malloc(sizeof(TreeNode));
    p->h = nullptr;
    p->t = nullptr;
    p->x = x;
    p->y = y;
    p->fa = nullptr;
    return p;
}

DIR chess::GenNext(int x, int y) {
    std::vector <dir> v;
    DIR q;
    for (int i = 0; i < 8; ++i) {
        if (InRange(x + dx[i], y + dy[i]) && !vis[x + dx[i]][y + dy[i]]) {
            int xx = x + dx[i], yy = y + dy[i], cnt = 0;
            for (int j = 0; j < 8; ++j) {
                if (InRange(xx + dx[j], yy + dy[j]) && !vis[xx + dx[j]][yy + dy[j]]) {
                    ++cnt;
                }
            }
            v.push_back({i, cnt});
        }
    }
    std::sort(v.begin(), v.end(), cmp);
    for (auto i : v)
        q.push(i);
    return q;
}

bool chess::cmp(dir a, dir b) {
    return a.cnt < b.cnt;
}

bool chess::InRange(int x, int y) {
    return 0 <= x && x < 8 && 0 <= y && y < 8;
}

EdgeLink chess::NewEdge(TreeLink x, TreeLink y) {
    auto p = (EdgeLink)malloc(sizeof(Edge));
    p->ot = y;
    p->ne = nullptr;
    if (x->h == nullptr) {
        x->h = x->t = p;
    }
    else {
        x->t->ne = p;
        x->t = p;
    }
    return p;
}
