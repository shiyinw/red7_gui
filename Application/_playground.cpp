#include "_playground.h"
#include "ui__playground.h"
#include <QPalette>
#include <QDebug>
#include <random>
#include <ctime>
#include <stdlib.h>
#include <QtGlobal>
#include <QMessageBox>
#include "mainwindow.h"
#include <sstream>
#include <list>
#include "Common.h"
#include <vector>
#include "rules.h"

_playground::_playground(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::_playground)
{
    ui->setupUi(this);
    //QTime time = QTime::currentTime();
    srand((unsigned)time(0));
    score1=0;
    score2=0;
    p2 = new Trivial;
    new_game();
    ui->pushButton_3->setEnabled(false);
    ui->lcdNumber->setDigitCount(2);
    ui->lcdNumber->setDecMode();
    ui->lcdNumber_2->setDigitCount(2);
    ui->lcdNumber_2->setDecMode();
    rule=7;
}

_playground::~_playground()
{
    MainWindow *w = new MainWindow;
    w->show();
    delete ui;
}


void _playground::ai_play()
{
    qDebug()<<"ai_play()"<<endl;
    cout<<"2:"<<endl;
    p2->see(hand2, palette2, palette1, rule);
    int s = p2->play();
    cout<<"AI Choose Strategy:"<<s<<endl;

    int change_rule = s/100;
    int add_palette = s%100;

                    if(change_rule%10!=0)
                    {
                        rule = change_rule%10;
                        for(list<int>::iterator i=hand2.begin(); i!=hand2.end(); i++)
                            if(change_rule==*i)
                            {
                                hand2.erase(i);
                                break;
                            }
                    }
                    if(add_palette!=0)
                    {
                        palette2.push_back(add_palette);
                        for(list<int>::iterator i=hand2.begin(); i!=hand2.end(); i++)
                            if(add_palette==*i)
                            {
                                hand2.erase(i);
                                break;
                            }
                    }
        //print(hand1,palette1,hand2,palette2,rule);
        paint_hand(hand1);
        paint_palette(palette1);
        paint_ai(palette2);
        paint(ui->label_9,rule);
        judge();
}


void _playground::judge()
{
    qDebug()<<"Judge the final of : "<<current_player<<"(rule"<<rule<<")"<<endl;
    if(current_player==1&&rule_compare(palette1, palette2,rule)==0)
    {
        p_alive=false;
        palette1.clear();
        hand1.clear();
        score2+= score(palette2, rule);
        ui->lcdNumber->display(score2);
        qDebug()<<"Score 1 = "<<score1<<"  Score 2 = "<<score2<<endl<<endl;
        if(score2>WIN_SCORE)
        {
            QMessageBox m;
            m.setText("Oops! Game Over.");
            m.exec();
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
        }
        else new_game();
    }
    else if(current_player==2&&rule_compare(palette2, palette1,rule)==0)
    {
        ai_alive=false;
        palette2.clear();
        hand2.clear();
        score1+= score(palette1, rule);
        ui->lcdNumber_2->display(score1);
        qDebug()<<"Score 1 = "<<score1<<"  Score 2 = "<<score2<<endl<<endl;
        if(score1>WIN_SCORE)
        {
            QMessageBox m;
            m.setText("Congratulations!! You win AI :D");
            m.exec();
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
        }
        else
        {
            new_game();
        }
    }
    else if(current_player==1&&rule_compare(palette1,palette2,rule)==1)
    {
        current_player=2;
        ai_play();
    }
    else if(current_player==2&&rule_compare(palette2,palette1,rule)==1)
    {
        current_player=1;
    }
}

