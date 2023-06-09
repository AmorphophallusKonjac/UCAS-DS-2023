//
// Created by wangm on 2023/6/7.
//

// this source code is created by Wang Haoyu and wangm transfer it to class board

#ifndef KNIGHT_BOARD_H
#define KNIGHT_BOARD_H

typedef struct BiTNode // 二叉树存储结构
{
    int x; // x坐标
    int y; // y坐标
    struct BiTNode *lchild,*rchild,*parent;
}BiTNode,*BiTree;

class board {
public:
    int x, y;
    int result[8][8] = {0}; // 最终的8x8数组
    BiTree T;
    board();
    void reset();
    void calc();
    int backward_count;
private:
    int Stack[100][3]={0};
    int chessboard[12][12] = {0};		//12 x 12 数组,边缘附加部分方便写程序
    int cnt = 1;			//标记马已走的方格数
    int move[8][2]={ {2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};	//初始马当前位置向其周围相邻八个日字的 x,y的偏移量
    void DFS(int x,int y,BiTree * Tp);
    void rel(BiTree t);
};


#endif //KNIGHT_BOARD_H
