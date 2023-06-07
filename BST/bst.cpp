//
// Created by wangm on 2023/6/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BST.h" resolved

#include <QIntValidator>
#include "bst.h"
#include "ui_BST.h"
#include "QGraphicsItem"
#include "QMouseEvent"

BST::BST(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::BST) {
    ui->setupUi(this);
    iniUI();
}

BST::~BST() {
    delete ui;
}

void BST::iniUI() {
    // set background color white
    auto *scene = new QGraphicsScene;
    scene->setBackgroundBrush(Qt::white);
    ui->PaintTree->setScene(scene);
    // set GuiNode size and gap
    NodeWidth = 80;
    NodeHeight = 40;
    NodeGapX = 40;
    NodeGapY = 40;

    // set text size
    textHeight = 15;

    // implement msgLabel
    msgLabel = new QLabel;
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    ui->statusbar->addWidget(msgLabel);

    // implement rltLabel
    rltLabel = new QLabel;
    rltLabel->setMinimumSize(rltLabel->sizeHint());
    rltLabel->setAlignment(Qt::AlignHCenter);
    ui->statusbar->addWidget(rltLabel);

    // initial status bar
    ui->statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

    // initial msgLabel to choose Splay
    ui->isSplay->setChecked(true);
    BSTtype = 0;
    msgLabel->setText("BST type: Splay");

    // initial rtlLabel to welcome
    rltLabel->setText("Welcome!");

    // connect radiobutton to painter
    connect(ui->isSplay, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("BST type: Splay");
            BSTtype = 0;
            SetPaint();
        }
    });
    connect(ui->isSBT, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("BST type: SBT");
            BSTtype = 1;
            SetPaint();
        }
    });
    connect(ui->isAVL, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("BST type: AVL");
            BSTtype = 2;
            SetPaint();
        }

    });
    connect(ui->isTreap, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("BST type: Treap");
            BSTtype = 3;
            SetPaint();
        }
    });

    // set inputNumber int
    ui->inputNumber->setValidator(new QIntValidator(ui->inputNumber));

    // set inputNumber placeholder text
    ui->inputNumber->setPlaceholderText("input argument");

    // connect inputNumber to value
    connect(ui->inputNumber, SIGNAL(textChanged(QString)), this, SLOT(UpdateValue()));

    //connect fnd ins del
    connect(ui->isfind, SIGNAL(clicked(bool)), this, SLOT(fnd()));
    connect(ui->isdelete, SIGNAL(clicked(bool)), this, SLOT(del()));
    connect(ui->isinsert, SIGNAL(clicked(bool)), this, SLOT(ins()));
    connect(ui->isreset, SIGNAL(clicked(bool)), this, SLOT(reset()));
}

void BST::SetPaint() {
    auto *scene = new QGraphicsScene;
    scene->setBackgroundBrush(Qt::white);
    switch (BSTtype) {
        case 0:
            scene->addText("This is Splay");
            break;
        case 1:
            //scene->addText("This is SBT");
            PaintTree(SBTtree.root, scene);
            break;
        case 2:
            scene->addText("This is AVL");
            break;
        case 3:
            scene->addText("This is Treap");
    }
    ui->PaintTree->setScene(scene);
}



void BST::CalcWidth(TreeLink x) {
    if (x == nullptr) return;
    x->width = NodeWidth;
    if (x->lch == nullptr && x->rch == nullptr)
        return;
    if (x->lch != nullptr) {
        CalcWidth(x->lch);
        x->width += x->lch->width + NodeGapX / 2.0 - NodeWidth / 2.0;
    }
    if (x->rch != nullptr) {
        CalcWidth(x->rch);
        x->width += x->rch->width + NodeGapX / 2.0 - NodeWidth / 2.0;
    }
}

void BST::CalcPos(TreeLink t, double x, double y) {
    if (t == nullptr) return;
    t->x = x; t->y = y;
    double lrwidth;
    double rlwidth;
    if (t->lch != nullptr) {
        lrwidth = (t->lch->rch != nullptr) ? t->lch->rch->width : 0;
        lrwidth = (lrwidth + NodeGapX / 2.0 < NodeWidth / 2.0) ? NodeWidth / 2.0 - NodeGapX / 2.0 : lrwidth;
        CalcPos(t->lch, x - NodeGapX - lrwidth, y + NodeGapY + NodeHeight);
    }
    if (t->rch != nullptr) {
        rlwidth = (t->rch->lch != nullptr) ? t->rch->lch->width : 0;
        rlwidth = (rlwidth + NodeGapX / 2.0 < NodeWidth / 2.0) ? NodeWidth / 2.0 - NodeGapX / 2.0 : rlwidth;
        CalcPos(t->rch, x + NodeGapX + rlwidth, y + NodeGapY + NodeHeight);
    }
}

