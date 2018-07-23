#include "gameboundary3.h"
#include "ui_gameboundary3.h"

gameboundary3::gameboundary3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameboundary3)
{
    ui->setupUi(this);

    for (int i = 1; i <= 7; i++)
        door[i] = true;
    for (int i = 1; i <= 2; i++)
        key[i] = true;
    for (int i = 1; i <= 4; i++)
        water[i] = true;
    for (int i = 1; i <= 4; i++)
        dia[i] = true;
    steal = true;

    mon1.initial(100, 20, 5, 3, 3);
    mon2.initial(100, 20, 5, 3, 3);
    mon3.initial(70, 15, 2, 2, 2);
    mon4.initial(200, 35, 10, 5, 5);
    mon5.initial(110, 25, 5, 4, 5);
    mon6.initial(200, 35, 10, 5, 5);
    mon7.initial(200, 35, 10, 5, 5);
    mon8.initial(110, 25, 5, 4, 5);
    mon9.initial(200, 35, 10, 5, 5);
    mon10.initial(100, 20, 5, 3, 3);
    mon11.initial(100, 20, 5, 3, 3);
    mon12.initial(70, 15, 2, 2, 2);
    mon13.initial(150, 65, 30, 8, 10);
    mon15.initial(150, 65, 30, 8, 10);
    mon16.initial(150, 65, 30, 8, 10);
    mon14.initial(550, 160, 90, 20, 25);
    mon17.initial(300, 75, 45, 10, 13);
    mon19.initial(300, 75, 45, 10, 13);
    mon20.initial(300, 75, 45, 10, 13);
    mon18.initial(450, 150, 90, 19, 22);
}

gameboundary3::~gameboundary3()
{
    delete ui;
}

void gameboundary3::jump(int floor)
{
    if (floor == -1){
        this->hide();
        emit three_to_store();
    }
    else if (floor == 4){
        this->hide();
        emit three_to_four();
    }
}

void gameboundary3::move(int direction)
{
    switch (direction)
    {
    case 1:     //向上移动
        ui->character->move(ui->character->x(), (ui->character->y()) - 50);
        break;
    case 2:     //向下移动
        ui->character->move(ui->character->x(), (ui->character->y()) + 50);
        break;
    case 3:     //向左移动
        ui->character->move((ui->character->x()) - 50, ui->character->y());
        break;
    case 4:     //向右移动
        ui->character->move((ui->character->x()) + 50, ui->character->y());
        break;
    }
}

void gameboundary3::MeetDoor(int direction, int type, int index, QLabel *label)     //遇到门
{
    if (door[index])
    {
        if(hero.key_number(type)){
            hero.lose_key(type);
            label->hide();
            door[index] = false;
            switch (type) {
                case 1: ui->yellowkey->setText(hero.get_yellowkey());  break;
                case 2: ui->bluekey->setText(hero.get_bluekey()); break;
                case 3: ui->redkey->setText(hero.get_redkey()); break;
            }
        }
    }
    else
        move(direction);
}

void gameboundary3::MeetKey(int direction, int type, int index, QLabel *label)
{
    if (key[index])
    {
        hero.gain_key(type);
        key[index] = false;
        label->hide();
        switch (type) {
            case 1: ui->yellowkey->setText(hero.get_yellowkey());  break;
            case 2: ui->bluekey->setText(hero.get_bluekey()); break;
            case 3: ui->redkey->setText(hero.get_redkey()); break;
        }
    }
    else
        move(direction);
}

void gameboundary3::MeetWater(int direction, int type, int index, QLabel *label)
{
    if (water[index])
    {
        water[index] = false;
        label->hide();
        (type == 1) ? hero.raise_life(200) : hero.raise_life(500);
        ui->life->setText(hero.get_life());
    }
    else
        move(direction);
}

void gameboundary3::MeetMonster(int direction, Monster &mon, QLabel *label)
{
    if (mon.get_alive()){
        if (hero.attack_monster(mon)){
            mon.update_alive();
            ui->life->setText(hero.get_life());
            ui->attack->setText(hero.get_attack());
            ui->defense->setText(hero.get_defense());
            ui->level1->setText(hero.get_level());
            ui->exp->setText(hero.get_exp());
            ui->money->setText(hero.get_money());
            label->hide();
        }
        else
            return;
    }
    else
        move(direction);
}

void gameboundary3::MeetDia(int direction, int type, int index, QLabel *label)
{
    if (dia[index])
    {
        dia[index] = false;
        label->hide();
        if(type==1)  {  hero.raise_attack(3);ui->attack->setText(hero.get_attack());}
        else   { hero.raise_defense(3); ui->defense->setText(hero.get_defense());}
    }
    else
        move(direction);
}

