#include "gameboundary2.h"
#include "ui_gameboundary2.h"

gameboundary2::gameboundary2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameboundary2)
{
    ui->setupUi(this);

    for (int i = 1; i <= 9; i++)
        door[i] = true;
    for (int i = 1; i <= 11; i++)
        key[i] = true;
    for (int i = 1; i <= 7; i++)
        water[i] = true;
    for (int i = 1; i <= 8; i++)
        dia[i] = true;
    irondoor = true;
    npc[1] = true;
    npc[2] = true;

    mon1.initial(900, 750, 650, 70, 77);
    mon2.initial(850, 350, 200, 40, 45);
    mon3.initial(850, 350, 200, 40, 45);

    QMovie* movie19 = new QMovie(MON19);
    ui->guai_2->setMovie(movie19);
    ui->guai_3->setMovie(movie19);
    movie19->start();

    QMovie* movie20 = new QMovie(MON20);
    ui->guai_1->setMovie(movie20);
    movie20->start();

    QMovie* npc1 = new QMovie(NPC1);
    ui->label_386->setMovie(npc1);
    npc1->start();

    QMovie* npc2 = new QMovie(NPC2);
    ui->label_387->setMovie(npc2);
    npc2->start();
}

gameboundary2::~gameboundary2()
{
    delete ui;
}

void gameboundary2::jump(int floor)
{
    if (floor == 1){
        this->hide();
        emit two_to_one();
    }
    else if (floor == -1){
        this->hide();
        emit two_to_store();
    }
}

void gameboundary2::move(int direction)
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

void gameboundary2::MeetDoor(int direction, int type, int index, QLabel *label)     //遇到门
{
    if (door[index])
    {
        if(hero.key_number(type)){
            hero.lose_key(type);
            label->hide();
            door[index] = false;
            switch (type) {
                case 1: ui->yellowkey2->setText(hero.get_yellowkey());  break;
                case 2: ui->bluekey2->setText(hero.get_bluekey()); break;
                case 3: ui->redkey2->setText(hero.get_redkey()); break;
        }
        }
    }
    else
        move(direction);
}

void gameboundary2::MeetKey(int direction, int type, int index, QLabel *label)
{
    if (key[index])
    {
        hero.gain_key(type);
        key[index] = false;
        label->hide();
        switch (type) {
            case 1: ui->yellowkey2->setText(hero.get_yellowkey());  break;
            case 2: ui->bluekey2->setText(hero.get_bluekey()); break;
            case 3: ui->redkey2->setText(hero.get_redkey()); break;
        }
    }
    else
        move(direction);
}

void gameboundary2::MeetWater(int direction, int type, int index, QLabel *label)
{
    if (water[index])
    {
        water[index] = false;
        label->hide();
        (type == 1) ? hero.raise_life(200) : hero.raise_life(500);
         ui->life2->setText(hero.get_life());
    }
    else
        move(direction);
}

void gameboundary2::MeetMonster(int direction, Monster &mon, QLabel *label)
{
    if (mon.get_alive()){
        if (hero.attack_monster(mon)){
            mon.update_alive();
            ui->life2->setText(hero.get_life());
            ui->attack2->setText(hero.get_attack());
            ui->defense2->setText(hero.get_defense());
            ui->level2->setText(hero.get_level());
            ui->exp2->setText(hero.get_exp());
            ui->money2->setText(hero.get_money());
            label->hide();
        }
        else
            return;
    }
    else
        move(direction);
}

void gameboundary2::MeetDia(int direction, int type, int index, QLabel *label)
{
    if (dia[index])
    {
        dia[index] = false;
        label->hide();
        if(type==1)  {  hero.raise_attack(3);ui->attack2->setText(hero.get_attack());}
        else   { hero.raise_defense(3); ui->defense2->setText(hero.get_defense());}
     //   type == 1 ? (hero.raise_attack(3);ui->attack2->setText(hero.get_attack());):( hero.raise_defense(3); ui->defense2->setText(hero.get_defense()););
    }
    else
        move(direction);
}

