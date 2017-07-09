#ifndef CONGRATULATION_H
#define CONGRATULATION_H

#include <QDialog>

namespace Ui {
class congratulation;
}

class congratulation : public QDialog
{
    Q_OBJECT

public:
    explicit congratulation(QWidget *parent = 0);
    ~congratulation();

public:
    Ui::congratulation *ui;
};

#endif // CONGRATULATION_H