void _playground::new_game()
{
    qDebug()<<"new_game()"<<endl;
    p2 = new Trivial;
    p_alive=1;
    ai_alive=1;
    hand1.clear();
    hand2.clear();
    palette1.clear();
    palette2.clear();

    vector<int> v;
    for(int i=1;i<8;i++)
        for(int j=1;j<8;j++)
            v.push_back(i*10+j);

    for(int i=0; i<7;i++)
    {
        card1 = rand()%v.size();
        hand1.push_back(v[card1]);
        v.erase(v.begin()+card1);
        card2 = rand()%v.size();
        hand2.push_back(v[card2]);
        v.erase(v.begin()+card2);
    }

    card1 = rand()%v.size();
    palette1.push_back(v[card1]);
    v.erase(v.begin()+card1);
    card2 = rand()%v.size();
    palette2.push_back(v[card2]);
    v.erase(v.begin()+card2);

    paint_palette(palette1);
    paint_hand(hand1);
    paint_ai(palette2);
    int rule=7;
    paint(ui->label_9,rule);

    if(rule_compare(palette1, palette2, 7)==1)
    {
        current_player=2;
        ai_play();
    }
    else if(rule_compare(palette1, palette2, 7)==0)
    {
        current_player=1;
        ui->label->setText("");
        ui->label_8->setText("");
    }
    else cout<<"Error for compare"<<endl;
    //qDebug()<<"New: "<<endl;
    //print(hand1,palette1,hand2,palette2,rule);
}

int _playground::score(list<int> a, int r)//结局的时候算分用
{
    list<int> top;
    top.clear();
    switch(r)
    {
        case 7: top=red(a); break;
        case 6: top=orange(a); break;
        case 5: top=yellow(a); break;
        case 4: top=green(a); break;
        case 3: top=blue(a); break;
        case 2: top=indigo(a); break;
        case 1: top=violet(a); break;
    }
    int score=0;
    for(list<int>::iterator i=top.begin(); i!=top.end(); i++)
    {
        score+= (*i)/10;
    }
    return score;
}

void _playground::paint(QLabel *q, int a)
{
    QString number = QString::number(a/10);
    q->setText(number);
    int color = a%10;
    if(color==7)    q->setStyleSheet("QLabel { background-color : red; color : white; }");
    else if(color==6)   q->setStyleSheet("QLabel { background-color : orange; color : white; }");
    else if(color==5)   q->setStyleSheet("QLabel { background-color : yellow; color : white; }");
    else if(color==4)   q->setStyleSheet("QLabel { background-color : green; color : white; }");
    else if(color==3)   q->setStyleSheet("QLabel { background-color : cyan; color : white; }");
    else if(color==2)   q->setStyleSheet("QLabel { background-color : blue; color : white; }");
    else if(color==1)   q->setStyleSheet("QLabel { background-color : purple; color : white; }");
    else if(color==0)
    {
        q->setStyleSheet("QLabel { background-color : black; color : white; }");
        q->setText("");
    }
    else    qDebug()<<"Error: wrong color!!";
}


void _playground::paint_hand(list<int> l)
{
    int j=1;
    ui->label_1->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_2->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_3->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_4->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_5->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_6->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_7->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_1->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->label_4->setText("");
    ui->label_5->setText("");
    ui->label_6->setText("");
    ui->label_7->setText("");
    ui->listWidget->clear();
    ui->listWidget->addItem("None");
    for(list<int>::iterator i= l.begin(); i!=l.end();i++)
    {
        switch(j)
        {
            case 1: paint(ui->label_1, *i);break;
            case 2: paint(ui->label_2, *i);break;
            case 3: paint(ui->label_3, *i);break;
            case 4: paint(ui->label_4, *i);break;
            case 5: paint(ui->label_5, *i);break;
            case 6: paint(ui->label_6, *i);break;
            case 7: paint(ui->label_7, *i);break;
        }
        j++;
        ui->listWidget->addItem(name(*i));
    }

}

