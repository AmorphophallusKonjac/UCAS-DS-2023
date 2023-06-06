//
// Created by wangm on 2023/6/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BST.h" resolved

#include "bst.h"
#include "ui_BST.h"
#include "QGraphicsRectItem"
#include "QGraphicsTextItem"


BST::BST(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::BST) {
    ui->setupUi(this);
    iniUI();
}

BST::~BST() {
    delete ui;
}

void BST::iniUI() {
    NodeHeight = 40;
    NodeWeight = 80;
    msgLabel = new QLabel;
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    msgLabel->setText("current BST is Splay");
    ui->statusbar->addWidget(msgLabel);
    ui->isSplay->setChecked(true);
    BSTtype = 0;
    ui->statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    connect(ui->isSplay, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("current BST is Splay");
            BSTtype = 0;
            SetPaint();
        }
    });
    connect(ui->isSBT, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("current BST is SBT");
            BSTtype = 1;
            SetPaint();
        }
    });
    connect(ui->isAVL, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("current BST is AVL");
            BSTtype = 2;
            SetPaint();
        }

    });
    connect(ui->isTreap, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("current BST is Treap");
            BSTtype = 3;
            SetPaint();
        }
    });
}

void BST::SetPaint() {
    auto *scene = new QGraphicsScene;
   /* auto *item = new QGraphicsRectItem(QRectF(0,0,NodeWeight,NodeHeight));
    auto *testText = new QGraphicsTextItem;
    testText->setPlainText("123123");
    QFont font = testText->font();
    font.setPointSize(15);
    testText->setFont(font);
    testText->setPos(100, 100);
    QPen    pen;
    pen.setWidth(2);
    item->setPen(pen);
    item->setBrush(Qt::darkBlue);


    scene->addItem(item);
    scene->addItem(testText);*/
    switch (BSTtype) {
        case 0: scene->addText("This is Splay");
        break;
        case 1:
            //scene->addRect(10, 10, 30, 30);//ExPaint(this->SBTtree.root, scene);//scene->addText("This is SBT");
            //scene->addEllipse(10 - k * dx, 10 + k * dy, 30, 30);
            //scene->addEllipse(10 + k * dx, 10 + k * dy, 30, 30);
            //scene->addLine(10, 10, 10 - k * dx, 10 + k * dy);
            break;
        case 2: scene->addText("This is AVL");
        break;
        case 3: scene->addText("This is Treap");
    }
    ui->PaintTree->setScene(scene);
}

void BST::ExPaint(TreeLink t, QGraphicsScene *scene, int x, int y) {
    auto *rec = new QGraphicsRectItem(QRectF(x, y, x + NodeWeight, y + NodeHeight));

}
