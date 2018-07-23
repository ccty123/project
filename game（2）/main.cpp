#include "gameboundary.h"
#include "gameboundary1.h"
#include "gameboundary2.h"
#include "gameboundary3.h"
#include "gameboundary4.h"
#include "store.h"
#include <QApplication>

person hero;
int main(int argc,char *args[])
{
    QApplication a(argc, args);
    GameBoundary floor0;
    GameBoundary1 floor1;
    gameboundary2 floor2;
    gameboundary3 floor3;
    gameboundary4 floor4;
    store floor2_2;

    QSound sound1(MUSIC1);
    QSound sound2(MUSIC2);

    sound1.play();
    floor0.show();

    QObject::connect(&floor0,SIGNAL(zero_to_one()),&sound2,SLOT(play()));
    QObject::connect(&floor0,SIGNAL(zero_to_one()),&sound1,SLOT(stop()));
    QObject::connect(&floor1,SIGNAL(one_to_zero()),&sound1,SLOT(play()));
    QObject::connect(&floor1,SIGNAL(one_to_zero()),&sound2,SLOT(stop()));

    QObject::connect(&floor0,SIGNAL(zero_to_one()),&floor1,SLOT(showfloor1()));
    QObject::connect(&floor1,SIGNAL(one_to_zero()),&floor0,SLOT(showfloor0()));
    QObject::connect(&floor1,SIGNAL(one_to_two()),&floor2,SLOT(showfloor2()));
    QObject::connect(&floor2,SIGNAL(two_to_one()),&floor1,SLOT(showfloor1()));
    QObject::connect(&floor2,SIGNAL(two_to_store()),&floor2_2,SLOT(showfloor2_2()));
    QObject::connect(&floor2_2,SIGNAL(store_to_two()),&floor2,SLOT(showfloor2()));
    QObject::connect(&floor2_2,SIGNAL(store_to_three()),&floor3,SLOT(showfloor3()));
    QObject::connect(&floor3,SIGNAL(three_to_store()),&floor2_2,SLOT(showfloor2_2()));
    QObject::connect(&floor3,SIGNAL(three_to_four()),&floor4,SLOT(showfloor4()));
    QObject::connect(&floor4,SIGNAL(four_to_three()),&floor3,SLOT(showfloor3()));
    return a.exec();
}
