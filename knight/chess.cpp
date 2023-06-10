//
// Created by wangm on 2023/6/9.
//

#include "chess.h"
#include "QDebug"

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

bool chess::calc() {
    std::stack <Pos> stack;
    int cnt = 1;
    TreeLink s;
    vis[x0][y0] = 1;
    result[x0][y0] = cnt;
    root = NewNode(x0, y0);
    s = root;
    stack.push({x0,y0,GenNext(x0, y0), nullptr});
    while (!stack.empty() && cnt < 64) {
        int x = stack.top().x;
        int y = stack.top().y;
        DIR q = stack.top().direction;
        TreeLink t = stack.top().p;
        if (q.empty()) {
            result[x][y] = 0;
            vis[x][y] = 0;
            --cnt;
            stack.pop();
        }
        else {
            int xx = x + dx[q.front().dir], yy = y + dy[q.front().dir];
            if (!q.front().cnt && cnt < 63) {
                result[x][y] = 0;
                vis[x][y] = 0;
                --cnt;
                stack.pop();
            }
            else {
                stack.top().direction.pop();
                vis[xx][yy] = 1;
                result[xx][yy] = ++cnt;
                if (t == nullptr) {
                    s->lch = NewNode(xx, yy);
                    s->lch->fa = s;
                    stack.top().p = s->lch;
                    s = s->lch;
                }
                else {
                    t->rch = NewNode(xx, yy);
                    t->rch->fa = t;
                    stack.top().p = t->rch;
                    s = t->rch;
                }
                stack.push({xx, yy, GenNext(xx, yy)});
            }
        }
    }
    if (cnt == 64)
        return true;
    return false;
}

TreeLink chess::NewNode(int x, int y) {
    auto p = (TreeLink) malloc(sizeof(TreeNode));
    p->x = x;
    p->y = y;
    p->lch = p->rch = p->fa = nullptr;
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
