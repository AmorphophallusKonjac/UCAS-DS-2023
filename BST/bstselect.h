//
// Created by wangm on 2023/6/5.
//

#ifndef BST_BSTSELECT_H
#define BST_BSTSELECT_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class BST; }
QT_END_NAMESPACE

class BST : public QDialog {
Q_OBJECT

public:
    explicit BST(QWidget *parent = nullptr);

    ~BST() override;

private:
    Ui::BST *ui;
};


#endif //BST_BSTSELECT_H
