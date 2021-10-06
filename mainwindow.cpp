#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    for(int i=0;i<9;++i)
    {
        board[i]=0;
    }


    QPushButton* restart_button=MainWindow::findChild<QPushButton*>("restart");
    connect(restart_button,SIGNAL(released()),this,SLOT(restart()));

    QPushButton* restart_score=MainWindow::findChild<QPushButton*>("rScore");
    connect(restart_score,SIGNAL(released()),this,SLOT(restartScore()));

    QPushButton* difficulty=MainWindow::findChild<QPushButton*>("difficulty");
    connect(difficulty,SIGNAL(released()),this,SLOT(changeDifficulty()));

    QPushButton* boardButtons[9];
    for(int i=0;i<9;++i)
    {
        QString butName="button"+ QString::number(i);
        boardButtons[i]=MainWindow::findChild<QPushButton*>(butName);
        connect(boardButtons[i],SIGNAL(released()),this,SLOT(button_pressed()));
        //connect(boardButtons[i],SIGNAL(released()),this,SLOT(checkWin()));



    }

    state="in play";
    playerWins=0;
    ComputerWins=0;
    Tie=0;
    _difficulty=1;

}

bool MainWindow::existMove()
{
    for(int i=0;i<9;++i)
{
    if(board[i]==0)
    {
        return true;
    }

}
return false;

}

int MainWindow::evaluate()
{
    if(board[0]==board[1] && board[0]==board[2] && board[0]!=0)
    {
        if(board[0]==1)
        {
            return -10;

        }
        else if(board[0]==2)
        {
            return 10;

        }
    }
    if(board[3]==board[4] && board[3]==board[5] && board[3]!=0)
    {
        if(board[3]==1)
        {
                return -10;

        }
        else if(board[3]==2)
        {
                return 10;

        }
    }
    if(board[6]==board[7] && board[6]==board[8] && board[6]!=0)
    {
        if(board[6]==1)
        {
            return -10;
        }
        else if(board[6]==2)
        {
            return 10;


        }
    }
    if(board[0]==board[3] && board[0]==board[6] && board[0]!=0)
    {
        if(board[0]==1)
        {
            return -10;


        }
        else if(board[0]==2)
        {
            return 10;


        }
    }
    if(board[1]==board[4] && board[1]==board[7] && board[1]!=0)
    {
        if(board[1]==1)
        {
            return -10;

        }
        else if(board[1]==2)
        {
            return 10;


        }
    }
    if(board[2]==board[5] && board[2]==board[8] && board[2]!=0)
    {
        if(board[2]==1)
        {
            return -10;


        }
        else if(board[2]==2)
        {
            return 10;


        }
    }
    if(board[0]==board[4] && board[0]==board[8] && board[0]!=0)
    {
        if(board[0]==1)
        {
            return -10;
        }
        else if(board[0]==2)
        {
            return 10;

        }
    }
    if(board[2]==board[4] && board[2]==board[6] && board[2]!=0)
    {
        if(board[2]==1)
        {
            return -10;

        }
        else if(board[2]==2)
        {return 10;

        }
    }
return 0;

}

int MainWindow::minimax(int depth,int alpha,int beta, bool isMax)
{
    int score=evaluate();
    if(score==10)
    {
        return score-depth;
    }
    if(score==-10)
    {
        return score+depth;
    }
    if(existMove()==false)
    {
        return 0;
    }

    if(isMax==true)
    {
        int best=-1000;
        for(int i=0;i<9;++i)
        {
            if(board[i]==0)
            {
                board[i]=2;
                int eval=minimax(depth+1,alpha,beta,false);
                best=std::max(best,eval);
                alpha=std::max(alpha,eval);
                board[i]=0;
                if(beta<=alpha)
                {
                    break;
                }
            }
        }
        return best;
    }
    else
    {
        int best=1000;
        for(int i=0;i<9;++i)
        {
            if(board[i]==0)
            {
                board[i]=1;
                int eval=minimax(depth+1,alpha,beta,true);
                best=std::min(best,eval);
                beta=std::min(beta,eval);
                board[i]=0;
                if(beta<=alpha)
                {
                    break;
                }
            }
        }
        return best;

    }

}

