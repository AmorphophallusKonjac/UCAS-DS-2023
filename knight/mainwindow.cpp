//
// Created by wangm on 2023/6/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <iostream>
#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "QRegularExpressionValidator"
#include "QRegularExpression"
#include "QDebug"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    iniUI();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::iniUI() {
    // initial CurrentAns
    CurrentAns = 0;
    ui->SucAns->setDisabled(true);
    ui->PreAns->setDisabled(true);
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

    // set input limit
    ui->inputX->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-7]")));
    ui->inputY->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-7]")));

    // connect button
    connect(ui->showResult, SIGNAL(clicked(bool)), this, SLOT(PrintResult()));
    connect(ui->isreset, SIGNAL(clicked(bool)), this, SLOT(Reset()));
    connect(ui->inputX, SIGNAL(textChanged(QString)), this, SLOT(UpdateX()));
    connect(ui->inputY, SIGNAL(textChanged(QString)), this, SLOT(UpdateY()));
    connect(ui->PreAns, SIGNAL(clicked(bool)), this, SLOT(ChPreAns()));
    connect(ui->SucAns, SIGNAL(clicked(bool)), this, SLOT(ChSucAns()));
    connect(ui->CurrentAns, SIGNAL(returnPressed()), this, SLOT(ChSelAns()));
    connect(ui->ShowProcess, SIGNAL(clicked(bool)), this, SLOT(PrintProcess()));
    connect(ui->SucStep, SIGNAL(clicked(bool)), this, SLOT(ChSucStep()));
    connect(ui->PreStep, SIGNAL(clicked(bool)), this, SLOT(CHPreStep()));

    // set CurrentAns input int
    ui->CurrentAns->setValidator(new QIntValidator(ui->CurrentAns));

    // set CurrentAns disable
    ui->CurrentAns->setDisabled(true);

    // set SucStep and PreStep disable
    ui->SucStep->setDisabled(true);
    ui->PreStep->setDisabled(true);
}

void MainWindow::iniGuiBoard() {
    auto *scene = new QGraphicsScene;
    PrintGuiBoard(scene);
    ui->guiboard->setScene(scene);
}

void MainWindow::PrintResult() {
    if (ui->inputX->text() == "" || ui->inputY->text() == "") {
        ui->msgdisplay->append("请完整输入参数\n");
        return;
    }
    ui->ShowProcess->setDisabled(true);
    ui->showResult->setDisabled(true);
    auto *scene = new QGraphicsScene;
    PrintGuiBoard(scene);
    board.MAXANS = 3000;
    CntAns = board.calc();
    ui->CntAns->setNum(CntAns);
    ui->CurrentAns->setText("1");
    auto *num = new QString;
    num->setNum(CntAns);
    ui->msgdisplay->append("得到" + *num + "个解\n");
    ShowResultMsg();
    if (CntAns)
        ui->CurrentAns->setDisabled(false);
    if (CntAns > 1)
        ui->SucAns->setDisabled(false);
    PrintGuiResult(scene);
    ui->guiboard->setScene(scene);
}

void MainWindow::PrintGuiBoard(QGraphicsScene *scene) const {
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
}

void MainWindow::PrintGuiResult(QGraphicsScene *scene) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            auto *data = new QGraphicsTextItem;
            auto *st = new QString;
            st->setNum(board.result[CurrentAns][i][j]);
            QFont font = data->font();
            font.setPointSize(15);
            data->setFont(font);
            data->setPos(i * width, j * width);
            data->setPlainText(*st);
            data->setDefaultTextColor(Qt::black);
            scene->addItem(data);
        }
}

void MainWindow::Reset() {
    board.reset();
    iniGuiBoard();
    CurrentAns = 0;
    CntAns = 0;
    ui->CurrentAns->setText("");
    ui->CntAns->setNum(0);
    ui->SucAns->setDisabled(true);
    ui->PreAns->setDisabled(true);
    ui->SucStep->setDisabled(true);
    ui->PreStep->setDisabled(true);
    ui->msgdisplay->clear();
    ui->CurrentAns->setDisabled(true);
    List.clear();
    ui->showResult->setDisabled(false);
    ui->ShowProcess->setDisabled(false);
    for (auto & i : ProcessResult)
        for (int & j : i)
            j = 0;
    ui->inputY->clear();
    ui->inputX->clear();
}

void MainWindow::UpdateX() {
    board.x0= ui->inputX->text().toInt();
}

void MainWindow::UpdateY() {
    board.y0 = ui->inputY->text().toInt();
}

void MainWindow::ChSucAns() {
    ++CurrentAns;
    ShowResultMsg();
    DisplayBoard();
    if (CurrentAns == CntAns - 1) {
        ui->SucAns->setDisabled(true);
        return;
    }
    ui->SucAns->setDisabled(false);
    ui->PreAns->setDisabled(false);
}

void MainWindow::ChPreAns() {
    --CurrentAns;
    ShowResultMsg();
    DisplayBoard();
    if (!CurrentAns) {
        ui->PreAns->setDisabled(true);
        return;
    }
    ui->SucAns->setDisabled(false);
    ui->PreAns->setDisabled(false);
}

void MainWindow::ShowResultMsg() {
    auto *st1 = new QString, *st2 = new QString;
    st1->setNum(CurrentAns + 1);
    st2->setNum(CntAns);
    ui->msgdisplay->append("展示第" + *st1 + "/" + *st2 +"个解\n");
    ui->CurrentAns->setText(*st1);
}

