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
    int value;
    int Splited;
public slots:
    void fnd();
    void ins();
    void del();
    void UpdateValue();
    void reset();
    void split();
    void merge();
private:
    Ui::BST *ui;
    QLabel *msgLabel;
    QLabel *rltLabel;
    void iniUI();
    void SetPaint();
    int BSTtype;                                                        //平衡树类型
    TreeLink SelectedNode;
    int SelectedTree;
    TreeLink SBT_SelectedNode;
    TreeLink Splay_SelectedNode;
    TreeLink AVL_SelectedNode;
    TreeLink Treap_SelectedNode;
    double NodeWidth;
    double NodeHeight;
    double NodeGapX;
    double NodeGapY;
    int textHeight;
    void CalcWidth(TreeLink x);
    void CalcPos(TreeLink t, double x, double y);
    void GenScene(TreeLink x, QGraphicsScene *scene);
    void PaintTree(TreeLink x, QGraphicsScene *scene);
    void wheelEvent(QWheelEvent *event) override;
    void GenTitle(TreeLink x, QGraphicsScene *scene);
};


#endif //BST_BST_H