void _playground::paint_palette(list<int> l)
{
    int j=1;
    ui->label_10->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_11->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_12->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_13->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_14->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_15->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_16->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_17->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_10->setText("");
    ui->label_11->setText("");
    ui->label_12->setText("");
    ui->label_13->setText("");
    ui->label_14->setText("");
    ui->label_15->setText("");
    ui->label_16->setText("");
    ui->label_17->setText("");
    for(list<int>::iterator i= l.begin(); i!=l.end();i++)
    {
        switch(j)
        {
            case 1: paint(ui->label_10, *i);break;
            case 2: paint(ui->label_11, *i);break;
            case 3: paint(ui->label_12, *i);break;
            case 4: paint(ui->label_13, *i);break;
            case 5: paint(ui->label_14, *i);break;
            case 6: paint(ui->label_15, *i);break;
            case 7: paint(ui->label_16, *i);break;
            case 8: paint(ui->label_17, *i);break;
        }
        j++;
    }
}

void _playground::paint_ai(list<int> l)
{
    int j=1;
    ui->label_18->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_19->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_20->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_21->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_22->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_23->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_24->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_25->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_18->setText("");
    ui->label_19->setText("");
    ui->label_20->setText("");
    ui->label_21->setText("");
    ui->label_22->setText("");
    ui->label_23->setText("");
    ui->label_24->setText("");
    ui->label_25->setText("");
    for(list<int>::iterator i= l.begin(); i!=l.end();i++)
    {
        switch(j)
        {
            case 1: paint(ui->label_18, *i);break;
            case 2: paint(ui->label_19, *i);break;
            case 3: paint(ui->label_20, *i);break;
            case 4: paint(ui->label_21, *i);break;
            case 5: paint(ui->label_22, *i);break;
            case 6: paint(ui->label_23, *i);break;
            case 7: paint(ui->label_24, *i);break;
            case 8: paint(ui->label_25, *i);break;
        }
        j++;
    }
}

void _playground::print_rule()
{
    paint((ui->label_9),rule);
}

void _playground::on_pushButton_clicked()
{
    choose_rule = reverse_name(choose);
    ui->label->setText("Change rule with "+choose);
    qDebug()<<"choose_rule="<<choose_rule<<endl;
    if(choose_rule&&choose_palette) ui->pushButton_3->setEnabled(true);
}

void _playground::on_listWidget_itemClicked(QListWidgetItem *item)
{
    choose = item->text();
}

void _playground::on_pushButton_2_clicked()
{
    choose_palette = reverse_name(choose);
    ui->label_8->setText("Add "+choose+" to palette");
    qDebug()<<"choose_palette="<<choose_palette<<endl;
    if(choose_rule&&choose_palette) ui->pushButton_3->setEnabled(true);
}

void _playground::on_pushButton_3_clicked()
{
    paint_hand(hand1);
    paint_palette(palette1);
    qDebug()<<"human play "<<choose_rule<<"  "<<choose_palette<<endl;
    int change_rule = choose_rule;
    int add_palette = choose_palette;
    choose_rule=0;
    choose_palette=0;
    ui->listWidget->update();
    choose="";
    int delete1=0;
    int delete2=0;

                    if(change_rule%10!=0)
                    {
                        rule = change_rule%10;
                        for(list<int>::iterator i=hand1.begin(); i!=hand1.end(); i++)
                            if(change_rule==*i)
                            {
                                hand1.erase(i);
                                delete1++;
                            }
                    }
                    if(add_palette!=0)
                    {
                        palette1.push_back(add_palette);
                        for(list<int>::iterator i=hand1.begin(); i!=hand1.end(); i++)
                            if(add_palette==*i)
                            {
                                hand1.erase(i);
                                delete2++;
                            }
                    }
        qDebug()<<"(delete) "<<delete1<<"  "<<delete2<<endl;
        //print(hand1,palette1,hand2,palette2,rule);
        paint_hand(hand1);
        paint_palette(palette1);
        paint_ai(palette2);
        paint(ui->label_9,rule);
        judge();
}

void _playground::on_commandLinkButton_clicked()
{
    Rules *r= new Rules;
    r->show();
}