void gameboundary2::on_up_clicked()     //向上移动
{
    QPixmap up(UP);
    ui->character->setPixmap(up);
    switch (ui->character->y() / 50)
    {
    case 1:
        break;

    case 2:
        if (ui->character->x() == 350)      //下到1楼
        {
            QPixmap down(DOWN);
            ui->character->setPixmap(down);
            jump(1);
        }
        else if (ui->character->x() == 450 || ui->character->x() == 550)
            move(1);
        else if (ui->character->x() == 650)         //红宝石
            MeetDia(1, 1, 1, ui->label_376);
        else if (ui->character->x() == 700)         //蓝宝石
            MeetDia(1, 2, 2, ui->label_375);
        else if (ui->character->x() == 750)         //黄钥匙
         {   MeetKey(1, 1, 1, ui->label_372);
             ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 800)         //红钥匙
          {  MeetKey(1, 3, 2, ui->label_380);
             ui->redkey2->setText(hero.get_bluekey());}
        break;

    case 3:
        if (ui->character->x() == 350)
            move(1);
        else if (ui->character->x() == 450)     //蓝宝石
            MeetDia(1, 2, 3, ui->label_371);
        else if (ui->character->x() == 550)     //蓝药水
            MeetWater(1, 2, 1, ui->label_361);
        else if (ui->character->x() == 650)     //红宝石
            MeetDia(1, 1, 4, ui->label_377);
        else if (ui->character->x() == 700)     //蓝宝石
            MeetDia(1, 2, 5, ui->label_373);
        else if (ui->character->x() == 750)         //黄钥匙
          {  MeetKey(1, 1, 3, ui->label_370);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 800)         //蓝钥匙
            MeetKey(1, 2, 4, ui->label_381);
        break;

    case 4:
        if (ui->character->x() == 350)
            move(1);
        else if (ui->character->x() == 450)         //黄钥匙
         {   MeetKey(1, 1, 5, ui->label_364);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 550)         //黄钥匙
         {   MeetKey(1, 1, 6, ui->label_362);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 800)         //遇怪
            MeetMonster(1, mon2, ui->guai_2);
        break;

    case 5:
        if (ui->character->x() == 350)
            move(1);
        else if (ui->character->x() == 450)         //黄钥匙
        {    MeetKey(1, 1, 8, ui->label_366);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 550)         //黄钥匙
         {   MeetKey(1, 1, 9, ui->label_365);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 800)         //黄门
        {    MeetDoor(1, 1, 1, ui->door);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        break;

    case 6:
        if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 600 || ui->character->x() == 750)
            move(1);
        break;

    case 7:
        if (ui->character->x() == 350)
            move(1);
        else if (ui->character->x() == 450)         //黄门
         {   MeetDoor(1, 1, 3, ui->door_5);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 600)         //黄门
         {   MeetDoor(1, 1, 4, ui->door_6);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 750)         //黄门
         {   MeetDoor(1, 1, 5, ui->door_2);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        break;

    case 8:
        if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 600 || ui->character->x() == 700 || ui->character->x() == 800)
            move(1);
        break;

    case 9:
        if (ui->character->x() == 350)
            move(1);
        else if (ui->character->x() == 450)         //黄门
        {    MeetDoor(1, 1, 6, ui->door_4);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 600)         //蓝门
            MeetDoor(1, 2, 7, ui->label_384);
        else if (ui->character->x() == 700){        //铁栏杆
            if (door[8])
                ui->label_382->hide();
            else
                move(1);
        }

        else if (ui->character->x() == 800){        //铁栏杆
            if (door[9])
                ui->label_383->hide();
            else
                move(1);
        }
        break;

    case 10:
        if (ui->character->x() == 350 || ui->character->x() == 700 || ui->character->x() == 800)
            move(1);
        else if (ui->character->x() == 450)         //黄钥匙
            MeetKey(1, 1, 10, ui->label_368);
        else if (ui->character->x() == 550)         //蓝药水
            MeetWater(1, 2, 2, ui->label_358);
        else if (ui->character->x() == 600)         //红药水
            MeetWater(1, 1, 3, ui->label_355);
        break;

    case 11:
        if (ui->character->x() == 450)
            move(1);
        else if (ui->character->x() == 550)         //蓝药水
            MeetWater(1, 2, 4, ui->label_359);
        else if (ui->character->x() == 600)         //红药水
            MeetWater(1, 1, 5, ui->label_357);
        break;

    default:
        break;
    }
}

