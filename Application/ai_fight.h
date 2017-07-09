#ifndef AI_FIGHT_H
#define AI_FIGHT_H

#include <QMainWindow>
#include <fstream>
#include <QLabel>
#include <sstream>
using namespace std;

namespace Ui {
class ai_fight;
}

class ai_fight : public QMainWindow
{
    Q_OBJECT

public:
    explicit ai_fight(QWidget *parent = 0);
    ~ai_fight();
    void getfile();

private slots:
    void on_pushButton_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::ai_fight *ui;
    void naive_module_run();
    void extend_module_run();
    void print_p1hand(string s);
    void print_p2hand(string s);
    void print_p1p(string s);
    void print_p2p(string s);
    void print_rule(string s);
    void print_win(string s);

    int p0, p1;

    void print(QLabel *q, int a);

    std::ifstream t;
    std::stringstream buffer;
    string line;
    string rule, p1hand, p1p, p2hand, p2p, announce;
    string win, buf;
};

#endif // AI_FIGHT_H
