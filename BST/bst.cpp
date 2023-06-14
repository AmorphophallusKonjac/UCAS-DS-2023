//
// Created by wangm on 2023/6/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BST.h" resolved

#include <QIntValidator>
#include "bst.h"
#include "ui_BST.h"
#include "QGraphicsItem"
#include "QMouseEvent"
#include "QAbstractTextDocumentLayout"

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
    NodeGapX = 50;
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

    // connect type radiobutton to painter
    connect(ui->isSplay, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("BST type: Splay");
            BSTtype = 0;
            SelectedNode = Splay_SelectedNode;
            SetPaint();
        }
    });
    connect(ui->isSBT, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("BST type: SBT");
            BSTtype = 1;
            SelectedNode = SBT_SelectedNode;
            SetPaint();
        }
    });
    connect(ui->isAVL, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("BST type: AVL");
            BSTtype = 2;
            SelectedNode = AVL_SelectedNode;
            SetPaint();
        }

    });
    connect(ui->isTreap, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            msgLabel->setText("BST type: Treap");
            BSTtype = 3;
            SelectedNode = Treap_SelectedNode;
            SetPaint();
        }
    });

    // connect select radiobutton to painter
    connect(ui->isLeft, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            SelectedTree = 0;
        }
    });

    connect(ui->isRight, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked) {
            SelectedTree = 1;
        }
    });

    // set inputNumber int
    ui->inputNumber->setValidator(new QIntValidator(ui->inputNumber));

    // set inputNumber placeholder text
    ui->inputNumber->setPlaceholderText("input argument");

    // set clear button
    ui->inputNumber->setClearButtonEnabled(true);

    // connect inputNumber to value
    connect(ui->inputNumber, SIGNAL(textChanged(QString)), this, SLOT(UpdateValue()));

    // connect fnd ins del split merge
    connect(ui->isfind, SIGNAL(clicked(bool)), this, SLOT(fnd()));
    connect(ui->isdelete, SIGNAL(clicked(bool)), this, SLOT(del()));
    connect(ui->isinsert, SIGNAL(clicked(bool)), this, SLOT(ins()));
    connect(ui->isreset, SIGNAL(clicked(bool)), this, SLOT(reset()));
    connect(ui->issplit, SIGNAL(clicked(bool)), this, SLOT(split()));
    connect(ui->ismerge, SIGNAL(clicked(bool)), this, SLOT(merge()));

    // set isLeft and isRight disable
    ui->isLeft->setChecked(false);
    ui->isRight->setChecked(false);
    ui->isLeft->setDisabled(true);
    ui->isRight->setDisabled(true);

    // set ismerge disable
    ui->ismerge->setDisabled(true);

    // set SelectNode and SelectTree
    SelectedTree = 2;
    SelectedNode = nullptr;

    // set splited 0
    Splited = 0;
}

void BST::SetPaint() {
    delete ui->PaintTree->scene();
    auto *scene = new QGraphicsScene;
    scene->setBackgroundBrush(Qt::white);
    switch (BSTtype) {
        case 0:
            //scene->addText("This is Splay");
            PaintTree(Splaytree.Root, scene);
            break;
        case 1:
            //scene->addText("This is SBT");
            PaintTree(SBTtree.root, scene);
            break;
        case 2:
            //scene->addText("This is AVL");
            PaintTree(AVLtree.Root, scene);
            break;
        case 3:
            //scene->addText("This is Treap");
            PaintTree(Treaptree.Root, scene);
    }
    ui->PaintTree->setScene(scene);
}



void BST::CalcWidth(TreeLink x) {
    if (x == nullptr) return;
    auto data = GenText(x);
    x->RectWidth = (NodeWidth > data->document()->documentLayout()->documentSize().width()) ? NodeWidth : data->document()->documentLayout()->documentSize().width();
    x->lwidth = x->RectWidth / 2.0;
    x->rwidth = x->RectWidth / 2.0;
    delete data;
    if (x->lch == nullptr && x->rch == nullptr)
        return;
    if (x->lch != nullptr) {
        CalcWidth(x->lch);
        if (x->lch->rwidth + NodeGapX / 2.0 <= x->RectWidth / 2.0) {
            x->lwidth += x->lch->RectWidth / 2.0 + x->lch->lwidth;
        }
        else {
            x->lwidth = x->lch->lwidth + x->lch->rwidth + NodeGapX / 2.0;
        }
    }
    if (x->rch != nullptr) {
        CalcWidth(x->rch);
        if (x->rch->lwidth + NodeGapX / 2.0 <= x->RectWidth / 2.0) {
            x->rwidth += x->rch->RectWidth / 2.0 + x->rch->rwidth;
        }
        else {
            x->rwidth = x->rch->lwidth + x->rch->rwidth + NodeGapX / 2.0;
        }
    }
}

