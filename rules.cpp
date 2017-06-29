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
