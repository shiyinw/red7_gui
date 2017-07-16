#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <fcntl.h>
#include <cstring>
#include <signal.h>
#include <ctime>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include <QProcess>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QLabel>
#include <fstream>
#include <sstream>
#include "mainwindow.h"
#include "global.h"
#include "congratulation.h"
#include "ai_fight.h"
#include "ui_ai_fight.h"
#define LOG_FILE "log.txt"
#define PLAYER_OUTPUT "output.txt"
#define MAX_PLAYERS 4
#define MAX_ROUNDS 12
#define TIME_LIMIT 2

using namespace std;

ai_fight::ai_fight(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ai_fight)
{
    sleep(1);
    p1=0;
    p0=0;
    ui->setupUi(this);
    naive_module_run();
    ui->lcdNumber->setDigitCount(2);
    ui->lcdNumber->setDecMode();
    ui->lcdNumber_2->setDigitCount(2);
    ui->lcdNumber_2->setDecMode();
    ui->commandLinkButton->setVisible(false);
}

ai_fight::~ai_fight()
{
   MainWindow *m = new MainWindow;
   m->show();
    delete ui;
   t.close();
}


void ai_fight::naive_module_run()
{
    QProcess p(0);
    QDir::setCurrent(global::path+"/AI");
    qDebug()<<"current path: "<<QDir::currentPath()<<endl;
    p.start("rm log.txt");
    p.waitForStarted();
    p.waitForFinished();
    p.start("rm log_p.txt");
    p.waitForStarted();
    p.waitForFinished();

    /*
    p.start("./red7 "+global::player1+" "+global::player2+" -m 0 -g 1");
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());
    QMessageBox testMassage;
    testMassage.setText(strTemp);
    testMassage.exec();
    */


    p.start("./red7_p "+global::player1+" "+global::player2+" -m 0 -g 1");
    p.waitForStarted();
    p.waitForFinished();QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());
    QMessageBox testMassage;
    testMassage.setText(strTemp);
    testMassage.exec();

}

void ai_fight::getfile()
{
    if(!t.is_open())    t.open("log_p.txt");
    ui->pushButton->setEnabled(false);
    getline(t, rule);
    print_rule(rule);

    if(getline(t, p1hand)) print_p1hand(p1hand);

    if(getline(t, p1p)) print_p1p(p1p);

    if(getline(t, p2hand)) print_p2hand(p2hand);

    if(getline(t, p2p)) print_p2p(p2p);

    getline(t, announce);
    if(announce=="1 eliminated"||announce=="0 eliminated")
    {
        if(!t.eof())
        {
        getline(t, buf);
        getline(t, buf);
        getline(t, buf);
        getline(t, buf);
        getline(t, win);
        print_win(win);
        ui->pushButton->setEnabled(true);
        }
        else
        {
            QMessageBox *end= new QMessageBox;
            end->setText("Game Over :-)");
            end->exec();
            ui->pushButton->setEnabled(false);
            ui->commandLinkButton->setVisible(true);
        }
     }
     else if(announce=="0 winning"||announce=="1 winning")
     {
        ui->pushButton->setEnabled(true);
     }
     else qDebug()<<"----------announcement error"<<endl;
    ui->pushButton->setEnabled(true);

}

void ai_fight::print(QLabel *q, int a)
{
    QString number = QString::number(a/10);
    q->setText(number);
    int color = a%10;
    if(color==1)    q->setStyleSheet("QLabel { background-color : red; color : white; }");
    else if(color==2)   q->setStyleSheet("QLabel { background-color : orange; color : white; }");
    else if(color==3)   q->setStyleSheet("QLabel { background-color : yellow; color : white; }");
    else if(color==4)   q->setStyleSheet("QLabel { background-color : green; color : white; }");
    else if(color==5)   q->setStyleSheet("QLabel { background-color : cyan; color : white; }");
    else if(color==6)   q->setStyleSheet("QLabel { background-color : blue; color : white; }");
    else if(color==7)   q->setStyleSheet("QLabel { background-color : purple; color : white; }");
    else if(color==0)
    {
        q->setStyleSheet("QLabel { background-color : black; color : white; }");
        q->setText("");
    }
    else    qDebug()<<"Error: wrong color!!";
}


