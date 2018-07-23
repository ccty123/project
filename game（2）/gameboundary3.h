#ifndef GAMEBOUNDARY3_H
#define GAMEBOUNDARY3_H

#include <QMainWindow>
#include "store.h"

namespace Ui {
class gameboundary3;
}
extern person hero;
class gameboundary3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameboundary3(QWidget *parent = 0);
    ~gameboundary3();

public:
    bool door[7];
    bool key[2];
    bool water[4];
    bool dia[4];
    bool steal;

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
    Monster mon18;
    Monster mon19;
    Monster mon20;

private slots:
    void jump(int floor);
    void move(int direction);
    void MeetKey(int direction, int type, int index, QLabel* label);
    void MeetWater(int direction, int type, int index, QLabel* label);
    void MeetDoor(int direction, int type, int index, QLabel* label);
    void MeetMonster(int direction, Monster& mon, QLabel* label);
    void MeetDia(int direction, int type, int index, QLabel* label);
    void keyPressEvent(QKeyEvent* event);
    void showfloor3();

signals:
    void three_to_store();
    void three_to_four();

private:
    Ui::gameboundary3 *ui;
};

#endif // GAMEBOUNDARY3_H
