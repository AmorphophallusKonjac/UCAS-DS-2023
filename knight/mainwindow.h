//
// Created by wangm on 2023/6/7.
//

#ifndef KNIGHT_MAINWINDOW_H
#define KNIGHT_MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "board.h"
#include "chess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;
    //board board;
    chess board;
public slots:
    void PrintResult();
    void PrintProcess();
    void Reset();
    void UpdateX();
    void UpdateY();
private:
    Ui::MainWindow *ui;
    QLabel *msglabel;
    void iniUI();                   // initialize UI
    void iniGuiBoard();             // initialize GuiBoard
    int width;
    void PrintGuiBoard(QGraphicsScene *scene) const;
    void PrintGuiResult(QGraphicsScene *scene);
};


#endif //KNIGHT_MAINWINDOW_H
