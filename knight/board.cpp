//
// Created by wangm on 2023/6/7.
//

// this source code is created by Wang Haoyu and wangm transfer it to class board

#include <cstdlib>
#include <cstring>
#include "board.h"

void board::DFS(int x, int y, BiTree *Tp) {
    for(int m1 = 0 ; m1 <12 ; m1 ++){
        for(int m2 = 0 ; m2 < 12 ; m2 ++){
            if(m1 == 0 || m1 == 1|| m1 == 10 || m1 == 11 || m2 == 0 || m2 == 1 || m2 == 10 || m2 == 11){
                chessboard[m1][m2] = -1;
            }
        }
    }//初始化棋盘,边上填充的部分赋值-1
    BiTree p;
    int top=0,i=0;
    int flag = 0; //0代表左子树,1代表右子树
    int a,b;				//记录当前位置可以到达的位置
    chessboard[x][y]=1;	//代表这里已经走过
    p = *Tp;
    p->x = x-2;
    p->y = y-2;

    Stack[top][0]=Stack[top][1]=2;	//记录当前马的位置
    while(cnt < 64){
        for(;i<8;i++){
            a = x + move[i][0];
            b = y + move[i][1];
            if(chessboard[a][b] == 0){		//如果当前马位置附近的日字没有被访问
                if(flag == 0){
                    p->lchild = (BiTree)malloc(sizeof(BiTNode));
                    p->lchild->x = a-2;
                    p->lchild->y = b-2;
                    p->lchild->parent = p;
                    p=p->lchild;
                    p->lchild = nullptr;
                    p->rchild = nullptr;
                }else{
                    p->rchild = (BiTree)malloc(sizeof(BiTNode));
                    p->rchild->x = a-2;
                    p->rchild->y = b-2;
                    p->rchild->parent = p;
                    p=p->rchild;
                    p->lchild = nullptr;
                    p->rchild = nullptr;
                }
                break;						//跳出循环
            }
        }
        if(i<8){					//能够访问当前马位置附近的日字
            flag = 0;
            chessboard[a][b]=++cnt;
            Stack[top][2]=i;	//记录访问当前马位置走的方向
            top++;					//栈顶变更
            Stack[top][0]=a;	//向新的栈顶放入马的坐标
            Stack[top][1]=b;
            x=a;
            y=b;

            i=0; 					//从栈顶马位置开始寻找附近的 8 个日字
        }
        else{			//当前马没有位置可走
            flag = 1;
            p=p->parent;
            cnt--;				//回溯
            backward_count ++;
            chessboard[x][y]=0;
            top--;		//出栈
            x=Stack[top][0];		//拿到当前马位置的坐标
            y=Stack[top][1];
            i=Stack[top][2];		//拿到当前马位置当时走的方向
            i++; 						//走下一个方向
        }
    }

    for(int m1 = 0 ; m1 <8 ; m1 ++){
        for(int m2 = 0 ; m2 < 8 ; m2 ++){
            result[m1][m2] = chessboard[m1+2][m2+2];
        }
    }//把12x12的数组对应到8x8的结果棋盘
}

board::board() {
    x = 0; y = 0;
    T = nullptr;
    memset(result, 0, sizeof result);
    backward_count = 0;
}

void board::reset() {
    backward_count = 0;
    memset(result, 0, sizeof result);
    rel(T);
    T = nullptr;
}

void board::rel(BiTree t) {
    if (t == nullptr) return;
    rel(t->lchild);
    rel(t->rchild);
    free(t);
}

void board::calc() {
    T = (BiTree)malloc(sizeof(BiTNode));
    T->lchild = nullptr;
    T->rchild = nullptr;
    T->parent = nullptr;
    DFS(x + 2, y + 2, &T);
}
