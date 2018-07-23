#ifndef GAMEBOUNDARY4_H
#define GAMEBOUNDARY4_H

#include <QMainWindow>
#include "gameboundary3.h"

namespace Ui {
class gameboundary4;
}
extern person hero;
class gameboundary4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameboundary4(QWidget *parent = 0);
    ~gameboundary4();

public:
    bool door[6];
    bool key[4];
    bool all_key;
    bool tool;
    bool dia[4];
    bool water[4];

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
    Monster mon21;


private slots:
    void jump(int floor);
    void move(int direction);
    void MeetKey(int direction, int type, int index, QLabel* label);
    void MeetWater(int direction, int type, int index, QLabel* label);
    void MeetDoor(int direction, int type, int index, QLabel* label);
    void MeetMonster(int direction, Monster& mon, QLabel* label);
    void MeetDia(int direction, int type, int index, QLabel* label);
    void keyPressEvent(QKeyEvent* event);
    void showfloor4();

signals:
    void four_to_three();
private:
    Ui::gameboundary4 *ui;
};

#endif // GAMEBOUNDARY4_H
