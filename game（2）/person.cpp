#include "person.h"

#include <QThread>

person::person()
{
    this->life = 1000;
    this->attack = 10;
    this->defense = 10;
    this->exp = 0;
    this->level = 1;
    this->money = 0;
    this->yellowkey = 1;
    this->redkey = 1;
    this->bluekey = 1;
    this->mainkey = false;
}

person::~person()
{

}

void person::get_mainkey()
{
    this->mainkey = true;
}

int person::key_number(int color) const
{
    if (color == 1)
        return this->yellowkey;
    else if (color == 2)
        return this->bluekey;
    else if (color == 3)
        return this->redkey;
    else
        return 0;
}

int person::attack_monster(Monster mons)
{
    int plife = this->life;
    int mlife = mons.get_life();
    int i = this->attack - mons.get_defense();
    if(i<0) i=0;
    int j = mons.get_attack() - this->defense;
    if(j<0) j=0;

    while (plife > 0) {
        plife -= j;
        if (plife <= 0)
            return 0;
        mlife -= i;
        if (mlife <= 0)
            break;
    }
    /*fighting event;
    event.show();
    QThread::msleep(900);
    event.hide();*/

    this->life = plife;
    this->exp += mons.get_exp();
    this->money += mons.get_money();
    if (this->exp >= this->level * 10) raise_level();
    if (this->money >= 25){
        money -= 25;
        this->attack += 2;
        this->defense += 2;
        this->life += 100;
    }
    return 1;
}

bool person::mainkey_num()const
{
    return this->mainkey;
}

void person::raise_level()
{
    this->raise_life(200);
    this->level++;
    this->exp -= (this->level - 1) * 10;
    this->attack += 3;
    this->defense += 3;
}

void person::raise_life(int number)
{
    this->life += number;
}

void person::raise_attack(int number)
{
    this->attack += number;
}

void person::raise_defense(int number)
{
    this->defense += number;
}

void person::gain_key(int color)
{
    switch (color) {
        case 1: this->yellowkey++; break;
        case 2: this->bluekey++; break;
        case 3: this->redkey++; break;
    }
}

void person::lose_key(int color)
{
    switch (color) {
        case 1: this->yellowkey--; break;
        case 2: this->bluekey--; break;
        case 3: this->redkey--; break;
    }
}

QString person::get_life()const
{
    return QString::number(life,10);
}

QString person::get_attack()const
{
    return QString::number(attack,10);
}

QString person::get_defense()const
{
    return QString::number(defense,10);
}

QString person::get_money()const
{
    return QString::number(money,10);
}

QString person::get_level()const
{
    return QString::number(level,10);
}
QString person::get_bluekey()const
{
    return QString::number(bluekey,10);
}
QString person::get_yellowkey()const
{
    return QString::number(yellowkey,10);
}
QString person::get_redkey()const
{
    return QString::number(redkey,10);
}
QString person:: get_exp()const
{
    return QString::number(exp,10);
}
