#ifndef AI_FIGHT_H
#define AI_FIGHT_H

#include <QMainWindow>

namespace Ui {
class ai_fight;
}

class ai_fight : public QMainWindow
{
    Q_OBJECT

public:
    explicit ai_fight(QWidget *parent = 0);
    ~ai_fight();

private:
    Ui::ai_fight *ui;
    void naive_module_run();
    void extend_module_run();
};

#endif // AI_FIGHT_H
