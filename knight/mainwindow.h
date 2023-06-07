//
// Created by wangm on 2023/6/7.
//

#ifndef KNIGHT_MAINWINDOW_H
#define KNIGHT_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};


#endif //KNIGHT_MAINWINDOW_H