void BST::CalcPos(TreeLink t, double x, double y) {
    if (t == nullptr) return;
    t->x = x; t->y = y;
    if (t->lch != nullptr) {
        CalcPos(t->lch, t->x + t->RectWidth / 2.0 - t->lwidth + t->lch->lwidth - t->lch->RectWidth / 2.0, y + NodeGapY + NodeHeight);
    }
    if (t->rch != nullptr) {
        CalcPos(t->rch, t->x + t->RectWidth / 2.0 + t->rwidth - t->rch->rwidth - t->rch->RectWidth / 2.0, y + NodeGapY + NodeHeight);
    }
}

void BST::GenScene(TreeLink x, QGraphicsScene *scene) {
    if (x == nullptr) return;
    // gen text
    auto data = GenText(x);

    // gen rect
    auto *rect = new QGraphicsRectItem(QRectF(x->x,x->y,x->RectWidth,NodeHeight));
    QPen    pen;
    pen.setWidth(2);
    rect->setPen(pen);
    if (x == SelectedNode)
        rect->setBrush(Qt::red);
    else
        rect->setBrush(Qt::darkBlue);

    scene->addItem(rect);
    scene->addItem(data);

    if (x->lch != nullptr) {
        auto *Lline = new QGraphicsLineItem(x->x, x->y + NodeHeight, x->lch->x + x->lch->RectWidth / 2.0, x->lch->y);
        Lline->setPen(pen);
        scene->addItem(Lline);
        GenScene(x->lch, scene);
    }
    if (x->rch != nullptr) {
        auto *Rline = new QGraphicsLineItem(x->x + x->RectWidth, x->y + NodeHeight, x->rch->x + x->rch->RectWidth / 2.0, x->rch->y);
        Rline->setPen(pen);
        scene->addItem(Rline);
        GenScene(x->rch, scene);
    }
}

void BST::PaintTree(TreeLink x, QGraphicsScene *scene) {
    if (x == nullptr) return;
    CalcWidth(x);
    CalcPos(x, 0, 0);
    if (Splited) {
        GenTitle(x, scene);
        GenScene(x->lch, scene);
        GenScene(x->rch, scene);
    }
    else
        GenScene(x, scene);
}

void BST::fnd() {
    int ans;
    if (ui->inputNumber->text() == "") {
        rltLabel->setText("Please enter argument");
        SetPaint();
        return;
    }
    switch (SelectedTree) {
        case 0:
            SBT_SelectedNode = SBTtree.fnd(SBTtree.root->lch, value);

            Splay_SelectedNode = Splaytree.find_rank(Splaytree.Root->lch, value, 0) ? Splaytree.Root->lch : nullptr;

            Treap_SelectedNode = Treaptree.find_rank(Treaptree.Root->lch, value);

            AVL_SelectedNode = AVLtree.find_rank(AVLtree.Root->lch, value, ans);
            break;
        case 1:
            SBT_SelectedNode = SBTtree.fnd(SBTtree.root->rch, value);

            Splay_SelectedNode = Splaytree.find_rank(Splaytree.Root->rch, value, 1) ? Splaytree.Root->rch : nullptr;

            Treap_SelectedNode = Treaptree.find_rank(Treaptree.Root->rch, value);

            AVL_SelectedNode = AVLtree.find_rank(AVLtree.Root->rch, value, ans);
            break;
        case 2:
            SBT_SelectedNode = SBTtree.fnd(SBTtree.root, value);

            Splay_SelectedNode = Splaytree.find_rank(Splaytree.Root, value) ? Splaytree.Root : nullptr;

            Treap_SelectedNode = Treaptree.find_rank(Treaptree.Root, value);

            AVL_SelectedNode = AVLtree.find_rank(AVLtree.Root, value, ans);

            break;
        default:
            SBT_SelectedNode = SBTtree.fnd(SBTtree.root, value);

            Splay_SelectedNode = Splaytree.find_rank(Splaytree.Root, value) ? Splaytree.Root : nullptr;

            Treap_SelectedNode = Treaptree.find_rank(Treaptree.Root, value);

            AVL_SelectedNode = AVLtree.find_rank(AVLtree.Root, value, ans);
    }
    selectNode();
    QString st;
    st.setNum(value);
    if (SelectedNode == nullptr)
        st = st + " not found";
    else
        st = st + " found";
    if (SelectedTree == 0)
        st = st + " in left tree";
    if (SelectedTree == 1)
        st = st + " in right tree";
    rltLabel->setText(st);
    SetPaint();
}

