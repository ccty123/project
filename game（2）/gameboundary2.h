#ifndef GAMEBOUNDARY2_H
#define GAMEBOUNDARY2_H

#include <QMainWindow>
#include "gameboundary1.h"
#include "gameboundary.h"

namespace Ui {
class gameboundary2;
}

class gameboundary2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameboundary2(QWidget *parent = 0);
    ~gameboundary2();

public:
    bool door[9];
    bool key[11];
    bool water[7];
    bool dia[8];
    bool irondoor;
    bool npc[2];

    Monster mon1;
    Monster mon2;
    Monster mon3;

private slots:
    void jump(int floor);
    void move(int direction);
    void MeetKey(int direction, int type, int index, QLabel* label);
    void MeetWater(int direction, int type, int index, QLabel* label);
    void MeetDoor(int direction, int type, int index, QLabel* label);
    void MeetMonster(int direction, Monster& mon, QLabel* label);
    void MeetDia(int direction, int type, int index, QLabel* label);
    void keyPressEvent(QKeyEvent* event);
    void showfloor2();

    void on_up_clicked();
    void on_down_clicked();
    void on_left_clicked();
    void on_right_clicked();

signals:
    void two_to_one();
    void two_to_store();

private:
    Ui::gameboundary2 *ui;
};

#endif // GAMEBOUNDARY2_H
