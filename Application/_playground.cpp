#include "_playground.h"
#include "ui__playground.h"
#include <QPalette>

_playground::_playground(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::_playground)
{
    ui->setupUi(this);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
}

_playground::~_playground()
{
    delete ui;
}
