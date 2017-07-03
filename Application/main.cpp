#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <QString>
#include <QDebug>
#include <QDir>
#include "login.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen ss(QPixmap(":/new/prefix1/pictures/start.jpg"));
    ss.show();
    a.processEvents();
    QThread::sleep(1);
    ss.showMessage("Welcome to Red7", Qt::AlignCenter, Qt::white);
    a.processEvents();
    QThread::sleep(1);

    global::path = QDir::currentPath();
    qDebug()<<"path: "<<global::path<<endl;

    Login *w = new Login;
    w->show();
    return a.exec();
}
