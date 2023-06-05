//
// Created by wangm on 2023/6/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BSTselect.h" resolved

#include "bstselect.h"
#include "ui_BSTselect.h"


BST::BST(QWidget *parent) :
        QDialog(parent), ui(new Ui::BST) {
    ui->setupUi(this);
}

BST::~BST() {
    delete ui;
}