void gameboundary2::on_down_clicked()       //向下移动
{
    QPixmap down(DOWN);
    ui->character->setPixmap(down);
    switch (ui->character->y() / 50)
    {
    case 1:
        if (ui->character->x() == 450)      //蓝宝石
            MeetDia(2, 2, 3, ui->label_371);
        else if (ui->character->x() == 550)     //蓝药水
            MeetWater(2, 2, 1, ui->label_361);
        else if (ui->character->x() == 650)     //红宝石
            MeetDia(2, 1, 4, ui->label_377);
        else if (ui->character->x() == 700)     //蓝宝石
            MeetDia(2, 2, 5, ui->label_373);
        else if (ui->character->x() == 750)     //黄钥匙
         {   MeetKey(2, 1, 3, ui->label_370);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 800)     //蓝钥匙
            MeetKey(2, 2, 4, ui->label_381);
        break;

    case 2:
        if (ui->character->x() == 350 || ui->character->x() == 800)
            move(2);
        else if (ui->character->x() == 450)     //黄钥匙
        {    MeetKey(2, 1, 5, ui->label_364);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 550)     //黄钥匙
        {    MeetKey(2, 1, 6, ui->label_362);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 750)     //黄钥匙
        {    MeetKey(2, 1, 7, ui->label_369);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 650)     //红宝石
            MeetDia(2, 1, 5, ui->label_378);
        else if (ui->character->x() == 700)     //蓝宝石
            MeetDia(2, 2, 6, ui->label_374);
        break;

    case 3:
        if (ui->character->x() == 350 || ui->character->x() == 800)
            move(2);
        else if (ui->character->x() == 450)     //黄钥匙
        {    MeetKey(2, 1, 8, ui->label_366);
           ui->yellowkey2->setText(hero.get_yellowkey());}
         else if (ui->character->x() == 550)     //黄钥匙
        {    MeetKey(2, 1, 9, ui->label_365);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        break;

    case 4:
        if (ui->character->x() == 350 || ui->character->x() == 800 || ui->character->x() == 450 || ui->character->x() == 550)
            move(2);
        break;

    case 5:
        if (ui->character->x() == 350)
            move(2);
        else if (ui->character->x() == 450)     //黄门
        {     MeetDoor(2, 1, 3, ui->door_5);
          ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 600)     //黄门
        {    MeetDoor(2, 1, 4, ui->door_6);
            ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 750)     //黄门
        {    MeetDoor(2, 1, 5, ui->door_2);
        ui->yellowkey2->setText(hero.get_yellowkey());}
        break;

    case 6:
        if (ui->character->x() == 350 || ui->character->x() == 450 || ui->character->x() == 600)
            move(2);
        if (ui->character->x() == 750)      //遇怪
            MeetMonster(2, mon3, ui->guai_3);
        break;

    case 7:
        if (ui->character->x() == 350)
            move(2);
        else if (ui->character->x() == 450)     //黄门
        {    MeetDoor(2, 1, 6, ui->door_4);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 600)     //蓝门
            MeetDoor(2, 2, 7, ui->label_384);
        else if (ui->character->x() == 700){    //栏杆
            if (door[8]){
                door[8] = false;
                ui->label_382->hide();
            }
            else
                move(2);
        }
        else if (ui->character->x() == 800){    //栏杆
            if (door[9]){
                door[9] = false;
                ui->label_383->hide();
            }
            else
                move(2);
        }
        break;

    case 8:
        if (ui->character->x() == 350 || ui->character->x() == 700 || ui->character->x() == 800)
            move(2);
        else if (ui->character->x() == 450)     //黄钥匙
         {   MeetKey(2, 1, 10, ui->label_368);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 600)     //红药水
            MeetWater(2, 1, 3, ui->label_355);
        break;

    case 9:
        if (ui->character->x() == 350 || ui->character->x() == 700 || ui->character->x() == 800)
            move(2);
        else if (ui->character->x() == 450)     //黄钥匙
        {    MeetKey(2, 1, 11, ui->label_367);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 550)     //蓝药水
            MeetWater(2, 2, 4, ui->label_359);
        else if (ui->character->x() == 600)     //红药水
            MeetWater(2, 1, 5, ui->label_357);
        break;

    case 10:
        if (ui->character->x() == 350)      //上到商店楼
            jump(-1);
        else if (ui->character->x() == 450)     //红宝石
            MeetDia(2, 1, 8, ui->label_379);
        else if (ui->character->x() == 550)     //蓝药水
            MeetWater(2, 2, 6, ui->label_360);
        else if (ui->character->x() == 600)     //红药水
            MeetWater(2, 1, 7, ui->label_356);
        /*else if (ui->character->x() == 700)     //npc1
            if (npc[1])
            {
                return;
            }
        else if (ui->character->x() == 800)     //npc2
            if (npc[2])
            {
                return;
            }
        */
        break;

    default:
        break;
    }
}

void gameboundary2::on_left_clicked()       //向左移动
{
    QPixmap left(LEFT);
    ui->character->setPixmap(left);
    switch ((ui->character->x() - 300) / 50)
    {
    case 1:
        break;

    case 2:
        if (ui->character->y() == 350)
            move(3);
        break;

    case 3:
        if (ui->character->y() == 350)
            move(3);
        break;

    case 4:
        if (ui->character->y() == 350 || ui->character->y() == 50)
            move(3);
        break;

    case 5:
        if (ui->character->y() == 350)
            move(3);
        else if (ui->character->y() == 50)      //遇怪
            MeetMonster(3, mon1, ui->guai_1);
        break;

    case 6:
        if (ui->character->y() == 250 || ui->character->y() == 350)
            move(3);
        else if (ui->character->y() == 450)     //蓝药水
            MeetWater(3, 2, 2, ui->label_358);
        else if (ui->character->y() == 500)     //蓝药水
            MeetWater(3, 2, 4, ui->label_359);
        else if (ui->character->y() == 550)     //蓝药水
            MeetWater(3, 2, 6, ui->label_360);
        break;

    case 7:
        if (ui->character->y() == 250)
            move(3);
        break;

    case 8:
        if (ui->character->y() == 250)
            move(3);
        else if (ui->character->y() == 50)      //红宝石
            MeetDia(3, 1, 1, ui->label_376);
        else if (ui->character->y() == 100)      //红宝石
            MeetDia(3, 1, 4, ui->label_377);
        else if (ui->character->y() == 150)      //红宝石
            MeetDia(3, 1, 6, ui->label_378);
        break;

    case 9:
        if (ui->character->y() == 350)
            move(3);
        else if (ui->character->y() == 250)      //黄门
       {     MeetDoor(3, 1, 2, ui->door_3);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 50)      //蓝宝石
            MeetDia(3, 2, 2, ui->label_375);
        else if (ui->character->y() == 100)      //蓝宝石
            MeetDia(3, 2, 5, ui->label_373);
        else if (ui->character->y() == 150)      //蓝宝石
            MeetDia(3, 2, 7, ui->label_374);
        break;

    case 10:
        if (ui->character->y() == 250 || ui->character->y() == 350)
            move(3);
        else if (ui->character->y() == 50)      //黄钥匙
       {     MeetKey(3, 1, 1, ui->label_372);
          ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 100)     //黄钥匙
       {     MeetKey(3, 1, 3, ui->label_370);
        ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 150)     //黄钥匙
       {     MeetKey(3, 1, 7, ui->label_369);
        ui->yellowkey2->setText(hero.get_yellowkey());}
        break;

    default:
        break;
    }
}

void gameboundary2::on_right_clicked()      //向右移动
{
    QPixmap right(RIGHT);
    ui->character->setPixmap(right);
    switch ((ui->character->x() - 300) / 50)
    {
    case 1:
        if (ui->character->y() == 350)    //铁门
        {
            if (irondoor)
            {
                if (hero.mainkey_num()){
                    irondoor = false;
                    ui->label_385->hide();
                }
            }
            else
                move(4);
        }
        break;

    case 2:
        if (ui->character->y() == 350)
            move(4);
        break;

    case 3:
        if (ui->character->y() == 350)
            move(4);
        else if (ui->character->y() == 50)      //遇怪
            MeetMonster(4, mon1, ui->guai_1);
        break;

    case 4:
        if (ui->character->y() == 50 || ui->character->y() == 350)
            move(4);
        break;

    case 5:
        if (ui->character->y() == 250 || ui->character->y() == 350)
            move(4);
        else if (ui->character->y() == 450)     //红药水
            MeetWater(4, 1, 3, ui->label_355);
        else if (ui->character->y() == 500)     //红药水
            MeetWater(4, 1, 5, ui->label_357);
        else if (ui->character->y() == 550)     //红药水
            MeetWater(4, 1, 7, ui->label_356);
        break;

    case 6:
        if (ui->character->y() == 250)
            move(4);
        break;

    case 7:
        if (ui->character->y() == 50)       //蓝宝石
            MeetDia(4, 2, 2, ui->label_375);
        else if (ui->character->y() == 100)     //蓝宝石
            MeetDia(4, 2, 5, ui->label_373);
        else if (ui->character->y() == 150)     //蓝宝石
            MeetDia(4, 2, 7, ui->label_374);
        else if (ui->character->y() == 250)     //黄门
        {    MeetDoor(4, 1, 2, ui->door_3);
        ui->yellowkey2->setText(hero.get_yellowkey());}
        break;

    case 8:
        if (ui->character->y() == 50)       //黄钥匙
       {     MeetKey(4, 1, 1, ui->label_372);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 100)       //黄钥匙
      {      MeetKey(4, 1, 3, ui->label_370);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 150)       //黄钥匙
       {     MeetKey(4, 1, 7, ui->label_369);
           ui->yellowkey2->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 250 || ui->character->y() == 350)
            move(4);
        break;

    case 9:
        if (ui->character->y() == 50)       //红钥匙
      {      MeetKey(4, 3, 2, ui->label_380);
            ui->redkey2->setText(hero.get_bluekey());}
        else if (ui->character->y() == 100)     //蓝钥匙
            MeetKey(4, 2, 4, ui->label_381);
        else if (ui->character->y() == 150 || ui->character->y() == 250 || ui->character->y() == 350)
            move(4);
        break;

    default:
        break;
    }
}


void gameboundary2::keyPressEvent(QKeyEvent* event)   //控制方向--键盘事件
{
    if ((event->key()==Qt::Key_A)||(event->key()==Qt::Key_Left))
        gameboundary2::on_left_clicked();
    else if ((event->key()==Qt::Key_S)||(event->key()==Qt::Key_Down))
        gameboundary2::on_down_clicked();
    else if ((event->key()==Qt::Key_D)||(event->key()==Qt::Key_Right))
        gameboundary2::on_right_clicked();
    else if ((event->key()==Qt::Key_W)||(event->key()==Qt::Key_Up))
        gameboundary2::on_up_clicked();
    else QWidget::keyPressEvent(event);
}

void gameboundary2::showfloor2()
{
    this->show();
    ui->level2->setText(hero.get_level());         //等级
    ui->level2->setStyleSheet("color:white;");
    QFont font ( "Microsoft YaHei", 27, 75);
    ui->level2->setFont(font);
    ui->yellowkey2->setText(hero.get_yellowkey());  //黄钥匙
    ui->yellowkey2->setStyleSheet("color:white;");
    QFont font1 ( "Microsoft YaHei", 27, 75);
    ui->yellowkey2->setFont(font1);
    ui->bluekey2->setText(hero.get_bluekey());      //蓝钥匙
    ui->bluekey2->setStyleSheet("color:white;");
    QFont font2 ( "Microsoft YaHei", 27, 75);
    ui->bluekey2->setFont(font2);
    ui->redkey2->setText(hero.get_bluekey());      //红钥匙
    ui->redkey2->setStyleSheet("color:white;");
    QFont font3 ( "Microsoft YaHei", 27, 75);
    ui->redkey2->setFont(font3);
    ui->life2->setText(hero.get_life());         //生命值
    ui->life2->setStyleSheet("color:white;");
    QFont font4 ( "Microsoft YaHei", 27, 75);
    ui->life2->setFont(font4);
    ui->attack2->setText(hero.get_attack());         //攻击
    ui->attack2->setStyleSheet("color:white;");
    QFont font5 ( "Microsoft YaHei", 27, 75);
    ui->attack2->setFont(font5);
    ui->defense2->setText(hero.get_defense());         //防御
    ui->defense2->setStyleSheet("color:white;");
    QFont font6 ( "Microsoft YaHei", 27, 75);
    ui->defense2->setFont(font6);
    ui->exp2->setText(hero.get_exp());                //经验
    ui->exp2->setStyleSheet("color:white;");
    QFont font7 ( "Microsoft YaHei", 27, 75);
    ui->exp2->setFont(font7);
    ui->money2->setText(hero.get_money());            //金钱
    ui->money2->setStyleSheet("color:white;");
    QFont font8 ( "Microsoft YaHei", 27, 75);
    ui->money2->setFont(font8);
}



