#ifndef PERSON_H
#define PERSON_H

#include "monster.h"
#include <QString>
#include "fighting.h"

class person {
private:
    int life;
    int attack;
    int defense;
    int exp;
    int level;
    int money;
    int yellowkey;
    int redkey;
    int bluekey;
    bool mainkey;

public:
    person();
    ~person();
    int key_number(int color)const;
    int attack_monster(Monster mons);
    void raise_level();
    void raise_life(int number);
    void raise_attack(int number);
    void raise_defense(int number);
    void gain_key(int color);
    void lose_key(int color);
    void get_mainkey();
    bool mainkey_num()const;

    QString get_life()const;
    QString get_attack()const;
    QString get_defense()const;
    QString get_money()const;
    QString get_level()const;
    QString get_yellowkey()const;
    QString get_bluekey()const;
    QString get_redkey()const;
    QString get_exp()const;
  //  void set_life()const;


};

#endif // PERSON_H
