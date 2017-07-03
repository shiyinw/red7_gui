#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "global.h"
#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include "rules.h"

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
    Rules *w = new Rules;
    w->show();
    this->close();
}

