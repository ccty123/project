#include "gameboundary4.h"
#include "ui_gameboundary4.h"

gameboundary4::gameboundary4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameboundary4)
{
    ui->setupUi(this);
}

gameboundary4::~gameboundary4()
{
    delete ui;

    for (int i = 1; i <= 6; i++)
        door[i] = true;
    for (int i = 1; i <= 4; i++)
        key[i] = true;
    for (int i = 1; i <= 4; i++)
        dia[i] = true;
    for (int i = 1; i <= 4; i++)
        water[i] = true;
    tool = true;
    all_key = true;

    mon1.initial(125,50,25,7,10);
    mon2.initial(125,50,25,7,10);
    mon3.initial(125,50,25,7,10);
    mon4.initial(125,50,25,7,10);
    mon5.initial(150,65,30,8,10);
    mon6.initial(150,40,20,6,8);
    mon7.initial(125,50,25,7,10);
    mon8.initial(150,40,20,6,8);
    mon9.initial(300,75,45,10,13);
    mon10.initial(150,40,20,6,8);
    mon11.initial(150,65,30,8,10);
    mon12.initial(150,40,20,6,8);
    mon13.initial(100,20,5,3,3);
    mon14.initial(110,25,5,4,5);
    mon15.initial(200,35,10,5,5);
    mon16.initial(200,35,10,5,5);
    mon17.initial(300,75,45,10,13);
    mon18.initial(450,150,90,19,22);
    mon19.initial(100,20,5,3,3);
    mon20.initial(100,20,5,3,3);
    mon21.initial(100,20,5,3,3);
}

void gameboundary4::jump(int floor)
{
    if (floor == 3){
        this->hide();
        emit four_to_three();
    }
}

void gameboundary4::move(int direction)
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

void gameboundary4::MeetDoor(int direction, int type, int index, QLabel *label)     //遇到门
{
    if (door[index])
    {
        if(hero.key_number(type)){
            hero.lose_key(type);
            label->hide();
            door[index] = false;
            switch (type) {
                case 1: ui->yellowkey->setText(hero.get_yellowkey());break;
                case 2: ui->bluekey->setText(hero.get_bluekey()); break;
                case 3: ui->redkey->setText(hero.get_redkey()); break;
            }
        }
    }
    else
        move(direction);
}

void gameboundary4::MeetKey(int direction, int type, int index, QLabel *label)
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

void gameboundary4::MeetWater(int direction, int type, int index, QLabel *label)
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

