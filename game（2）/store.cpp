#include "store.h"
#include "ui_store.h"

store::store(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::store)
{
    ui->setupUi(this);

    for (int i = 1; i <= 3; i++)
        door[i] = true;
    for (int i = 1; i <= 8; i++)
        key[i] = true;
    sword = false;
    water = true;
    reddia = true;
    bluedia = true;

    mon1.initial(70, 15, 2, 2, 2);
    mon2.initial(70, 15, 2, 2, 2);
    mon3.initial(100, 20, 5, 3, 3);
    mon4.initial(110, 25, 5, 4, 5);
    mon5.initial(110, 25, 5, 4, 5);
    mon6.initial(70, 15, 2, 2, 2);
    mon7.initial(100, 20, 5, 3, 3);
    mon8.initial(50, 20, 1, 1, 1);
    mon9.initial(100, 20, 5, 3, 3);
    mon10.initial(70, 15, 2, 2, 2);
    mon11.initial(100, 20, 5, 3, 3);
    mon12.initial(70, 15, 2, 2, 2);
    mon13.initial(50, 20, 1, 1, 1);
    mon14.initial(100, 20, 5, 3, 3);
    mon15.initial(70, 15, 2, 2, 2);
    mon16.initial(70, 15, 2, 2, 2);
    mon17.initial(100, 20, 5, 3, 3);

    /*QMovie* movie = new QMovie(STORE);
    ui->label_605->setMovie(movie);
    movie->start();*/

    QMovie* movie1 = new QMovie(MON1);
    ui->label_653->setMovie(movie1);
    ui->label_649->setMovie(movie1);
    movie1->start();

    QMovie* movie2 = new QMovie(MON2);
    ui->label_585->setMovie(movie2);
    ui->label_591->setMovie(movie2);
    ui->label_525->setMovie(movie2);
    ui->label_472->setMovie(movie2);
    ui->label_474->setMovie(movie2);
    ui->label_424->setMovie(movie2);
    ui->label_431->setMovie(movie2);
    movie2->start();

    QMovie* movie4 = new QMovie(MON4);
    ui->label_641->setMovie(movie4);
    ui->label_625->setMovie(movie4);
    movie4->start();

    QMovie* movie7 = new QMovie(MON7);
    ui->label_531->setMovie(movie7);
    ui->label_518->setMovie(movie7);
    ui->label_537->setMovie(movie7);
    ui->label_403->setMovie(movie7);
    ui->label_579->setMovie(movie7);
    ui->label_473->setMovie(movie7);
    movie7->start();
}

store::~store()
{
    delete ui;
}

void store::jump(int floor)
{
    if (floor == 2){
        this->hide();
        emit store_to_two();
    }
    else if (floor == 3){
        this->hide();
        emit store_to_three();
    }
}

void store::move(int direction)
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

void store::MeetDoor(int direction, int type, int index, QLabel *label)     //遇到门
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

void store::MeetKey(int direction, int type, int index, QLabel *label)
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