void ai_fight::print_p1hand(string s)
{
    //qDebug()<<"print_p1hand()"<<endl;
    std::stringstream stream(s);
    int a;
    if(stream>>a)   print((ui->label_8),a);    else print((ui->label_8),0);
    if(stream>>a)   print((ui->label_9),a);    else print((ui->label_9),0);
    if(stream>>a)   print((ui->label_10),a);   else print((ui->label_10),0);
    if(stream>>a)   print((ui->label_11),a);   else print((ui->label_11),0);
    if(stream>>a)   print((ui->label_12),a);   else print((ui->label_12),0);
    if(stream>>a)   print((ui->label_13),a);   else print((ui->label_13),0);
    if(stream>>a)   print((ui->label_14),a);   else print((ui->label_14),0);
    if(stream>>a)   qDebug()<<"Error: number of cards exceed the limit."<<endl;
}

void ai_fight::print_p2hand(string s)
{
    //qDebug()<<"print_p2hand()"<<endl;
    std::stringstream stream(s);
    int a;
    if(stream>>a)   print((ui->label),a);  else print((ui->label),0);
    if(stream>>a)   print((ui->label_2),a);    else print((ui->label_2),0);
    if(stream>>a)   print((ui->label_3),a);    else print((ui->label_3),0);
    if(stream>>a)   print((ui->label_4),a);    else print((ui->label_4),0);
    if(stream>>a)   print((ui->label_5),a);    else print((ui->label_5),0);
    if(stream>>a)   print((ui->label_6),a);    else print((ui->label_6),0);
    if(stream>>a)   print((ui->label_7),a);    else print((ui->label_7),0);
    if(stream>>a)   qDebug()<<"Error: number of cards exceed the limit."<<endl;
}

void ai_fight::print_p1p(string s)
{
   //qDebug()<<"print_p1p()"<<endl;
    std::stringstream stream(s);
    int a;
    if(stream>>a)   print((ui->label_24),a);   else print((ui->label_24),0);
    if(stream>>a)   print((ui->label_25),a);   else print((ui->label_25),0);
    if(stream>>a)   print((ui->label_26),a);   else print((ui->label_26),0);
    if(stream>>a)   print((ui->label_27),a);   else print((ui->label_27),0);
    if(stream>>a)   print((ui->label_28),a);   else print((ui->label_28),0);
    if(stream>>a)   print((ui->label_29),a);   else print((ui->label_29),0);
    if(stream>>a)   print((ui->label_30),a);   else print((ui->label_30),0);
    if(stream>>a)   print((ui->label_31),a);   else print((ui->label_31),0);
    if(stream>>a)   qDebug()<<"Error: number of cards exceed the limit."<<endl;
}

void ai_fight::print_p2p(string s)
{
    //qDebug()<<"print_p2p"<<endl;
    std::stringstream stream(s);
    int a;
    if(stream>>a)   print((ui->label_16),a);   else print((ui->label_16),0);
    if(stream>>a)   print((ui->label_17),a);   else print((ui->label_17),0);
    if(stream>>a)   print((ui->label_18),a);   else print((ui->label_18),0);
    if(stream>>a)   print((ui->label_19),a);   else print((ui->label_19),0);
    if(stream>>a)   print((ui->label_20),a);   else print((ui->label_20),0);
    if(stream>>a)   print((ui->label_21),a);   else print((ui->label_21),0);
    if(stream>>a)   print((ui->label_22),a);   else print((ui->label_22),0);
    if(stream>>a)   print((ui->label_23),a);   else print((ui->label_23),0);
    if(stream>>a)   qDebug()<<"Error: number of cards exceed the limit."<<endl;
}

void ai_fight::print_rule(string s)
{
    std::stringstream stream(s);
    int a;
    if(stream>>a)
    {
        print((ui->label_15),a);
        ui->label_15->setText(QString::number(a/10));
    }
    //qDebug()<<"set rule: "<<a<<endl;
    if(stream>>a)   qDebug()<<"Error: number of cards exceed the limit."<<endl;
}

void ai_fight::print_win(string s)
{
    std::stringstream stream(s);
    //qDebug()<<"print_win()"<<endl;
    int a;
    int winner;
    int score=0;
    stream>>winner;
    while(stream>>a)
    {
        score += a/10;
    }
    if(winner==0)
    {
        p0 += score;
        ui->lcdNumber_2->display(p0);
    }
    else if(winner==1)
    {
        p1 += score;
        ui->lcdNumber->display(p1);
    }
    else
        qDebug()<<"Error: winner error!"<<endl;

    QMessageBox m;
    m.setText("Winner: "+QString::number(winner+1));
    m.exec();
}

void ai_fight::on_pushButton_clicked()
{
    getfile();
}

void ai_fight::on_commandLinkButton_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}
