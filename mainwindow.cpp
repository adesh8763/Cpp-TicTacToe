#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), xTurn(true) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    gridLayout = new QGridLayout(centralWidget);
    centralWidget->setLayout(gridLayout);

    initUI();
    setWindowTitle("Tic Tac Toe");
    resize(300, 300);
}

MainWindow::~MainWindow(){
    
}

void MainWindow::initUI() {
    buttons.resize(3);

    for (int i = 0; i < 3; ++i){
        buttons[i].resize(3);

        for (int j = 0; j < 3; ++j){
            QPushButton* btn = new QPushButton("");
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            // Auto-scaling font
            btn->setStyleSheet("font-size: 32px; font-weight: bold;");

            buttons[i][j] = btn;
            gridLayout->addWidget(btn, i, j);

            connect(btn, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
        }
    }
}

void MainWindow::handleButtonClick() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(button->text() != "")
        return;

    button->setText(xTurn ? "X" : "O");
    xTurn = !xTurn;

    checkWinner();
}

void MainWindow::checkWinner(){
    for(int i = 0; i < 3; ++i){
        if(buttons[i][0]->text() != "" &&
           buttons[i][0]->text() == buttons[i][1]->text() &&
           buttons[i][1]->text() == buttons[i][2]->text()){
            QMessageBox::information(this, "Game Over", buttons[i][0]->text() + " wins!");
            resetBoard();
            return;
        }

        if(buttons[0][i]->text() != "" &&
           buttons[0][i]->text() == buttons[1][i]->text() &&
           buttons[1][i]->text() == buttons[2][i]->text()){
            QMessageBox::information(this, "Game Over", buttons[0][i]->text() + " wins!");
            resetBoard();
            return;
        }
    }

    // Diagonals
    if(buttons[0][0]->text() != "" &&
       buttons[0][0]->text() == buttons[1][1]->text() &&
       buttons[1][1]->text() == buttons[2][2]->text())
    {
        QMessageBox::information(this, "Game Over", buttons[0][0]->text() + " wins!");
        resetBoard();
        return;
    }

    if(buttons[0][2]->text() != "" &&
       buttons[0][2]->text() == buttons[1][1]->text() &&
       buttons[1][1]->text() == buttons[2][0]->text())
    {
        QMessageBox::information(this, "Game Over", buttons[0][2]->text() + " wins!");
        resetBoard();
        return;
    }

    // Check draw
    bool draw = true;
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            if(buttons[i][j]->text() == "")
                draw = false;

    if(draw)
    {
        QMessageBox::information(this, "Game Over", "It's a draw!");
        resetBoard();
    }
}

void MainWindow::resetBoard() {
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            buttons[i][j]->setText("");
    xTurn = true;
}
