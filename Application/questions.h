#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <QMainWindow>

namespace Ui {
class Questions;
}

class Questions : public QMainWindow
{
    Q_OBJECT

public:
    explicit Questions(QWidget *parent = 0);
    ~Questions();

private:
    Ui::Questions *ui;
};

#endif // QUESTIONS_H
