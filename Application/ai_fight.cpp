#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <fcntl.h>
#include <cstring>
#include <signal.h>
#include <ctime>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include <QProcess>
#include <QMessageBox>

#include "mainwindow.h"
#include "global.h"

#include "ai_fight.h"
#include "ui_ai_fight.h"
#define LOG_FILE "log.txt"
#define PLAYER_OUTPUT "output.txt"
#define MAX_PLAYERS 4
#define MAX_ROUNDS 12
#define TIME_LIMIT 2

using namespace std;

ai_fight::ai_fight(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ai_fight)
{
    ui->setupUi(this);
    naive_module_run();

}

ai_fight::~ai_fight()
{
   MainWindow *m = new MainWindow;
   m->show();
    delete ui;
}


void ai_fight::naive_module_run()
{
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<"cd ../AI");
    p.waitForStarted();
    p.waitForFinished();
    p.start("cmd", QStringList()<<"/c"<<"./red7 "<<global::player1<<" "<<global::player2<<" -m 0 -g 1");
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());

    QMessageBox testMassage;
    testMassage.setText(strTemp);
    testMassage.exec();
}

void ai_fight::extend_module_run()
{

}