void gameboundary4::MeetMonster(int direction, Monster &mon, QLabel *label)
{
    if (mon.get_alive()){
        if (hero.attack_monster(mon)){
            mon.update_alive();
            ui->life->setText(hero.get_life());
            ui->attack->setText(hero.get_attack());
            ui->defense->setText(hero.get_defense());
            ui->level->setText(hero.get_level());
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

void gameboundary4::MeetDia(int direction, int type, int index, QLabel *label)
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

void gameboundary4::showfloor4()
{
    this->show();
    ui->level->setText(hero.get_level());         //等级
    ui->level->setStyleSheet("color:white;");
    QFont font ( "Microsoft YaHei", 27, 75);
    ui->level->setFont(font);
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

void gameboundary4::keyPressEvent(QKeyEvent*event)
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
            if (ui->character->y() == 200 || ui->character->y() == 500)
                move(3);
            else if (ui->character->y() == 550)     //下到3楼
            {
                QPixmap down(DOWN);
                ui->character->setPixmap(down);
                jump(3);
            }
            break;

        case 3:
            if (ui->character->y() == 550 || ui->character->y() == 200)
                move(3);
            break;

        case 4:
            if (ui->character->y() == 300 || ui->character->y() == 550)
                move(3);
            break;

        case 5:
            if (ui->character->y() == 300 || ui->character->y() == 550)
                move(3);
            break;

        case 6:
            if (ui->character->y() == 300 || ui->character->y() == 550)
                move(3);
            else if (ui->character->y() == 50)      //蓝药水
                MeetWater(3, 2, 2, ui->label_731);
            else if (ui->character->y() == 100)     //遇怪
                MeetMonster(3, mon3, ui->label_767);
            else if (ui->character->y() == 150)     //  遇怪
                MeetMonster(3, mon6, ui->label_803);
            else if (ui->character->y() == 200)     //盾牌
            {
                if (tool){
                    tool = false;
                    ui->label_747->hide();
                    hero.raise_defense(10);
                }
                else
                    move(3);
            }
            break;

        case 7:
            if (ui->character->y() == 100 || ui->character->y() == 300 || ui->character->y() == 400)
                move(3);
            else if (ui->character->y() == 50)      //遇怪
                MeetMonster(3, mon1, ui->label_768);
            break;

        case 8:
            if (ui->character->y() == 50 || ui->character->y() == 100 || ui->character->y() == 300 || ui->character->y() == 400)
                move(3);
            break;

        case 9:
            if (ui->character->y() == 100 || ui->character->y() == 50 || ui->character->y() == 200 || ui->character->y() == 250 || ui->character->y() == 300 || ui->character->y() == 400)
                move(3);
            else if (ui->character->y() == 500)     //蓝宝石
                MeetDia(3, 2, 4, ui->label_807);
            break;

        case 10:
            if (ui->character->y() == 250 || ui->character->y() == 100 || ui->character->y() == 300 || ui->character->y() == 350)
                move(3);
            else if (ui->character->y() == 50)      //遇怪
                MeetMonster(3, mon2, ui->label_770);
            else if (ui->character->y() == 200)     //遇怪
                MeetMonster(3, mon9, ui->label_647);
            else if (ui->character->y() == 400)     //遇怪
                MeetMonster(3, mon17, ui->label_781);
            else if (ui->character->y() == 500)     //黄门
                MeetDoor(3, 1, 6, ui->label_778);
            break;

        case 11:
            if (ui->character->y() == 250 || ui->character->y() == 300 || ui->character->y() == 350)
                move(3);
            else if (ui->character->y() == 50)      //黄钥匙
                MeetKey(3, 1, 1, ui->label_721);
            else if (ui->character->y() == 100)     //遇怪
                MeetMonster(3, mon4, ui->label_769);
            else if (ui->character->y() == 400)     //遇怪
                MeetMonster(3, mon18, ui->label_805);
            break;

        default:
            break;
        }
    }

    else  if ((event->key()==Qt::Key_S)||(event->key()==Qt::Key_Down))      //向下移动
    {
        QPixmap down(DOWN);
        ui->character->setPixmap(down);
        switch(ui->character->y() / 50)
        {
        case 1:
            if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 650 || ui->character->x() == 700 || ui->character->x() == 750)
                move(2);
            else if (ui->character->x() == 550)     //遇怪
                MeetMonster(2, mon3, ui->label_767);
            else if (ui->character->x() == 800)     //遇怪
                MeetMonster(2, mon4, ui->label_769);
            else if (ui->character->x() == 850)     //黄钥匙
                MeetKey(2, 1, 3, ui->label_771);
            break;

        case 2:
            if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 600 || ui->character->x() == 750)
                move(2);
            else if (ui->character->x() == 550)     //遇怪
                MeetMonster(2, mon6, ui->label_803);
            break;

        case 3:
            if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 750)
                move(2);
            else if (ui->character->x() == 550)         //盾牌
            {
                if (tool){
                    tool = false;
                    hero.raise_defense(30);
                    ui->label_747->hide();
                }
                else
                    move(2);
            }
            else if (ui->character->x() == 600)     //遇怪
                MeetMonster(2, mon8, ui->label_804);
            break;

        case 4:
            if (ui->character->x() == 450 || ui->character->x() == 800 || ui->character->x() == 700 || ui->character->x() == 750)
                move(2);
            else if (ui->character->x() == 350)     //遇怪
                MeetMonster(2, mon11, ui->label_802);
            break;

        case 5:
            if (ui->character->x() == 800 || ui->character->x() == 450 || ui->character->x() == 850 || ui->character->x() == 700 || ui->character->x() == 750)
                move(2);
            else if (ui->character->x() == 350)     //红宝石
                MeetDia(2, 1, 2, ui->label_518);
            break;

        case 6:
            if (ui->character->x() == 500 || ui->character->x() == 750 || ui->character->x() == 800 || ui->character->x() == 850)
                move(2);
            else if (ui->character->x() == 350)     //蓝宝石
                MeetDia(2, 2, 3, ui->label_779);
            break;

        case 7:
            if (ui->character->x() == 350 || ui->character->x() == 500 || ui->character->x() == 850)
                move(2);
            else if (ui->character->x() == 750)     //遇怪
                MeetMonster(2, mon17, ui->label_781);
            else if (ui->character->x() == 800)     //遇怪
                MeetMonster(2, mon18, ui->label_805);
            break;

        case 8:
            if (ui->character->x() == 500)
                move(2);
            else if (ui->character->x() == 600)     //黄门
                MeetDoor(2, 1, 3, ui->label_775);
            else if (ui->character->x() == 700)     //蓝门
                MeetDoor(2, 2, 4, ui->label_806);
            else if (ui->character->x() == 800)     //黄门
                MeetDoor(2, 1, 5, ui->label_774);
            break;

        case 9:
            if (ui->character->x() == 500||ui->character->x() == 800)
                move(2);
            else if (ui->character->x() == 600)     //遇怪
                MeetMonster(2, mon20, ui->label_783);
            else if (ui->character->x() == 700)     //蓝宝石
                MeetDia(2, 2, 4, ui->label_807);
            break;

        case 10:
            if (ui->character->x() == 400||ui->character->x() == 500||ui->character->x() == 600)
                move(2);
            else if (ui->character->x() == 350)     //下到3楼
                jump(3);
            else if (ui->character->x() == 700)     //黄钥匙
                MeetKey(2, 1, 4, ui->label_772);
            else if (ui->character->x() == 800)     //蓝药水
                //MeetWater(2, 2, 3, ui->label_764);
            {
                if (water[3]){
                    water[3] = false;
                    hero.raise_life(500);
                    ui->label_764->hide();
                }
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
            if (ui->character->y() == 200 || ui->character->y() == 500)
                move(4);
            else if (ui->character->y() == 400)     //升级
            {
                return;
            }
            break;

        case 2:
            if (ui->character->y() == 200 || ui->character->y() == 550)
                move(4);
            break;

        case 3:
            if (ui->character->y() == 300 || ui->character->y() == 550)
                move(4);
            break;

        case 4:
            if (ui->character->y() == 300 || ui->character->y() == 550)
                move(4);
            break;

        case 5:
            if (ui->character->y() == 100 || ui->character->y() == 150 || ui->character->y() == 550)
                move(4);
            else if (ui->character->y() == 50)      //遇怪
                MeetMonster(4, mon1, ui->label_768);
            else if (ui->character->y() == 200)      //遇怪
                MeetMonster(4, mon8, ui->label_804);
            else if (ui->character->y() == 300)      //遇怪
                MeetMonster(4, mon13, ui->label_785);
            break;

        case 6:
            if (ui->character->y() == 100 || ui->character->y() == 50 || ui->character->y() == 400)
                move(4);
            else if (ui->character->y() == 300)      //遇怪
                MeetMonster(4, mon14, ui->label_595);
            break;

        case 7:
            if (ui->character->y() == 100 || ui->character->y() == 50 || ui->character->y() == 300 || ui->character->y() == 400)
                move(4);
            break;

        case 8:
            if (ui->character->y() == 100 || ui->character->y() == 250 || ui->character->y() == 300)
                move(4);
            else if (ui->character->y() == 50)      //遇怪
                MeetMonster(4, mon2, ui->label_770);
            else if (ui->character->y() == 200)      //遇怪
                MeetMonster(4, mon9, ui->label_647);
            else if (ui->character->y() == 400)      //遇怪
                MeetMonster(4, mon17, ui->label_781);
            else if (ui->character->y() == 500  )   //黄门
                MeetDoor(4, 1, 6, ui->label_778);
            break;

        case 9:
            if (ui->character->y() == 350 || ui->character->y() == 250 || ui->character->y() == 300 || ui->character->y() == 500)
                move(4);
            else if (ui->character->y() == 50)      //黄钥匙
                MeetKey(4, 1, 1, ui->label_721);
            else if (ui->character->y() == 100)     //遇怪
                MeetMonster(4, mon4, ui->label_769);
            else if (ui->character->y() == 200)     //遇怪
                MeetMonster(4, mon10, ui->label_634);
            else if (ui->character->y() == 400)     //遇怪
                MeetMonster(4, mon18, ui->label_805);
            break;

        case 10:
            if (ui->character->y() == 350 || ui->character->y() == 400 || ui->character->y() == 300)
                move(4);
            else if (ui->character->y() == 50)      //蓝钥匙
                MeetKey(4, 2, 2, ui->label_726);
            else if (ui->character->y() == 100)     //黄钥匙
                MeetKey(4, 1, 3, ui->label_771);
            else if (ui->character->y() == 200)     //商人
            {
                return;
            }
            else if (ui->character->y() == 250)     //遇怪
                MeetMonster(4, mon12, ui->label_780);
            break;

        default:
            break;
        }
    }

    else  if ((event->key()==Qt::Key_W)||(event->key()==Qt::Key_Up))        //向上移动
    {
        QPixmap up(UP);
        ui->character->setPixmap(up);
        switch(ui->character->y() / 50)
        {
        case 1:
            break;

        case 2:
            if (ui->character->x() == 650 || ui->character->x() == 700)
                move(1);
            else if (ui->character->x() == 350)     //万能钥匙
            {
                if (all_key){
                    hero.get_mainkey();
                    ui->label_504->hide();
                    all_key = false;
                }
                else
                    move(1);
            }
            else if (ui->character->x() == 450)     //红药水
                MeetWater(1, 1, 1, ui->label_555);
            else if (ui->character->x() == 550)     //蓝药水
                MeetWater(1, 2, 2, ui->label_731);
            else if (ui->character->x() == 600)     //遇怪
                MeetMonster(1, mon1, ui->label_768);
            else if (ui->character->x() == 750)     //遇怪
                MeetMonster(1, mon2, ui->label_770);
            else if (ui->character->x() == 800)     //黄钥匙
                MeetKey(1, 1, 1, ui->label_721);
            else if (ui->character->x() == 850)     //蓝钥匙
                MeetKey(1, 2, 2, ui->label_726);
            break;

        case 3:
            if (ui->character->x() == 350 || ui->character->x() == 600 || ui->character->x() == 750)
                move(1);
            else if (ui->character->x() == 450)     //红宝石
                MeetDia(1, 1, 1, ui->label_766);
            else if (ui->character->x() == 550)     //遇怪
                MeetMonster(1, mon3, ui->label_767);
            break;

        case 4:
            if (ui->character->x() == 450 || ui->character->x() == 600)
                move(1);
            else if (ui->character->x() == 350)     //遇怪
                MeetMonster(1, mon5, ui->label_801);
            else if (ui->character->x() == 550)     //遇怪
                MeetMonster(1, mon6, ui->label_803);
            else if (ui->character->x() == 750)     //黄门
                MeetDoor(1, 1, 1, ui->label_773);
            break;

        case 5:
            if (ui->character->x() == 350 || ui->character->x() == 700)
                move(1);
            else if (ui->character->x() == 450)     //遇怪
                MeetMonster(1, mon7, ui->label_549);
            else if (ui->character->x() == 750)         //遇怪
                MeetMonster(1, mon9, ui->label_647);
            else if (ui->character->x() == 800)         //遇怪
                MeetMonster(1, mon10, ui->label_634);
            break;

        case 6:
            if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 700 || ui->character->x() == 750 || ui->character->x() == 800)
                move(1);
            else if (ui->character->x() == 850)     //遇怪
                MeetMonster(1, mon12, ui->label_780);
            break;

        case 7:
            if (ui->character->x() == 350 || ui->character->x() == 500 || ui->character->x() == 750 || ui->character->x() == 800 || ui->character->x() == 850)
                move(1);
            break;

        case 8:
            if (ui->character->x() == 350 || ui->character->x() == 750 || ui->character->x() == 800 || ui->character->x() == 850)
                move(1);
            else if (ui->character->x() == 500)     //遇怪
                MeetMonster(1, mon15, ui->label_472);
            break;

        case 9:
            if (ui->character->x() == 600 || ui->character->x() == 700)
                move(1);
            else if (ui->character->x() == 500)     //遇怪
                MeetMonster(1, mon16, ui->label_782);
            else if (ui->character->x() == 800)     //遇怪
                MeetMonster(1, mon18, ui->label_805);
            break;

        case 10:
            if (ui->character->x() == 500)
                move(1);
            else if (ui->character->x() == 600)     //黄门
                MeetDoor(1, 1, 3, ui->label_775);
            else if (ui->character->x() == 700)     //蓝门
                MeetDoor(1, 2, 4, ui->label_806);
            else if (ui->character->x() == 800)     //黄门
                MeetDoor(1, 1, 5, ui->label_774);
            break;

        case 11:
            if (ui->character->x() == 400 || ui->character->x() == 500 || ui->character->x() == 800)
                move(1);
            else if (ui->character->x() == 600)     //遇怪
                MeetMonster(1, mon20, ui->label_783);
            else if (ui->character->x() == 700)     //蓝宝石
                MeetDia(1, 2, 4, ui->label_807);
            break;

        default:
            break;
        }
    }

    else QWidget::keyPressEvent(event);
}
