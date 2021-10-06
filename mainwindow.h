#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setState(QString setting);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int board[9];
    QString state;
    int playerWins;
    int ComputerWins;
    int Tie;
    int _difficulty;

    bool existMove();
    int minimax(int depth,int alpha,int beta,bool isMax);
    int bestMove();
    int evaluate();

    void computerEasy();
    void computerMedium();
    void computerHard();

private slots:
    void button_pressed();
    void restart();
    void checkWin();
    void restartScore();
    void changeDifficulty();
};
#endif // MAINWINDOW_H
