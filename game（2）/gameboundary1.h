#ifndef GAMEBOUNDARY1_H
#define GAMEBOUNDARY1_H

#include <QMainWindow>
#include "gameboundary.h"

namespace Ui {
class GameBoundary1;
}
extern person hero;
class GameBoundary1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameBoundary1(QWidget *parent = 0);
    ~GameBoundary1();

public:


    bool door[6];
    bool key[14];
    bool water[8];
    bool dia[2];
    bool check_tool;

    Monster mon1;
    Monster mon2;
    Monster mon3;
    Monster mon4;
    Monster mon5;
    Monster mon6;
    Monster mon7;
    Monster mon8;
    Monster mon9;
    Monster mon10;
    Monster mon11;
    Monster mon12;

private slots:
    void jump(int floor);
    void move(int direction);
    void MeetKey(int direction, int type, int index, QLabel* label);
    void MeetWater(int direction, int type, int index, QLabel* label);
    void MeetDoor(int direction, int type, int index, QLabel* label);
    void MeetMonster(int direction, Monster& mon, QLabel* label);
    void on_up_clicked();
    void on_down_clicked();
    void on_left_clicked();
    void on_right_clicked();
    void keyPressEvent(QKeyEvent*event);
    void showfloor1();

signals:
    void one_to_zero();
    void one_to_two();

private:
    Ui::GameBoundary1 *ui;
};

#endif // GAMEBOUNDARY1_H