void BST::GenScene(TreeLink x, QGraphicsScene *scene) {
    if (x == nullptr) return;
    // gen rect
    auto *rect = new QGraphicsRectItem(QRectF(x->x,x->y,NodeWidth,NodeHeight));
    QPen    pen;
    pen.setWidth(2);
    rect->setPen(pen);
    if (x == SelectedNode)
        rect->setBrush(Qt::red);
    else
        rect->setBrush(Qt::darkBlue);
    scene->addItem(rect);

    // gen text
    auto *data = new QGraphicsTextItem;
    auto *NodeValue = new QString;
    auto *NodeCnt = new QString;
    NodeValue->setNum(x->value);
    NodeCnt->setNum(x->cnt);
    data->setPlainText(*NodeValue + "(" + *NodeCnt + ")");
    QFont font = data->font();
    font.setPointSize(textHeight);
    data->setFont(font);
    data->setPos(x->x, x->y);
    scene->addItem(data);

    if (x->lch != nullptr) {
        auto *Lline = new QGraphicsLineItem(x->x, x->y + NodeHeight, x->lch->x + NodeWidth / 2.0, x->lch->y);
        Lline->setPen(pen);
        scene->addItem(Lline);
        GenScene(x->lch, scene);
    }
    if (x->rch != nullptr) {
        auto *Rline = new QGraphicsLineItem(x->x + NodeWidth, x->y + NodeHeight, x->rch->x + NodeWidth / 2.0, x->rch->y);
        Rline->setPen(pen);
        scene->addItem(Rline);
        GenScene(x->rch, scene);
    }
}

void BST::PaintTree(TreeLink x, QGraphicsScene *scene) {
    if (x == nullptr) return;
    CalcWidth(x);
    CalcPos(x, 0, 0);
    GenScene(x, scene);
}

void BST::fnd() {
    SBT_SelectedNode = SBTtree.fnd(SBTtree.root, value);
    switch (BSTtype) {
        case 0:
            //scene->addText("This is Splay");
            break;
        case 1:
            //scene->addText("This is SBT");
            SelectedNode = SBT_SelectedNode;
            break;
        case 2:
            //scene->addText("This is AVL");
            break;
        case 3:
            //scene->addText("This is Treap");
            break;
    }
    QString st;
    st.setNum(value);
    if (SelectedNode == nullptr)
        rltLabel->setText(st + " not found");
    else
        rltLabel->setText(st + " found");
    SetPaint();
}

void BST::ins() {
    SBT_SelectedNode = SBTtree.ins(SBTtree.root, value);
    switch (BSTtype) {
        case 0:
            //scene->addText("This is Splay");
            break;
        case 1:
            //scene->addText("This is SBT");
            SelectedNode = SBT_SelectedNode;
            break;
        case 2:
            //scene->addText("This is AVL");
            break;
        case 3:
            //scene->addText("This is Treap");
            break;
    }
    QString st;
    st.setNum(value);
    rltLabel->setText(st + " inserted");
    SetPaint();
}

void BST::del() {
    QString st;
    st.setNum(value);
    int flag, SBT_flag;
    SBT_flag = SBTtree.del(SBTtree.root, value);
    SBT_SelectedNode = SBTtree.fnd(SBTtree.root, value);
    switch (BSTtype) {
        case 0:
            //scene->addText("This is Splay");
            break;
        case 1:
            //scene->addText("This is SBT");
            flag = SBT_flag;
            SelectedNode = SBT_SelectedNode;
            break;
        case 2:
            //scene->addText("This is AVL");
            break;
        case 3:
            //scene->addText("This is Treap");
            break;
    }
    switch (flag) {
        case 0:
            rltLabel->setText(st + " not found");
            break;
        case 1:
            rltLabel->setText(st + " deleted and still left");
            break;
        case 2:
            rltLabel->setText(st + " deleted");
            break;
        default:
            rltLabel->setText("del is wrong");
    }
    SetPaint();
}

void BST::reset() {
    SBTtree.rel(SBTtree.root);
    SBTtree.root = nullptr;
    rltLabel->setText("reset");
    SetPaint();
}

void BST::UpdateValue() {
    value = ui->inputNumber->text().toInt();
}

void BST::wheelEvent(QWheelEvent *event)
{
    int wheelValue = event->angleDelta().y();
    double ratio = (double)wheelValue / (double)1200 + 1;
    ui->PaintTree->scale(ratio, ratio);
}
