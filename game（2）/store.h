#ifndef STORE_H
#define STORE_H

#include <QMainWindow>
#include "gameboundary2.h"

namespace Ui {
class store;
}

class store : public QMainWindow
{
    Q_OBJECT

public:
    explicit store(QWidget *parent = 0);
    ~store();

public:


    bool door[3];
    bool key[8];
    bool sword;
    bool water;
    bool reddia;
    bool bluedia;

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
    Monster mon13;
    Monster mon14;
    Monster mon15;
    Monster mon16;
    Monster mon17;

private slots:
    void jump(int floor);
    void move(int direction);
    void MeetKey(int direction, int type, int index, QLabel* label);
    void MeetDoor(int direction, int type, int index, QLabel* label);
    void MeetMonster(int direction, Monster& mon, QLabel* label);
    void keyPressEvent(QKeyEvent* event);
    void showfloor2_2();

signals:
    void store_to_two();
    void store_to_three();

private:
    Ui::store *ui;
};

#endif // STORE_H
