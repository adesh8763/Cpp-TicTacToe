#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QVector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVector<QVector<QPushButton*>> buttons;
    bool xTurn;

    void initUI();
    void checkWinner();
    void resetBoard();

private slots:
    void handleButtonClick();
};

#endif 
