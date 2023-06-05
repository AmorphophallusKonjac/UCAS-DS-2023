#include <QApplication>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include "SBT.h"
#include "bstselect.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BST w;
    w.show();
    return QApplication::exec();
}

