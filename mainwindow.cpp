#include <QDebug>
#include <QString>
#include <QListWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "_playground.h"
#include "ai_fight.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"player1: "<<player1<<endl;
    qDebug()<<"player2: "<<player2<<endl;
    if(player1 == "Me")
    {
        _playground *p = new _playground;
        p->show();
        this->close();
    }
    else if(player1 == "Naive AI")
    {
        ai_fight *p = new ai_fight;
        p->show();
        this->close();
    }
    else if(player1 == "Trivial AI")
    {
        ai_fight *p = new ai_fight;
        p->show();
        this->close();
    }
    else if(player1 == "Your AI")
    {
        ai_fight *p = new ai_fight;
        p->show();
        this->close();
    }

}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    player1 = item->text();
}

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    player2 = item->text();
}
