#include <QDebug>
#include <QString>
#include <QListWidgetItem>
#include <QString>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "_playground.h"
#include "ai_fight.h"
#include "questions.h"
#include "global.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("Me");
    ui->listWidget->addItem("Naive AI");
    ui->listWidget->addItem("Trivial AI");
    ui->listWidget->addItem("Your AI");
    ui->listWidget_2->addItem("Naive AI");
    ui->listWidget_2->addItem("Trivial AI");
    ui->listWidget_2->addItem("Your AI");
    ui->pushButton_3->setEnabled(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"player1: "<<_player1<<endl;
    if(_player1 == "Your AI")
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile(*.*);;mp3file(*.mp3)"));
        qDebug()<<'file path: '<<fileName<<endl;
    }
    selected1=1;
    //global::player1 = _player1;
    if(selected1==1 && selected2==1)
        ui->pushButton_3->setEnabled(1);
    else
        ui->pushButton_3->setEnabled(0);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    _player1 = item->text();
}

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    _player2 = item->text();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"player2: "<<_player2<<endl;
    if(_player2 == "Your AI")
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile(*.*);;cpp(*.cpp);;exec()"));
        qDebug()<<'file path: '<<fileName<<endl;
    }
    selected2=1;
    //global::player2 = _player2;
    if(selected1==1 && selected2==1)
        ui->pushButton_3->setEnabled(1);
    else
        ui->pushButton_3->setEnabled(0);
}

void MainWindow::on_commandLinkButton_clicked()
{
    Questions *q = new Questions;
    q->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(_player1=="Naive AI"||_player1=="Trivial AI"||_player1=="Your AI")
    {
        if(_player2=="Naive AI"||_player2=="Trivial AI"||_player2=="Your AI")
        {
            ai_fight *a = new ai_fight;
            a->show();
            this->close();
        }
    }
    else if(_player1=="Me")
    {
        _playground *p = new _playground;
        p->show();
        this->close();
    }

}
