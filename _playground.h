#ifndef _PLAYGROUND_H
#define _PLAYGROUND_H

#include <QMainWindow>

namespace Ui {
class _playground;
}

class _playground : public QMainWindow
{
    Q_OBJECT

public:
    explicit _playground(QWidget *parent = 0);
    ~_playground();

private:
    Ui::_playground *ui;
};

#endif // _PLAYGROUND_H
