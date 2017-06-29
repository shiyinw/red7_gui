#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "global.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    global::meid = this->ui->lineEdit->text();
    qDebug()<<"id: "<<global::meid<<endl;
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}

