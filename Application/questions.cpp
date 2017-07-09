#include "questions.h"
#include "ui_questions.h"

Questions::Questions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Questions)
{
    ui->setupUi(this);
}

Questions::~Questions()
{
    delete ui;
}
