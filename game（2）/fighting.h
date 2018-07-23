#ifndef FIGHTING_H
#define FIGHTING_H

#include <QWidget>

namespace Ui {
class fighting;
}

class fighting : public QWidget
{
    Q_OBJECT

public:
    explicit fighting(QWidget *parent = 0);
    ~fighting();

private:
    Ui::fighting *ui;
};

#endif // FIGHTING_H