int MainWindow::bestMove()
{
    int bestValue=-1000;
    int move=-1;

    for(int i=0;i<9;++i)
    {
        if(board[i]==0)
        {
            board[i]=2;
            int moveValue=minimax(0,-1000,1000,false);
            board[i]=0;
            if(moveValue>bestValue)
            {
                move=i;
                bestValue=moveValue;
            }
        }
    }
    return move;
}

void MainWindow::setState(QString setting)
{
    state=setting;
}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::button_pressed()
{

    QPushButton*button=(QPushButton*)sender();
    if(button->text()=="" && state=="in play")
    {


             QString name=button->objectName();
             QString pos=name.back();
             board[pos.toInt()]=1;
             button->setText("X");
             button->setStyleSheet("background-color:orange;border:1px solid orange ;color:blue;font:43pt;");
             checkWin();
           if(existMove())
           {
             if(_difficulty==1)
             {
                 computerEasy();
             }
             else if(_difficulty==2)
             {
                 computerMedium();
             }
             else
             {
                 computerHard();
             }
           }

    }









}

void unsetBold(MainWindow* curr)
{
    for(int i=0;i<9;++i)
    {
        QPushButton* but;
        QString butName="button"+ QString::number(i);
        but=curr->MainWindow::findChild<QPushButton*>(butName);

        QFont font;
        font.setBold(false);
        but->setFont(font);

    }
}

void MainWindow::restart()
{
    for(int i=0;i<9;++i)
    {
        QPushButton* but;
        QString butName="button"+ QString::number(i);
        but=MainWindow::findChild<QPushButton*>(butName);
        but->setText("");
        board[i]=0;

    }



    unsetBold(this);
    state="in play";
}

void setBold(QString num1,QString num2,QString num3, MainWindow*  current)
{
    QString style;

    QPushButton* button;

    button=current->MainWindow::findChild<QPushButton*>("button"+num1);
    style=button->styleSheet();
   button->setStyleSheet(style+"font-weight:bold");
    button=current->MainWindow::findChild<QPushButton*>("button"+num2);
    style=button->styleSheet();
 button->setStyleSheet(style+"font-weight:bold");
    button=current->MainWindow::findChild<QPushButton*>("button"+num3);
    style=button->styleSheet();
   button->setStyleSheet(style+"font-weight:bold");

   current->setState("finish");

}


void incrementWins(int& increment,MainWindow* curr,QString name)
{
    increment=increment+1;
    QLabel* player=curr->findChild<QLabel*>(name);
    player->setText(QString::number(increment));
}


