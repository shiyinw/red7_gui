#include "ai_fight.h"
#include "ui_ai_fight.h"

ai_fight::ai_fight(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ai_fight)
{
    ui->setupUi(this);
}

ai_fight::~ai_fight()
{
    delete ui;
}
