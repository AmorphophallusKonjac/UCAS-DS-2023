#include <QApplication>
#include "SBT.h"
#include "bst.h"

SBT SBT_Tree;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BST w;
    w.show();
    return QApplication::exec();
}

