#include <QApplication>
#include "bst.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BST w;
    w.show();
    return QApplication::exec();
}

