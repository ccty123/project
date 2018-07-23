#include "monster.h"
Monster::Monster():
    alive(true)
{

}

void Monster::initial(int life, int attack, int defense, int exp, int money)
{
    this->life = life;
    this->attack = attack;
    this->defense = defense;
    this->exp = exp;
    this->money = money;
}

Monster::~Monster()
{

}

bool Monster::get_alive()const
{
    return alive;
}

void Monster::update_alive()
{
    alive = false;
}

int Monster::get_life()const
{
    return life;
}

int Monster::get_attack()const
{
    return attack;
}

int Monster::get_defense()const
{
    return defense;
}

int Monster::get_exp()const
{
    return exp;
}

int Monster::get_money()const
{
    return money;
}




























