#ifndef MONSTER_H
#define MONSTER_H
class Monster
{
public:
    Monster();
    void initial(int life, int attack, int defense, int exp, int money);
    ~Monster();

    bool get_alive()const;
    void update_alive();
    int get_life()const;
    int get_attack()const;
    int get_defense()const;
    int get_exp()const;
    int get_money()const;

private:
    bool alive;
    int life;
    int attack;
    int defense;
    int exp;
    int money;
};



#endif // MONSTER_H
