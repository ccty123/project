#ifndef GAMEBOUNDARY_H
#define GAMEBOUNDARY_H

#include <QMainWindow>
#include "global.h"
#include "QDialog"
#include <QKeyEvent>
#include "QLabel"
#include <QMovie>
#include <QSound>
#include "fighting.h"
#include <QThread>

namespace Ui {
class GameBoundary;
}
extern person hero;
class GameBoundary : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameBoundary(QWidget *parent = 0);
    ~GameBoundary();
   // person hero;

private slots:
    void showfloor0();
    void jump();
    void keyPressEvent(QKeyEvent*event);

signals:
    void zero_to_one();

private:
    Ui::GameBoundary *ui;
    bool door = true;
};

#endif // GAMEBOUNDARY_H
