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
    int dx = 10; int dy = 20; int k = 2;
    auto *scene = new QGraphicsScene;
    //scene->setSceneRect(QRectF(0,0,800,600));
    auto   *item = new QGraphicsEllipseItem(QRectF(0,0,50,50));
    QGraphicsTextItem *testText = new QGraphicsTextItem;
    testText->setPlainText(tr("12"));
    testText->setPos(500, 500);
    QPen    pen;
    pen.setWidth(2);
    item->setPen(pen);
    item->setBrush(Qt::red);


    scene->addItem(item);
    scene->addItem(testText);
    scene->setBackgroundBrush(Qt::green);
    /*switch (BSTtype) {
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
    }*/
    ui->PaintTree->setScene(scene);
}

void BST::ExPaint(TreeLink x, QGraphicsScene *scene) {

}
