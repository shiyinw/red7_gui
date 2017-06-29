#include "mainwindow.h"
#include "rules.h"
#include "ui_rules.h"

Rules::Rules(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Rules)
{
    ui->setupUi(this);
}

Rules::~Rules()
{
    delete ui;
}

void Rules::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}