void gameboundary3::showfloor3()
{
    this->show();
    ui->level1->setText(hero.get_level());         //等级
    ui->level1->setStyleSheet("color:white;");
    QFont font ( "Microsoft YaHei", 27, 75);
    ui->level1->setFont(font);
    ui->yellowkey->setText(hero.get_yellowkey());  //黄钥匙
    ui->yellowkey->setStyleSheet("color:white;");
    QFont font1 ( "Microsoft YaHei", 27, 75);
    ui->yellowkey->setFont(font1);
    ui->bluekey->setText(hero.get_bluekey());      //蓝钥匙
    ui->bluekey->setStyleSheet("color:white;");
    QFont font2 ( "Microsoft YaHei", 27, 75);
    ui->bluekey->setFont(font2);
    ui->redkey->setText(hero.get_bluekey());      //红钥匙
    ui->redkey->setStyleSheet("color:white;");
    QFont font3 ( "Microsoft YaHei", 27, 75);
    ui->redkey->setFont(font3);
    ui->life->setText(hero.get_life());         //生命值
    ui->life->setStyleSheet("color:white;");
    QFont font4 ( "Microsoft YaHei", 27, 75);
    ui->life->setFont(font4);
    ui->attack->setText(hero.get_attack());         //攻击
    ui->attack->setStyleSheet("color:white;");
    QFont font5 ( "Microsoft YaHei", 27, 75);
    ui->attack->setFont(font5);
    ui->defense->setText(hero.get_defense());         //防御
    ui->defense->setStyleSheet("color:white;");
    QFont font6 ( "Microsoft YaHei", 27, 75);
    ui->defense->setFont(font6);
    ui->exp->setText(hero.get_exp());            //经验
    ui->exp->setStyleSheet("color:white;");
    QFont font7 ( "Microsoft YaHei", 27, 75);
    ui->exp->setFont(font7);
    ui->money->setText(hero.get_money());            //金钱
    ui->money->setStyleSheet("color:white;");
    QFont font8 ( "Microsoft YaHei", 27, 75);
    ui->money->setFont(font8);
}