void BST::ins() {
    if (ui->inputNumber->text() == "") {
        rltLabel->setText("Please enter argument");
        SetPaint();
        return;
    }
    switch (SelectedTree) {
        case 0:
            SBT_SelectedNode = SBTtree.ins(SBTtree.root->lch, value);

            Splaytree.insert(Splaytree.Root->lch, value, 0);
            Splay_SelectedNode = Splaytree.Root->lch;

            Treap_SelectedNode = Treaptree.insert(Treaptree.Root->lch, value);

            AVL_SelectedNode = AVLtree.insert(AVLtree.Root->lch, value, 0);
            break;
        case 1:
            SBT_SelectedNode = SBTtree.ins(SBTtree.root->rch, value);

            Splaytree.insert(Splaytree.Root->rch, value, 1);
            Splay_SelectedNode = Splaytree.Root->rch;

            Treap_SelectedNode = Treaptree.insert(Treaptree.Root->rch, value);

            AVL_SelectedNode = AVLtree.insert(AVLtree.Root->rch, value, 1);
            break;
        case 2:
            SBT_SelectedNode = SBTtree.ins(SBTtree.root, value);

            Splaytree.insert(Splaytree.Root, value);
            Splay_SelectedNode = Splaytree.Root;

            Treap_SelectedNode = Treaptree.insert(Treaptree.Root, value);

            AVL_SelectedNode = AVLtree.insert(AVLtree.Root, value);
            break;
        default:
            SBT_SelectedNode = SBTtree.ins(SBTtree.root, value);

            Splaytree.insert(Splaytree.Root, value);
            Splay_SelectedNode = Splaytree.Root;

            Treap_SelectedNode = Treaptree.insert(Treaptree.Root, value);

            AVL_SelectedNode = AVLtree.insert(AVLtree.Root, value);
    }
    selectNode();
    QString st;
    st.setNum(value);
    st = st + " inserted";
    if (SelectedTree == 0)
        st = st + " in left tree";
    if (SelectedTree == 1)
        st = st + " in right tree";
    rltLabel->setText(st);
    SetPaint();
}

