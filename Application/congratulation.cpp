#include "congratulation.h"
#include "ui_congratulation.h"

congratulation::congratulation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::congratulation)
{
    ui->setupUi(this);
}

congratulation::~congratulation()
{
    delete ui;
}