void store::MeetMonster(int direction, Monster &mon, QLabel *label)
{
    if (mon.get_alive()){
        if (hero.attack_monster(mon)){
            mon.update_alive();
            ui->life->setText(hero.get_life());
            ui->attack->setText(hero.get_attack());
            ui->defense->setText(hero.get_defense());
            ui->level3->setText(hero.get_level());
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

void store::showfloor2_2()
{
    this->show();
    ui->level3->setText(hero.get_level());         //等级
    ui->level3->setStyleSheet("color:white;");
    QFont font ( "Microsoft YaHei", 27, 75);
    ui->level3->setFont(font);
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

void store::keyPressEvent(QKeyEvent*event)
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
            if (ui->character->y() == 250 || ui->character->y() == 400)
                move(3);
            else if (ui->character->y() == 50){      //剑
                if (!sword){
                    sword = true;
                    ui->label_607->hide();
                    hero.raise_attack(10);
                    ui->attack->setText(hero.get_attack());
                }
                else
                    move(3);
            }
            else if (ui->character->y() == 100)     //遇怪
                MeetMonster(3, mon2, ui->label_591);
            else if (ui->character->y() == 150)     //黄钥匙
            {    MeetKey(3, 1, 3, ui->label_588);
                ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->y() == 550){    //下到2楼
                QPixmap down(DOWN);
                ui->character->setPixmap(down);
                jump(2);
            }
            break;

        case 3:
            if (ui->character->y() == 250 || ui->character->y() == 400 || ui->character->y() == 500)
                move(3);
            else if (ui->character->y() == 50)      //遇怪
                MeetMonster(3, mon1, ui->label_585);
            else if (ui->character->y() == 100)     //黄钥匙
             {   MeetKey(3, 1, 2, ui->label_685);
                ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 4:
            if (ui->character->y() == 300 || ui->character->y() == 400 || ui->character->y() == 500)
                move(3);
            break;

        case 5:
            if (ui->character->y() == 300 || ui->character->y() == 400 || ui->character->y() == 500)
                move(3);
            break;

        case 6:
            if (ui->character->y() == 100 || ui->character->y() == 200 || ui->character->y() == 300)
                move(3);
            break;

        case 7:
            if (ui->character->y() == 100 || ui->character->y() == 300)
                move(3);
            else if (ui->character->y() == 200)     //遇怪
                MeetMonster(3, mon5, ui->label_625);
            break;

        case 8:
            if (ui->character->y() == 350)
                move(3);
            else if (ui->character->y() == 450)     //遇怪
                MeetMonster(3, mon15, ui->label_424);
            else if (ui->character->y() == 500){        //蓝宝石
                if (bluedia){
                    bluedia = false;
                    ui->label_407->hide();
                    hero.raise_defense(3);
                    ui->defense->setText(hero.get_defense());
                }
                else
                    move(3);
            }
            else if (ui->character->y() == 550){        //红宝石
                if (reddia){
                    reddia = false;
                    ui->label_391->hide();
                    hero.raise_attack(3);
                    ui->attack->setText(hero.get_attack());
                }
                else
                    move(3);
            }
            break;

        case 9:
            if (ui->character->y() == 350 || ui->character->y() == 450)
                move(3);
            else if (ui->character->y() == 500)     //遇怪
                MeetMonster(3, mon17, ui->label_403);
            else if (ui->character->y() == 550){        //蓝药水
                if (water){
                    water = false;
                    ui->label_392->hide();
                    hero.raise_life(500);
                    ui->life->setText(hero.get_life());
                }
                else
                    move(3);
            }
            break;

        case 10:
            if (ui->character->y() == 100)
                move(3);
            break;

        case 11:
            if (ui->character->y() == 100)
                move(3);
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
            if (ui->character->x() == 350)      //遇怪
                MeetMonster(2, mon2, ui->label_591);
            else if (ui->character->x() == 450)
                move(2);
            else if (ui->character->x() == 400)     //黄钥匙
            {    MeetKey(2, 1, 2, ui->label_685);
                ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 2:
            if (ui->character->x() == 600 || ui->character->x() == 750 || ui->character->x() == 850 || ui->character->x() == 400)
                move(2);
            else if (ui->character->x() == 350)     //黄钥匙
            {    MeetKey(2, 1, 3, ui->label_588);
               ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 3:
            if (ui->character->x() == 600 || ui->character->x() == 750 || ui->character->x() == 400)
                move(2);
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(2, mon6, ui->label_472);
            break;

        case 4:
            if (ui->character->x() == 650 || ui->character->x() == 750 || ui->character->x() == 400)
                move(2);
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(2, mon7, ui->label_473);
            break;

        case 5:
            if (ui->character->x() == 650 || ui->character->x() == 750 || ui->character->x() == 450 || ui->character->x() == 350)
                move(2);
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(2, mon12, ui->label_474);
            break;

        case 6:
            if (ui->character->x() == 350 || ui->character->x() == 750 || ui->character->x() == 650 || ui->character->x() == 850)
                move(2);
            break;

        case 7:
            if (ui->character->x() == 350 || ui->character->x() == 850)
                move(2);
            else if (ui->character->x() == 700)     //黄门
            {    MeetDoor(2, 1, 3, ui->label_670);
               ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 8:
            if (ui->character->x() == 550 || ui->character->x() == 850 || ui->character->x() == 700)
                move(2);
            break;

        case 9:
            if (ui->character->x() == 550 || ui->character->x() == 850)
                move(2);
            else if (ui->character->x() == 650){        //蓝宝石
                if (bluedia){
                    bluedia = false;
                    ui->label_407->hide();
                    hero.raise_defense(3);
                    ui->defense->setText(hero.get_defense());
                }
                else
                    move(2);
            }
            else if (ui->character->x() == 700)     //遇怪
                MeetMonster(2, mon17, ui->label_403);
            else if (ui->character->x() == 750)     //黄钥匙
            {    MeetKey(2, 1, 7, ui->label_705);
               ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 10:
            if (ui->character->x() == 400)
                move(2);
            else if (ui->character->x() == 650){        //红宝石
                if (reddia){
                    reddia = false;
                    ui->label_391->hide();
                    hero.raise_attack(3);
                    ui->attack->setText(hero.get_attack());
                }
                else
                    move(2);
            }
            else if (ui->character->x() == 700){        //蓝药水
                if (water){
                    water = false;
                    ui->label_392->hide();
                    hero.raise_life(500);
                    ui->life->setText(hero.get_life());
                }
                else
                    move(2);
            }
            else if (ui->character->x() == 750)     //黄钥匙
            {    MeetKey(2, 1, 8, ui->label_700);
               ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->x() == 850)     //上到3楼
            {
                QPixmap down(DOWN);
                ui->character->setPixmap(down);
                jump(3);
            }
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
            if (ui->character->y() == 150 || ui->character->y() == 250 || ui->character->y() == 400)
                move(4);
            else if (ui->character->y() == 50)      //遇怪
                MeetMonster(4, mon1, ui->label_585);
            else if (ui->character->y() == 100)     //黄钥匙
            {    MeetKey(4, 1, 2, ui->label_685);
                ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 2:
            if (ui->character->y() == 100 || ui->character->y() == 250 || ui->character->y() == 400 || ui->character->y() == 500)
                move(4);
            else if (ui->character->y() == 50)      //黄钥匙
           {     MeetKey(4, 1, 1, ui->label_674);
                ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 3:
            if (ui->character->y() == 400 || ui->character->y() == 500)
                move(4);
            else if (ui->character->y() == 300)     //遇怪
                MeetMonster(4, mon9, ui->label_531);
            break;

        case 4:
            if (ui->character->y() == 400 || ui->character->y() == 500)
                move(4);
            else if (ui->character->y() == 300)     //遇怪
                MeetMonster(4, mon10, ui->label_525);
            break;

        case 5:
            if (ui->character->y() == 100 || ui->character->y() == 200)
                move(4);
            else if (ui->character->y() == 300)     //遇怪
                MeetMonster(4, mon11, ui->label_518);
            break;

        case 6:
            if (ui->character->y() == 100 || ui->character->y() == 200 || ui->character->y() == 300)
                move(4);
            break;

        case 7:
            if (ui->character->y() == 350 || ui->character->y() == 450)
                move(4);
            else if (ui->character->y() == 500)     //遇怪
                MeetMonster(4, mon17, ui->label_403);
            else if (ui->character->y() == 550){        //蓝药水
                if (water){
                    water = false;
                    ui->label_392->hide();
                    hero.raise_life(500);
                    ui->life->setText(hero.get_life());
                }
                else
                    move(4);
            }
            break;

        case 8:
            if (ui->character->y() == 350)
                move(4);
            else if (ui->character->y() == 450)     //遇怪
                MeetMonster(4, mon16, ui->label_431);
            else if (ui->character->y() == 500)     //黄钥匙
             {   MeetKey(4, 1, 7, ui->label_705);
                ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->y() == 550)     //黄钥匙
           {     MeetKey(4, 1, 8, ui->label_700);
               ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 9:
            if (ui->character->y() == 100)      //遇怪
                MeetMonster(4, mon3, ui->label_579);
            break;

        case 10:
            if (ui->character->y() == 100)
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
            if (ui->character->x() == 350){     //剑
                if (!sword){
                    sword = true;
                    ui->label_607->hide();
                    hero.raise_attack(10);
                    ui->attack->setText(hero.get_attack());
                }
                else
                    move(1);
            }
            else if (ui->character->x() == 400)     //遇怪
                MeetMonster(1, mon1, ui->label_585);
            else if (ui->character->x() == 450)     //黄钥匙
           {     MeetKey(1, 1, 1, ui->label_674);
               ui->yellowkey->setText(hero.get_yellowkey());}
            //else if (ui->character->x() == 600)     //商店
            break;

        case 3:
            if (ui->character->x() == 600 || ui->character->x() == 750 || ui->character->x() == 850)
                move(1);
            else if (ui->character->x() == 350)     //遇怪
                MeetMonster(1, mon2, ui->label_591);
            else if (ui->character->x() == 400)     //遇黄钥匙
           {     MeetKey(1, 1, 2, ui->label_685);
               ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 4:
            if (ui->character->x() == 750 || ui->character->x() == 850)
                move(1);
            else if (ui->character->x() == 400)      //遇怪
                MeetMonster(1, mon4, ui->label_641);
            else if (ui->character->x() == 600)     //黄门
           {     MeetDoor(1, 1, 1, ui->label_672);
               ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        case 5:
            if (ui->character->x() == 650)
                move(1);
            else if (ui->character->x() == 400) //黄门
           {     MeetDoor(1, 1, 2, ui->label_648);
               ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->x() == 750)     //黄钥匙
            {    MeetKey(1, 1, 4, ui->label_697);
               ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(1, mon6, ui->label_472);
            break;

        case 6:
            if (ui->character->x() == 650 || ui->character->x() == 350 || ui->character->x() == 450)
                move(1);
            else if (ui->character->x() == 750)     //黄钥匙
           {     MeetKey(1, 1, 5, ui->label_686);
             ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(1, mon7, ui->label_473);
            break;

        case 7:
            if (ui->character->x() == 650)
                move(1);
            else if (ui->character->x() == 350)     //遇怪
                MeetMonster(1, mon8, ui->label_653);
            else if (ui->character->x() == 750)     //黄钥匙
          {      MeetKey(1, 1, 6, ui->label_688);
                ui->yellowkey->setText(hero.get_yellowkey());}
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(1, mon12, ui->label_474);
            break;

        case 8:
            if (ui->character->x() == 850 || ui->character->x() == 700)
                move(1);
            else if (ui->character->x() == 350)     //遇怪
                MeetMonster(1, mon13, ui->label_649);
            break;

        case 9:
            if (ui->character->x() == 850 || ui->character->x() == 700 || ui->character->x() == 550)
                move(1);
            break;

        case 10:
            if (ui->character->x() == 850 || ui->character->x() == 700)
                move(1);
            else if (ui->character->x() == 550)     //遇怪
                MeetMonster(1, mon14, ui->label_537);
            else if (ui->character->x() == 650)     //遇怪
                MeetMonster(1, mon15, ui->label_424);
            else if (ui->character->x() == 750)     //遇怪
                MeetMonster(1, mon16, ui->label_431);
            break;

        case 11:
            if (ui->character->x() == 400)
                move(1);
            else if (ui->character->x() == 650){        //蓝宝石
                if (bluedia){
                    bluedia = false;
                    ui->label_407->hide();
                    hero.raise_defense(3);
                    ui->defense->setText(hero.get_defense());
                }
                else
                    move(1);
            }
            else if (ui->character->x() == 700)     //遇怪
                MeetMonster(1, mon17, ui->label_403);
            else if (ui->character->x() == 750)     //黄钥匙
          {      MeetKey(1, 1, 7, ui->label_705);
               ui->yellowkey->setText(hero.get_yellowkey());}
            break;

        default:
            break;
        }
    }

    else QWidget::keyPressEvent(event);
}
