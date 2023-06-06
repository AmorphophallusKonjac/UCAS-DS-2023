//
// Created by wangm on 2023/6/5.
//

#ifndef BST_BST_H
#define BST_BST_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include "SBT.h"


QT_BEGIN_NAMESPACE
namespace Ui { class BST; }
QT_END_NAMESPACE

class BST : public QMainWindow {
Q_OBJECT

public:
    explicit BST(QWidget *parent = nullptr);

    ~BST() override;

    SBT SBTtree;

private:
    Ui::BST *ui;
    QLabel *msgLabel;
    void iniUI();
    void SetPaint();
    void ExPaint(TreeLink t, QGraphicsScene* scene, int x, int y);      //画出树
    int BSTtype;                                                        //平衡树类型
    int NodeWeight;
    int NodeHeight;
};


#endif //BST_BST_H
