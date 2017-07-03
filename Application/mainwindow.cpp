#include <QDebug>
#include <QString>
#include <QListWidgetItem>
#include <QString>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QStringList>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "_playground.h"
#include "ai_fight.h"
#include "questions.h"
#include "global.h"
#include "login.h"
#include "rules.h"

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

    selected1=1;
    if(selected1==1 && selected2==1)
        ui->pushButton_3->setEnabled(1);
    else
        ui->pushButton_3->setEnabled(0);


    if(_player1=="Naive AI")
        global::player1="pure_random";
    else if (_player1=="Trivial AI")
        global::player1="trivial";
    else if (_player1=="Me")
        global::player1="Me";
    else if (_player1=="Your AI")
    {
        QString fileName;
        fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile()"));
        qDebug()<<'file path: '<<fileName<<endl;
        std::string f=fileName.toStdString();
        int pos = f.find_last_of('/');
        QString s=QString::fromStdString(f.substr(pos + 1) );
        global::player1=s;

        QProcess p(0);
        QString cmd = "cp -av "+fileName+" "+global::path+"/../../../../AI";
        qDebug()<<cmd<<endl;
        p.start(cmd);
        p.waitForStarted();
        p.waitForFinished();
        QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());
        QMessageBox testMassage;
        testMassage.setText(strTemp);
        testMassage.exec();
    }
    else
        qDebug()<<"Error!!"<<endl;
    qDebug()<<"player1: "<<global::player1<<endl;
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
    QString fileName;
    if(_player2 == "Your AI")
    {
        QString fileName;
        fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile()"));
        qDebug()<<'file path: '<<fileName<<endl;
        std::string f=fileName.toStdString();
        int pos = f.find_last_of('/');
        QString s=QString::fromStdString(f.substr(pos + 1) );
        global::player2=s;
        qDebug()<<"player2: "<<s<<endl;
        QProcess p(0);
        p.start("cmd", QStringList()<<"/c"<<"cp -av "<<fileName<<" ../AI");
        p.waitForStarted();
        p.waitForFinished();

    }
    else if(_player2=="Naive AI")
        global::player2 = "pure_random";
    else if(_player2=="Trivial AI")
        global::player2 = "trivial";
    else
        qDebug()<<"Error!!"<<endl;
    qDebug()<<"player2: "<<global::player2<<endl;

    selected2=1;
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
        ai_fight *a = new ai_fight;
        a->show();
        this->close();
    }
    else if(_player1=="Me")
    {
        _playground *p = new _playground;
        p->show();
        this->close();
    }
    else qDebug()<<"Error!!"<<endl;

}