void gameboundary3::keyPressEvent(QKeyEvent*event)
{
    if ((event->key()==Qt::Key_A)||(event->key()==Qt::Key_Left))        //向左移动
    {
        QPixmap left(LEFT);
        ui->character->setPixmap(left);
        switch ((ui->character->x() - 300) / 50)
        {
        case 1:
            break;

        case 2:
            if (ui->character->y() == 50)
                move(3);
            break;

        case 3:
            if (ui->character->y() == 50)       //遇怪
                MeetMonster(3, mon4, ui->label_812);
            break;

        case 4:
            if (ui->character->y() == 550)
                move(3);
            break;

        case 5:
            if (ui->character->y() == 550)      //遇怪
                MeetMonster(3, mon6, ui->label_634);
            break;

        case 6:
            if (ui->character->y() == 100 || ui->character->y() == 550)
                move(3);
            else if (ui->character->y() == 200)     //遇怪
                MeetMonster(3, mon13, ui->label_816);
            else if (ui->character->y() == 250)     //蓝宝石
                MeetDia(3, 2, 1, ui->label_767);
            else if (ui->character->y() == 350)     //遇怪
                MeetMonster(3, mon17, ui->label_772);
            else if (ui->character->y() == 400)     //红宝石
                MeetDia(3, 1, 3, ui->label_773);
            else if (ui->character->y() == 500)     //黄钥匙
              {  MeetKey(3, 1, 1, ui->label_501);
                ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 7:
            if (ui->character->y() == 100 || ui->character->y() == 250 ||ui->character->y() == 400 || ui->character->y() == 500 || ui->character->y() == 550)
                move(3);
            else if (ui->character->y() == 200)     //遇怪
                MeetMonster(3, mon14, ui->label_817);
            else if (ui->character->y() == 350)     //遇怪
                MeetMonster(3, mon18, ui->label_778);
            break;

        case 8:
            if (ui->character->y() == 550)
                move(3);
            break;

        case 9:
            if (ui->character->y() == 550)      //遇怪
                MeetMonster(3, mon7, ui->label_780);
            break;

        case 10:
            if (ui->character->y() == 50)
                move(3);
            break;

        case 11:
            if (ui->character->y() == 50)       //遇怪
                MeetMonster(3, mon9, ui->label_811);
            break;

        default:
            break;
        }
    }

    else  if ((event->key()==Qt::Key_S)||(event->key()==Qt::Key_Down))      //向下移动
    {
        QPixmap down(DOWN);
        ui->character->setPixmap(down);
        switch (ui->character->y() / 50)
        {
        case 1:
            if (ui->character->x() == 450 || ui->character->x() == 550 || ui->character->x() == 650 || ui->character->x() == 850)
                move(2);
            else if (ui->character->x() == 350)     //黄门
            {    MeetDoor(2, 1, 1, ui->label_395);
                ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->x() == 750)     //黄门
                MeetDoor(2, 1, 3, ui->label_473);
            break;

        case 2:
            if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 750 || ui->character->x() == 850 || ui->character->x() == 600)
                move(2);
            break;

        case 3:
            if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 600 || ui->character->x() == 850)
                move(2);
            else if (ui->character->x() == 750)     //遇怪
                MeetMonster(2, mon8, ui->label_766);
            break;

        case 4:
            if (ui->character->x() == 450 || ui->character->x() == 600 || ui->character->x() == 850)
                move(2);
            else if (ui->character->x() == 350)     //遇怪
                MeetMonster(2, mon1, ui->label_726);
            else if (ui->character->x() == 550)     //蓝宝石
                MeetDia(2, 2, 1, ui->label_767);
            else if (ui->character->x() == 650)     //蓝宝石
                MeetDia(2, 2, 2, ui->label_779);
            else if (ui->character->x() == 750)     //红药水
                MeetWater(2, 1, 2, ui->label_765);
            break;

        case 5:
            if (ui->character->x() == 450 || ui->character->x() == 600 || ui->character->x() == 850)
                move(2);
            else if (ui->character->x() == 350)     //遇怪
                MeetMonster(2, mon2, ui->label_758);
            else if (ui->character->x() == 750)     //红药水
                MeetWater(2, 1, 4, ui->label_764);
            break;

        case 6:
            if (ui->character->x() == 450 || ui->character->x() == 600 || ui->character->x() == 750 || ui->character->x() == 850)
                move(2);
            else if (ui->character->x() == 350)     //遇怪
                MeetMonster(2, mon3, ui->label_719);
            break;

        case 7:
            if (ui->character->x() == 450 || ui->character->x() == 350 || ui->character->x() == 600 || ui->character->x() == 850 || ui->character->x() == 750)
                move(2);
            else if (ui->character->x() == 550)     //红宝石
                MeetDia(2, 1, 3, ui->label_773);
            else if (ui->character->x() == 650)     //红宝石
                MeetDia(2, 1, 4, ui->label_777);
            break;

        case 8:
            if (ui->character->x() == 450 || ui->character->x() == 350 || ui->character->x() == 600 || ui->character->x() == 850 || ui->character->x() == 750)
                move(2);
            break;

        case 9:
            if (ui->character->x() == 450 || ui->character->x() == 350 || ui->character->x() == 600 || ui->character->x() == 850 || ui->character->x() == 750)
                move(2);
            break;

        case 10:
            if (ui->character->x() == 450 || ui->character->x() == 550 || ui->character->x() == 600 || ui->character->x() == 650 || ui->character->x() == 750)
                move(2);
            else if (ui->character->x() == 350)     //上到4楼
                jump(4);
            else if (ui->character->x() == 850)     //下到store楼
                jump(-1);
            break;

        default:
            break;
        }
    }

    else  if ((event->key()==Qt::Key_D)||(event->key()==Qt::Key_Right))     //向右移动
    {
        QPixmap right(RIGHT);
        ui->character->setPixmap(right);
        switch ((ui->character->x() - 300) / 50)
        {
        case 1:
            if (ui->character->y() == 50)
                move(4);
            break;

        case 2:
            if (ui->character->y() == 50)
                move(4);
            break;

        case 3:
            if (ui->character->y() == 550)
                move(4);
            break;

        case 4:
            if (ui->character->y() == 550)
                move(4);
            break;

        case 5:
            if (ui->character->y() == 100 || ui->character->y() == 250 || ui->character->y() == 400 || ui->character->y() == 500 || ui->character->y() == 550)
                move(4);
            else if (ui->character->y() == 200)     //遇怪
                MeetMonster(4, mon14, ui->label_817);
            else if (ui->character->y() == 350)     //遇怪
                MeetMonster(4, mon18, ui->label_778);
            break;

        case 6:
            if (ui->character->y() == 100 || ui->character->y() == 550)
                move(4);
            else if (ui->character ->y() == 200)        //遇怪
                MeetMonster(4, mon15, ui->label_818);
            else if (ui->character->y() == 250)     //蓝宝石
                MeetDia(4, 2, 2, ui->label_779);
            else if (ui->character->y() == 350)     //遇怪
                MeetMonster(4, mon19, ui->label_774);
            else if (ui->character->y() == 400)     //红宝石
                MeetDia(4, 1, 4, ui->label_777);
            else if (ui->character->y() == 500)     //黄钥匙
            {    MeetKey(4, 1, 2, ui->label_561);
               ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 7:
            if (ui->character->y() == 550)
                move(4);
            break;

        case 8:
            if (ui->character->y() == 550)
                move(4);
            break;

        case 9:
            if (ui->character->y() == 50)
                move(4);
            break;

        case 10:
            if (ui->character->y() == 50)
                move(4);
            break;

        default:
            break;
        }
    }

    else  if ((event->key()==Qt::Key_W)||(event->key()==Qt::Key_Up))        //向上移动
    {
        QPixmap up(UP);
        ui->character->setPixmap(up);
        switch (ui->character->y() / 50)
        {
        case 1:
            break;

        case 2:
            if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 750 || ui->character->x() == 850 || ui->character->x() == 550 || ui->character->x() == 650)
                move(1);
            else if (ui->character->x() == 600)        //小偷
            {
                if (steal){
                    steal = false;
                    ui->label_724->hide();
                    for (int i = 1; i <= 10; i++)
                        hero.raise_level();
                    ui->attack->setText(hero.get_attack());
                    ui->defense->setText(hero.get_defense());
                    ui->life->setText(hero.get_life());
                    ui->level1->setText(hero.get_level());
                }
                else
                    move(1);
            }
            break;

        case 3:
            if (ui->character->x() == 350 || ui->character->x() == 600 || ui->character->x() == 750)
                move(1);
            else if (ui->character->x() == 450)     //黄门
            {    MeetDoor(1, 1, 2, ui->label_410);
                ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->x() == 850)     //黄门
             {   MeetDoor(1, 1, 4, ui->label_457);
                ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 4:
            if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 750 || ui->character->x() == 850)
                move(1);
            else if (ui->character->x() == 600)     //栏杆
            {
                if (door[5]){
                    door[5] = false;
                    ui->label_810->hide();
                }
                else
                    move(1);
            }
            break;

        case 5:
            if (ui->character->x() == 350 || ui->character->x() == 750 || ui->character->x() == 850)
                move(1);
            else if (ui->character->x() == 450)     //遇怪
                MeetMonster(1, mon5, ui->label_656);
            else if (ui->character->x() == 550)     //遇怪
                MeetMonster(1, mon13, ui->label_816);
            else if (ui->character->x() == 600)     //遇怪
                MeetMonster(1, mon14, ui->label_817);
            else if (ui->character->x() == 650)     //遇怪
                MeetMonster(1, mon15, ui->label_818);
            break;

        case 6:
            if (ui->character->x() == 350 || ui->character->x() == 750)
                move(1);
            else if (ui->character->x() == 450)     //红药水
                MeetWater(1, 1, 1, ui->label_636);
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(1, mon10, ui->label_759);
            else if (ui->character->x() == 600)     //遇怪
                MeetMonster(1, mon16, ui->label_815);
            break;

        case 7:
            if (ui->character->x() == 350 || ui->character->x() == 750)
                move(1);
            else if (ui->character->x() == 450)     //红药水
                MeetWater(1, 1, 3, ui->label_763);
            else if (ui->character->x() == 600)     //红门
             {   MeetDoor(1, 3, 6, ui->label_483);
               ui->redkey->setText(hero.get_bluekey());}
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(1, mon11, ui->label_762);
            break;

        case 8:
            if (ui->character->x() == 350 || ui->character->x() == 750 || ui->character->x() == 450)
                move(1);
            else if (ui->character->x() == 550)     //遇怪
                MeetMonster(1, mon17, ui->label_772);
            else if (ui->character->x() == 600)     //遇怪
                MeetMonster(1, mon18, ui->label_778);
            else if (ui->character->x() == 650)     //遇怪
                MeetMonster(1, mon19, ui->label_774);
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(1, mon12, ui->label_770);
            break;

        case 9:
            if (ui->character->x() == 350 || ui->character->x() == 750 || ui->character->x() == 450 || ui->character->x() == 850)
                move(1);
            else if (ui->character->x() == 600)     //遇怪
                MeetMonster(1, mon20, ui->label_771);
            break;

        case 10:
            if (ui->character->x() == 350 || ui->character->x() == 750 || ui->character->x() == 450 || ui->character->x() == 850)
                move(1);
            else if (ui->character->x() == 600)     //蓝门
                MeetDoor(1, 2, 7, ui->label_813);
            break;

        case 11:
            if (ui->character->x() == 750 || ui->character->x() == 450 || ui->character->x() == 600)
                move(1);
            else if (ui->character->x() == 550)     //黄钥匙
           {     MeetKey(1, 1, 1, ui->label_501);
               ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->x() == 650)     //黄钥匙
            {    MeetKey(1, 1, 2, ui->label_561);
               ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        default:
            break;
        }
    }

    else QWidget::keyPressEvent(event);
}