void MainWindow::DisplayBoard() {
    auto *scene = new QGraphicsScene;
    PrintGuiBoard(scene);
    PrintGuiResult(scene);
    ui->guiboard->setScene(scene);
}

void MainWindow::ChSelAns() {
    int num = ui->CurrentAns->text().toInt();
    if (num > CntAns || num < 1) {
        ui->msgdisplay->append("请输入正确的解序号");
        return;
    }
    CurrentAns = num - 1;
    ShowResultMsg();
    DisplayBoard();
    ui->SucAns->setDisabled(false);
    ui->PreAns->setDisabled(false);
    if (CurrentAns == CntAns - 1) {
        ui->SucAns->setDisabled(true);
        return;
    }
    if (!CurrentAns) {
        ui->PreAns->setDisabled(true);
        return;
    }
}

void MainWindow::PrintProcess() {
    if (ui->inputX->text() == "" || ui->inputY->text() == "") {
        ui->msgdisplay->append("请完整输入参数\n");
        return;
    }
    ui->showResult->setDisabled(true);
    ui->ShowProcess->setDisabled(true);
    for (auto & i : ProcessResult)
        for (int & j : i)
            j = 0;
    board.MAXANS = 2;
    CntAns = board.calc();
    BuildList(board.root, 1);
    CurrentListIndex = 0;
    ui->SucStep->setDisabled(false);
    ui->PreStep->setDisabled(true);
    CurrentListCnt = 1;
    ProcessResult[List[CurrentListIndex].x][List[CurrentListIndex].y] = List[CurrentListIndex].cnt;
    DisplayProcess();
}

void MainWindow::BuildList(TreeLink x, int cnt) {
    List.push_back({x->x, x->y, cnt, 1});
    for (EdgeLink i = x->h; i != nullptr; i = i->ne) {
        TreeLink y = i->ot;
        BuildList(y, cnt + 1);
    }
    List.push_back({x->x, x->y, cnt, 0});
}

void MainWindow::DisplayProcess() {
    auto *scene = new QGraphicsScene;
    PrintGuiBoard(scene);
    PrintGuiProcess(scene);
    ui->guiboard->setScene(scene);
}

void MainWindow::PrintGuiProcess(QGraphicsScene *scene) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            if (ProcessResult[i][j] < CurrentListCnt && ProcessResult[i][j]) {
                auto *data = new QGraphicsTextItem;
                auto *st = new QString;
                st->setNum(board.result[CurrentAns][i][j]);
                QFont font = data->font();
                font.setPointSize(15);
                data->setFont(font);
                data->setPos(i * width, j * width);
                data->setPlainText(*st);
                data->setDefaultTextColor(Qt::black);
                scene->addItem(data);
            }
            if (ProcessResult[i][j] == CurrentListCnt) {
                auto *knight = new QGraphicsPixmapItem;
                knight->setPixmap(QPixmap("./sources/horse.png"));
                knight->setOffset(5, 0);
                knight->setPos(i * width, j * width);
                scene->addItem(knight);
            }
        }
}

void MainWindow::ChSucStep() {
    ++CurrentListIndex;
    UpdateProcessButtonStatus();
    if (List[CurrentListIndex].in) {
        CurrentListCnt = List[CurrentListIndex].cnt;
        ProcessResult[List[CurrentListIndex].x][List[CurrentListIndex].y] = CurrentListCnt;
    }
    else {
        CurrentListCnt = List[CurrentListIndex].cnt - 1;
        ProcessResult[List[CurrentListIndex].x][List[CurrentListIndex].y] = 0;
    }
    DisplayProcess();
    //DebugDisplay();
}

void MainWindow::UpdateProcessButtonStatus() {
    if (CurrentListIndex + 2 == List.size())
        ui->SucStep->setDisabled(true);
    else
        ui->SucStep->setDisabled(false);
    if (!CurrentListIndex)
        ui->PreStep->setDisabled(true);
    else
        ui->PreStep->setDisabled(false);
}

void MainWindow::CHPreStep() {
    if (List[CurrentListIndex].in) {
        ProcessResult[List[CurrentListIndex].x][List[CurrentListIndex].y] = 0;
    }
    else {
        ProcessResult[List[CurrentListIndex].x][List[CurrentListIndex].y] = List[CurrentListIndex].cnt;
    }
    --CurrentListIndex;
    UpdateProcessButtonStatus();
    if (List[CurrentListIndex].in)
        CurrentListCnt = List[CurrentListIndex].cnt;
    else
        CurrentListCnt = List[CurrentListIndex].cnt - 1;
    DisplayProcess();
    //DebugDisplay();
}

void MainWindow::DebugDisplay() {
    qDebug("CurrentListIndex: %d\n", CurrentListIndex);
    qDebug("{List[CurrentListIndex].x, List[CurrentListIndex].y, List[CurrentListIndex].cnt, List[CurrentListIndex].in}: {%d, %d, %d, %d}\n", List[CurrentListIndex].x, List[CurrentListIndex].y, List[CurrentListIndex].cnt, List[CurrentListIndex].in);
    qDebug("CurrentListCnt: %d\n", CurrentListCnt);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j)
            std::cout << ProcessResult[i][j];
        qDebug("\n");
    }

}
