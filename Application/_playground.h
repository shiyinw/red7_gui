#ifndef _PLAYGROUND_H
#define _PLAYGROUND_H

#include <QMainWindow>
#include <iostream>
#include <list>
#include <QtGlobal>
#include <QTime>
#include <random>
#include "Common.h"
#include <QDateTime>
#include "AI.h"
#include <stdlib.h>
#include <QLabel>
#include <QListWidgetItem>

#define WIN_SCORE 45

namespace Ui {
class _playground;
}

class _playground : public QMainWindow
{
    Q_OBJECT

public:
    explicit _playground(QWidget *parent = 0);
    ~_playground();

    void paint(QLabel *q, int a);
    void paint_hand(list<int> l);
    void paint_palette(list<int> l);
    void paint_ai(list<int> l);
    void print_rule();

    list<int> hand1, hand2;
    list<int> palette1, palette2;
    int card1, card2;
    int score1, score2;

    // 2 is AI
    int rule;
    bool p_alive, ai_alive;

    list<int> _strategy;
    int choose_rule;
    int choose_palette;
    QString choose;


private:
    Ui::_playground *ui;
    int score(list<int> a, int r);//结局的时候算分用
    void new_game();
    Trivial *p2;
    int current_player;
    void _print(QLabel *q, int a);
public:
    void ai_play();
    void judge();
private slots:
    void on_pushButton_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_commandLinkButton_clicked();
};

#endif // _PLAYGROUND_H
