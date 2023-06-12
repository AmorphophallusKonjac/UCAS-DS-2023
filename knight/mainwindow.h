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

typedef struct step {
    int x, y, cnt, in;
} step;

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
    void PrintProcess();
    void PrintResult();
    void Reset();
    void UpdateX();
    void UpdateY();
    void ChSucAns();
    void ChPreAns();
    void ChSelAns();
    void ChSucStep();
    void CHPreStep();
private:
    Ui::MainWindow *ui;
    QLabel *msglabel;
    void iniUI();                   // initialize UI
    void iniGuiBoard();             // initialize GuiBoard
    int width;
    void PrintGuiBoard(QGraphicsScene *scene) const;
    void PrintGuiResult(QGraphicsScene *scene);
    int CurrentAns;
    int CurrentListCnt;
    int CntAns;
    void ShowResultMsg();
    void DisplayBoard();
    int CurrentListIndex;
    int ProcessResult[8][8]{0};
    void BuildList(TreeLink x, int cnt);
    std::vector<step> List;
    void DisplayProcess();
    void PrintGuiProcess(QGraphicsScene *scene);
    void UpdateProcessButtonStatus();
    void DebugDisplay();
};


#endif //KNIGHT_MAINWINDOW_H