void BST::del() {
    int ans;
    if (ui->inputNumber->text() == "") {
        rltLabel->setText("Please enter argument");
        SetPaint();
        return;
    }
    QString st;
    st.setNum(value);
    switch (SelectedTree) {
        case 0:
            SBT_flag = SBTtree.del(SBTtree.root->lch, value);
            SBT_SelectedNode = SBTtree.fnd(SBTtree.root->lch, value);

            Splay_flag = Splaytree.del(Splaytree.Root->lch, value, 0);
            Splay_SelectedNode = Splaytree.find_rank(Splaytree.Root->lch, value, 0) ? Splaytree.Root->lch : nullptr;

            Treap_flag = Treaptree.del(Treaptree.Root->lch, value);
            Treap_SelectedNode = Treaptree.find_rank(Treaptree.Root->lch, value);

            AVL_flag = AVLtree.del(AVLtree.Root->lch, value, 0);
            AVL_SelectedNode = AVLtree.find_rank(AVLtree.Root->lch, value, ans);
            break;
        case 1:
            SBT_flag = SBTtree.del(SBTtree.root->rch, value);
            SBT_SelectedNode = SBTtree.fnd(SBTtree.root->rch, value);

            Splay_flag = Splaytree.del(Splaytree.Root->rch, value, 1);
            Splay_SelectedNode = Splaytree.find_rank(Splaytree.Root->rch, value, 1) ? Splaytree.Root->rch : nullptr;

            Treap_flag = Treaptree.del(Treaptree.Root->rch, value);
            Treap_SelectedNode = Treaptree.find_rank(Treaptree.Root->rch, value);

            AVL_flag = AVLtree.del(AVLtree.Root->rch, value, 1);
            AVL_SelectedNode = AVLtree.find_rank(AVLtree.Root->rch, value, ans);
            break;
        case 2:
            SBT_flag = SBTtree.del(SBTtree.root, value);
            SBT_SelectedNode = SBTtree.fnd(SBTtree.root, value);

            Splay_flag = Splaytree.del(Splaytree.Root, value);
            Splay_SelectedNode = Splaytree.find_rank(Splaytree.Root, value) ? Splaytree.Root : nullptr;

            Treap_flag = Treaptree.del(Treaptree.Root, value);
            Treap_SelectedNode = Treaptree.find_rank(Treaptree.Root, value);

            AVL_flag = AVLtree.del(AVLtree.Root->lch, value);
            AVL_SelectedNode = AVLtree.find_rank(AVLtree.Root, value, ans);
            break;
        default:
            SBT_flag = SBTtree.del(SBTtree.root->lch, value);
            SBT_SelectedNode = SBTtree.fnd(SBTtree.root, value);

            Splay_flag = Splaytree.del(Splaytree.Root, value);
            Splay_SelectedNode = Splaytree.find_rank(Splaytree.Root, value) ? Splaytree.Root : nullptr;

            Treap_flag = Treaptree.del(Treaptree.Root, value);
            Treap_SelectedNode = Treaptree.find_rank(Treaptree.Root, value);

            AVL_flag = AVLtree.del(AVLtree.Root->lch, value);
            AVL_SelectedNode = AVLtree.find_rank(AVLtree.Root, value, ans);
    }
    selectNode();
    selectFlag();
    switch (flag) {
        case 0:
            st = st + " not found";
            break;
        case 1:
            st = st + " deleted and still left";
            break;
        case 2:
            st = st + " deleted";
            break;
        default:
            st = st + "del is wrong";
    }
    if (SelectedTree == 0)
        st = st + " in left tree";
    if (SelectedTree == 1)
        st = st + " in right tree";
    rltLabel->setText(st);
    SetPaint();
}

