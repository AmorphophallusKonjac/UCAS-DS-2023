//
// Created by wangm on 2023/6/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <QGraphicsItem>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    iniUI();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::iniUI() {
    // initial width
    width = 40;
    // initial msglabel
    msglabel = new QLabel;
    msglabel->setMinimumSize(msglabel->sizeHint());
    msglabel->setAlignment(Qt::AlignHCenter);
    ui->statusbar->addWidget(msglabel);
    msglabel->setText("Welcome!");

    // initial status bar
    ui->statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    ui->guiboard->setRenderHint(QPainter::Antialiasing, true);
    iniGuiBoard();
}

void MainWindow::iniGuiBoard() {
    auto *scene = new QGraphicsScene;
    scene->setBackgroundBrush(QColor(232,208,170));
    auto  *FrameRect = new QGraphicsRectItem(QRectF(0, 0, 8 * width, 8 * width));
    QPen    pen;
    pen.setWidth(5);
    FrameRect->setPen(pen);
    FrameRect->setBrush(QColor(148,62,1));
    scene->addItem(FrameRect);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            auto *rect = new QGraphicsRectItem(QRectF(i * width, j * width, width, width));
            rect->setPen(QPen(Qt::NoPen));
            if ((i + j) % 2)
                rect->setBrush(QColor(148,62,1));
            else
                rect->setBrush(QColor(232,208,170));
            scene->addItem(rect);
        }
    }
    for (int i = 0; i < 8; ++i) {
        auto *text = new QGraphicsTextItem;
        auto *st = new QString;
        st->setNum(i);
        QFont font = text->font();
        font.setPointSize(15);
        text->setFont(font);
        text->setPos(i * width + 10, -30);
        text->setPlainText(*st);
        text->setDefaultTextColor(Qt::black);
        scene->addItem(text);
    }

    for (int i = 0; i < 8; ++i) {
        auto *text = new QGraphicsTextItem;
        auto *st = new QString;
        st->setNum(i);
        QFont font = text->font();
        font.setPointSize(15);
        text->setFont(font);
        text->setPos(-25, i * width + 3);
        text->setPlainText(*st);
        text->setDefaultTextColor(Qt::black);
        scene->addItem(text);
    }
    ui->guiboard->setScene(scene);
}
