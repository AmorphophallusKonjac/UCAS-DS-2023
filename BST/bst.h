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
    void ExPaint(TreeLink x, QGraphicsScene* scene);
    int BSTtype;                                    //平衡树类型
};


#endif //BST_BST_H