void BST::reset() {
    ui->isRight->setChecked(false);
    ui->isLeft->setChecked(false);
    ui->isRight->setDisabled(true);
    ui->isLeft->setDisabled(true);
    ui->issplit->setDisabled(false);
    ui->ismerge->setDisabled(true);
    ui->inputNumber->clear();
    SelectedTree = 2;
    SelectedNode = nullptr;
    Splited = 0;

    SBTtree.rel(SBTtree.root);
    SBTtree.root = nullptr;
    Splaytree.rel(Splaytree.Root);
    Splaytree.isSplit = 0;
    Splaytree.Root = nullptr;
    Treaptree.rel(Treaptree.Root);
    Treaptree.Root = nullptr;
    Treaptree.isSplit = 0;
    rltLabel->setText("reset");
    AVLtree.rel(AVLtree.Root);
    AVLtree.Root = nullptr;
    AVLtree.isSplit = 0;
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

void BST::split() {
    if (ui->inputNumber->text() == "") {
        rltLabel->setText("Please enter argument");
        SetPaint();
        return;
    }
    Splited = 1;
    ui->issplit->setDisabled(true);
    ui->ismerge->setDisabled(false);
    ui->isLeft->setDisabled(false);
    ui->isLeft->setChecked(true);
    ui->isRight->setDisabled(false);
    ui->isRight->setChecked(false);
    SBTtree.split(value);
    SBT_SelectedNode = nullptr;
    Splaytree.split(value);
    Splay_SelectedNode = nullptr;
    Treaptree.split(value);
    Treap_SelectedNode = nullptr;
    AVLtree.split(value);
    AVL_SelectedNode = nullptr;
    SelectedTree = 0;
    rltLabel->setText("split complete");
    SelectedNode = nullptr;
    SetPaint();
}

void BST::merge() {
    Splited = 0;
    ui->isLeft->setChecked(false);
    ui->isRight->setChecked(false);
    ui->isLeft->setDisabled(true);
    ui->isRight->setDisabled(true);
    ui->ismerge->setDisabled(true);
    ui->issplit->setDisabled(false);
    SBTtree.merge();
    SBT_SelectedNode = nullptr;
    Splaytree.merge();
    Splay_SelectedNode = nullptr;
    Treaptree.merge();
    Treap_SelectedNode = nullptr;
    AVLtree.merge();
    AVL_SelectedNode = nullptr;
    SelectedTree = 2;
    rltLabel->setText("merge complete");
    SelectedNode = nullptr;
    SetPaint();
}

void BST::GenTitle(TreeLink x, QGraphicsScene *scene) const {
    auto *textl = new QGraphicsTextItem;
    auto *textr = new QGraphicsTextItem;
    auto *stl = new QString;
    auto *str = new QString;
    *str = "右树";
    *stl = "左树";
    textl->setPlainText(*stl);
    textr->setPlainText(*str);
    QFont fontl = textl->font();
    fontl.setPointSize(textHeight);
    textl->setFont(fontl);
    QFont fontr = textr->font();
    fontr.setPointSize(textHeight);
    textr->setFont(fontr);
    textl->setDefaultTextColor(Qt::black);
    textr->setDefaultTextColor(Qt::black);
    if (x->lch != nullptr && x->rch != nullptr) {
        textl->setPos(x->lch->x + x->lch->RectWidth / 2.0 - 25, x->lch->y - 3 * textHeight);
        textr->setPos(x->rch->x + x->rch->RectWidth / 2.0 - 25, x->rch->y - 3 * textHeight);
    }
    else if (x->lch != nullptr && x->rch == nullptr) {
        textl->setPos(x->lch->x + x->lch->RectWidth / 2.0 - 25, x->lch->y - 3 * textHeight);
        textr->setPos(x->lch->x + x->lch->RectWidth / 2.0 - 25 + x->RectWidth / 2.0 + x->lch->rwidth + NodeGapX, x->lch->y - 3 * textHeight);
    }
    else if (x->lch == nullptr && x->rch != nullptr) {
        textl->setPos(x->rch->x + x->rch->RectWidth / 2.0 - 25 - x->rch->lwidth - NodeGapX, x->rch->y - 3 * textHeight);
        textr->setPos(x->rch->x + x->rch->RectWidth / 2.0 - 25, x->rch->y - 3 * textHeight);
    }
    else {
        textl->setPos(0, 0);
        textr->setPos(80, 0);
    }
    scene->addItem(textl);
    scene->addItem(textr);
}

void BST::selectNode() {
    switch (BSTtype) {
        case 0:
            //scene->addText("This is Splay");
            SelectedNode = Splay_SelectedNode;
            break;
        case 1:
            //scene->addText("This is SBT");
            SelectedNode = SBT_SelectedNode;
            break;
        case 2:
            //scene->addText("This is AVL");
            SelectedNode = AVL_SelectedNode;
            break;
        case 3:
            //scene->addText("This is Treap");
            SelectedNode = Treap_SelectedNode;
            break;
    }
}

void BST::selectFlag() {
    switch (BSTtype) {
        case 0:
            //scene->addText("This is Splay");
            flag = Splay_flag;
            break;
        case 1:
            //scene->addText("This is SBT");
            flag = SBT_flag;
            break;
        case 2:
            //scene->addText("This is AVL");
            flag = AVL_flag;
            break;
        case 3:
            //scene->addText("This is Treap");
            flag = Treap_flag;
            break;
    }
}

QGraphicsTextItem* BST::GenText(TreeLink x) const {
    auto *data = new QGraphicsTextItem;
    auto *NodeValue = new QString;
    auto *NodeCnt = new QString;
    auto *NodeSpMsg = new QString;
    NodeValue->setNum(x->value);
    NodeCnt->setNum(x->cnt);
    switch (BSTtype) {
        case 2:
            NodeSpMsg->setNum(x->bf);
            break;
        case 3:
            NodeSpMsg->setNum(x->key);
            break;
        default:
            NodeSpMsg->clear();
    }
    switch (BSTtype) {
        case 2:
            data->setPlainText(*NodeValue + "(" + *NodeCnt + ")" + " bf:" + *NodeSpMsg);
            break;
        case 3:
            data->setPlainText(*NodeValue + "(" + *NodeCnt + ")" + " rnd:" + *NodeSpMsg);
            break;
        default:
            data->setPlainText(*NodeValue + "(" + *NodeCnt + ")" + *NodeSpMsg);
    }
    QFont font = data->font();
    font.setPointSize(textHeight);
    data->setFont(font);
    data->setPos(x->x, x->y);
    data->setDefaultTextColor(Qt::white);
    return data;
}