void MainWindow::checkWin()
{

if(state=="in play")
{
    if(board[0]==board[1] && board[0]==board[2] && board[0]!=0)
    {
        if(board[0]==1)
        {

            setBold("0","2","1",this);
            incrementWins(playerWins,this,"label_5");
            return;
        }
        else
        {

            setBold("0","2","1",this);
            incrementWins(ComputerWins,this,"label_6");
            return;
        }
    }
    if(board[3]==board[4] && board[3]==board[5] && board[3]!=0)
    {
        if(board[3]==1)
        {

            setBold("3","4","5",this);
            incrementWins(playerWins,this,"label_5");
            return;
        }
        else
        {

            setBold("3","4","5",this);
            incrementWins(ComputerWins,this,"label_6");
            return;
        }
    }
    if(board[6]==board[7] && board[6]==board[8] && board[6]!=0)
    {
        if(board[6]==1)
        {

            setBold("6","7","8",this);
            incrementWins(playerWins,this,"label_5");
            return;
        }
        else
        {

            setBold("6","7","8",this);
            incrementWins(ComputerWins,this,"label_6");
            return;
        }
    }
    if(board[0]==board[3] && board[0]==board[6] && board[0]!=0)
    {
        if(board[0]==1)
        {

            setBold("0","3","6",this);
            incrementWins(playerWins,this,"label_5");
            return;
        }
        else
        {

            setBold("0","3","6",this);
            incrementWins(ComputerWins,this,"label_6");
            return;
        }
    }
    if(board[1]==board[4] && board[1]==board[7] && board[1]!=0)
    {
        if(board[1]==1)
        {

            setBold("1","4","7",this);
            incrementWins(playerWins,this,"label_5");
            return;
        }
        else
        {

            setBold("1","4","7",this);
            incrementWins(ComputerWins,this,"label_6");
            return;
        }
    }
    if(board[2]==board[5] && board[2]==board[8] && board[2]!=0)
    {
        if(board[2]==1)
        {

            setBold("2","5","8",this);
            incrementWins(playerWins,this,"label_5");
            return;
        }
        else
        {

            setBold("2","5","8",this);
            incrementWins(ComputerWins,this,"label_6");
            return;
        }
    }
    if(board[0]==board[4] && board[0]==board[8] && board[0]!=0)
    {
        if(board[0]==1)
        {

             setBold("0","4","8",this);
             incrementWins(playerWins,this,"label_5");
            return;
        }
        else
        {

            setBold("0","4","8",this);
            incrementWins(ComputerWins,this,"label_6");
            return;
        }
    }
    if(board[2]==board[4] && board[2]==board[6] && board[2]!=0)
    {
        if(board[2]==1)
        {

            setBold("2","4","6",this);
            incrementWins(playerWins,this,"label_5");
            return;
        }
        else
        {

            setBold("2","4","6",this);
            incrementWins(ComputerWins,this,"label_6");
            return;
        }
    }
    bool ok=true;
    for(int i=0;i<9;++i)
    {
        if(board[i]==0)
        {
            ok=false;
        }

    }
    if(ok==true)
    {
        incrementWins(Tie,this,"label_4");
        state="finish";
        return;
    }
}
}

void MainWindow::computerEasy()
{
  if(state=="in play")
  {


    bool taken=true;
    bool boardFull=true;

    for(int i=0;i<9;++i)
    {
        if(board[i]==0)
        {
            boardFull=false;
        }
    }
    while(taken==true && boardFull!=true)
    {


        int i=rand()%9;
        if(board[i]==0)
        {
            board[i]=2;
            QString butName="button"+ QString::number(i);
            QPushButton* button=MainWindow::findChild<QPushButton*>(butName);

            button->setText("O");
            button->setStyleSheet("background-color:orange; border:1px solid orange;color:red; font:43pt;");
            taken=false;
            boardFull=true;

        }
        for(int i=0;i<9;++i)
        {
            if(board[i]==0)
            {
                boardFull=false;
            }
        }
    }
   checkWin();
  }

}

void MainWindow::computerHard()
{
    if(state=="in play")
    {
        int move=bestMove();
        board[move]=2;
        QString butName="button"+ QString::number(move);
        QPushButton* button=MainWindow::findChild<QPushButton*>(butName);

        button->setText("O");
        button->setStyleSheet("background-color:orange; border:1px solid orange;color:red; font:43pt;");
        checkWin();
    }
}


void MainWindow::restartScore()
{
    QLabel* label=MainWindow::findChild<QLabel*>("label_4");
    label->setText("0");
    Tie=0;

    label=MainWindow::findChild<QLabel*>("label_5");
    label->setText("0");
    playerWins=0;

    label=MainWindow::findChild<QLabel*>("label_6");
    label->setText("0");
    ComputerWins=0;
}

void MainWindow::computerMedium()
{
    if(state=="in play")
    {
       int change=rand()%2;
       if(change==0)
       {
           computerHard();
       }
       else
       {
           computerEasy();
       }
    }
}

void MainWindow::changeDifficulty()
{
    _difficulty++;

    QPushButton* button=MainWindow::findChild<QPushButton*>("difficulty");


    if(_difficulty==1)
    {
        button->setText("DIFFICULTY:EASY");

    }
    else if(_difficulty==2)
    {
        button->setText("DIFFICULTY:MEDIUM");
    }
    else if(_difficulty==3)
    {
        button->setText("DIFFICULTY:HARD");
    }
    else
    {
        _difficulty=1;
        button->setText("DIFFICULTY:EASY");
    }

}
