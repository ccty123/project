#include "gameboundary1.h"
#include "ui_gameboundary1.h"

GameBoundary1::GameBoundary1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameBoundary1)
{
    ui->setupUi(this);

    for (int i = 1; i <= 6; i++)
        door[i] = true;
    for (int i = 1; i <= 14; i++)
        key[i] = true;
    for (int i = 1; i <= 8; i++)
        water[i] = true;
    dia[1] = true;
    dia[2] = true;
    check_tool = false;

    mon1.initial(50, 20, 1, 1, 1);
    mon2.initial(70, 15, 2, 2, 2);
    mon3.initial(50, 20, 1, 1, 1);
    mon4.initial(110, 25, 5, 4, 5);
    mon5.initial(110, 25, 5, 4, 5);
    mon6.initial(200, 35, 10, 5, 5);
    mon7.initial(150, 40, 20, 6, 8);
    mon8.initial(125, 50, 25, 7, 10);
    mon9.initial(50, 20, 1, 1, 1);
    mon10.initial(100, 20, 5, 3, 3);
    mon11.initial(150, 40, 20, 6, 8);
    mon12.initial(300, 75, 45, 10, 13);

    QMovie* movie1 = new QMovie(MON1);
    ui->label_168->setMovie(movie1);
    ui->label_301->setMovie(movie1);
    ui->label_303->setMovie(movie1);
    movie1->start();

    QMovie* movie2 = new QMovie(MON2);
    ui->label_302->setMovie(movie2);
    movie2->start();

    QMovie* movie3 = new QMovie(MON3);
    ui->label_114->setMovie(movie3);
    movie3->start();

    QMovie* movie4 = new QMovie(MON4);
    ui->label_66->setMovie(movie4);
    ui->label_112->setMovie(movie4);
    movie4->start();

    QMovie* movie5 = new QMovie(MON5);
    ui->label_157->setMovie(movie5);
    ui->label_214->setMovie(movie5);
    movie5->start();

    QMovie* movie7 = new QMovie(MON7);
    ui->label_125->setMovie(movie7);
    movie7->start();

    QMovie* movie10 = new QMovie(MON10);
    ui->label_223->setMovie(movie10);
    movie10->start();

    QMovie* movie12 = new QMovie(MON12);
    ui->label_156->setMovie(movie12);
    movie12->start();
}
GameBoundary1::~GameBoundary1()
{
    delete ui;
}

void GameBoundary1::jump(int floor)
{
    if (floor == 0){
      this->hide();
      emit one_to_zero();
    }

    else if (floor == 2){
        this->hide();
        emit one_to_two();
    }
}

void GameBoundary1::move(int direction)
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

void GameBoundary1::MeetDoor(int direction, int type, int index, QLabel *label)     //遇到门
{
    if (door[index])
    {
        if(hero.key_number(type)){
            hero.lose_key(type);
            label->hide();
            door[index] = false;
            switch (type) {
                case 1: ui->yellowkey1->setText(hero.get_yellowkey());  break;
                case 2: ui->bluekey1->setText(hero.get_bluekey()); break;
                case 3: ui->redkey1->setText(hero.get_redkey()); break;
            }
        }
    }
    else
        move(direction);
}

void GameBoundary1::MeetKey(int direction, int type, int index, QLabel *label)
{
    if (key[index])
    {
        hero.gain_key(type);
        key[index] = false;
        label->hide();
        switch (type) {
            case 1: ui->yellowkey1->setText(hero.get_yellowkey());  break;
            case 2: ui->bluekey1->setText(hero.get_bluekey()); break;
            case 3: ui->redkey1->setText(hero.get_redkey()); break;
        }
    }
    else
        move(direction);
}

void GameBoundary1::MeetWater(int direction, int type, int index, QLabel *label)
{
    if (water[index])
    {
        water[index] = false;
        label->hide();
        (type == 1) ? hero.raise_life(200) : hero.raise_life(500);
    }
    else
        move(direction);
}

void GameBoundary1::MeetMonster(int direction, Monster &mon, QLabel *label)
{
    if (mon.get_alive()){
        if (hero.attack_monster(mon)){
            mon.update_alive();
            ui->life1->setText(hero.get_life());
            ui->attack1->setText(hero.get_attack());
            ui->defense1->setText(hero.get_defense());
            ui->level1->setText(hero.get_level());
            ui->exp1->setText(hero.get_exp());
            ui->money1->setText(hero.get_money());
            label->hide();
        }
        else
            return;
    }
    else
        move(direction);
}

void GameBoundary1::on_up_clicked()     //向上移动
{
    QPixmap up(UP);
    ui->character->setPixmap(up);

    switch (ui->character->y() / 50)        //按行遍历
    {
    case 1:
        break;

    case 2:
        if (ui->character->x() == 850)
            move(1);
        break;

    case 3:
        if (ui->character->x() == 850)
            move(1);
        break;

    case 4:
        switch (ui->character->x())
        {
        case 350:       //红药水
          {  MeetWater(1, 1, 1, ui->label_82);
            ui->life1->setText(hero.get_life()); }
            break;

        case 650:       //红药水
          {  MeetWater(1, 1, 2, ui->label_99);
            ui->life1->setText(hero.get_life()); }
            break;

        case 750:       //红药水
          {  MeetWater(1, 1, 3, ui->label_68);
            ui->life1->setText(hero.get_life()); }
            break;

        case 400:
            move(1);
            break;

        case 550:
            move(1);
            break;

        case 850:
            move(1);
            break;

        case 450:       //遇怪
            MeetMonster(1, mon4, ui->label_66);
            break;

        case 700:       //黄钥匙
            MeetKey(1, 1, 2, ui->label_111);
            ui->yellowkey1->setText(hero.get_yellowkey());
            break;
        }
        break;

    case 5:
        if (ui->character->x() == 550 || ui->character->x() == 850 || ui->character->x() == 400)
            move(1);
        else if (ui->character->x() == 750)        //红药水
          {  MeetWater(1, 1, 5, ui->label_69);
             ui->life1->setText(hero.get_life()); }
        break;

    case 6:
        if (ui->character->x() == 400 || ui->character->x() == 550 || ui->character->x() == 850)
            move(1);
        else if (ui->character->x() == 750)        //遇怪
            MeetMonster(1, mon6, ui->label_114);
        break;

    case 7:
        if (ui->character->x() == 400 || ui->character->x() == 550 || ui->character->x() == 850 || ui->character->x() == 450)
            move(1);
        else if (ui->character->x() == 350)        //黄钥匙
          {  MeetKey(1, 1, 5, ui->label_139);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    case 8:
        if (ui->character->x() == 400 || ui->character->x() == 550 || ui->character->x() == 850)
            move(1);
        break;

    case 9:
        if (ui->character->x() == 400 || ui->character->x() == 600 || ui->character->x() == 800)
            move(1);
        break;

    case 10:
        if (ui->character->x() == 350 || ui->character->x() == 400 || ui->character->x() == 450 || ui->character->x() == 800)
            move(1);
        else if (ui->character->x() == 600)            //红门
         {   MeetDoor(1, 3, 5, ui->label_197);
            ui->redkey1->setText(hero.get_redkey());}
        break;

    case 11:
        if (ui->character->x() == 550 || ui->character->x() == 650 || ui->character->x() == 800)
            move(1);
        else if (ui->character->x() == 350)        //红药水
         {   MeetWater(1, 1, 6, ui->label_177);
             ui->life1->setText(hero.get_life()); }
        else if (ui->character->x() == 400)        //蓝药水
         {   MeetWater(1, 2, 7, ui->label_226);
             ui->life1->setText(hero.get_life()); }
        else if (ui->character->x() == 450)        //黄钥匙
         {   MeetKey(1, 1, 7, ui->label_212);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 750)        //黄钥匙
          {  MeetKey(1, 1, 9, ui->label_183);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 850)        //蓝钥匙
        {    MeetKey(1, 2, 10, ui->label_188);
           ui->bluekey1->setText(hero.get_bluekey()); }
        break;

    default:
        break;
    }
}

void GameBoundary1::on_down_clicked()       //向下移动
{
    QPixmap down(DOWN);
    ui->character->setPixmap(down);

    switch (ui->character->y() / 50)
    {
    case 1:
        if (ui->character->x() == 850)
            move(2);
        break;

    case 2:
        if (ui->character->x() == 850)
            move(2);
        break;

    case 3:
        if (ui->character->x() == 550 || ui->character->x() == 850)
            move(2);
        else if (ui->character->x() == 350)        //黄钥匙
        {    MeetKey(2, 1, 3, ui->label_63);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 700)        //黄钥匙
        {   MeetKey(2, 1, 4, ui->label_101);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 400)        //遇怪
            MeetMonster(2, mon5, ui->label_112);
        else if (ui->character->x() == 650)        //红药水
        {    MeetWater(2, 1, 4, ui->label_67);
            ui->life1->setText(hero.get_life()); }
        else if (ui->character->x() == 750)        //红药水
       {     MeetWater(2, 1, 5, ui->label_69);
             ui->life1->setText(hero.get_life()); }
        else if (ui->character->x() == 450){        //红宝石
            if (dia[1]){
                dia[1] = false;
                ui->label_98->hide();
                hero.raise_attack(3);
                ui->attack1->setText(hero.get_attack());
            }
            else
                move(2);
        }
        break;

    case 4:
        if (ui->character->x() == 550 || ui->character->x() == 750 || ui->character->x() == 850)
            move(2);
        else if (ui->character->x() == 400)        //黄门
         {   MeetDoor(2, 1, 2, ui->label_334);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    case 5:
        if (ui->character->x() == 550 || ui->character->x() == 750 || ui->character->x() == 850)
            move(2);
        else if (ui->character->x() == 400)        //遇怪
            MeetMonster(2, mon7, ui->label_157);
        break;

    case 6:
        if (ui->character->x() == 400 || ui->character->x() == 550 || ui->character->x() == 850)
            move(2);
        else if (ui->character->x() == 350){        //蓝宝石
            if (dia[2]){
                dia[2] = false;
                ui->label_120->hide();
                hero.raise_defense(3);
                ui->defense1->setText(hero.get_defense());
            }
            else
                move(2);
        }
        else if (ui->character->x() == 450)        //蓝钥匙
         {   MeetKey(2, 2, 6, ui->label_155);
           ui->bluekey1->setText(hero.get_bluekey()); }
        break;

    case 7:
        if (ui->character->x() == 550 || ui->character->x() == 850)
            move(2);
        else if (ui->character->x() == 400)        //黄门
         {   MeetDoor(2, 1, 4, ui->label_331);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    case 8:
        if (ui->character->x() == 400)     //遇怪
            MeetMonster(2, mon11, ui->label_214);
        else if (ui->character->x() == 600)        //红门
      {      MeetDoor(2, 3, 5, ui->label_197);
            ui->redkey1->setText(hero.get_redkey());}
        else if (ui->character->x() == 800)        //黄门
          {  MeetDoor(2, 1, 6, ui->label_279);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    case 9:
        if (ui->character->x() == 600)
            move(2);
        else if (ui->character->x() == 350)        //红药水
        {    MeetWater(2, 1, 6, ui->label_177);
             ui->life1->setText(hero.get_life()); }
        else if (ui->character->x() == 400)        //蓝药水
         {   MeetWater(2, 2, 7, ui->label_226);
             ui->life1->setText(hero.get_life()); }
        else if (ui->character->x() == 450)        //黄钥匙
        {    MeetKey(2, 1, 7, ui->label_212);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 800)        //遇怪
            MeetMonster(2, mon12, ui->label_223);
        break;

    case 10:
        if (ui->character->x() == 550 || ui->character->x() == 650)
            ui->character->move(ui->character->x(), (ui->character->y()) + 50);
        else if (ui->character->x() == 350)        //红药水
        {    MeetWater(2, 1, 8, ui->label_191);
             ui->life1->setText(hero.get_life()); }
        else if (ui->character->x() == 400){        //捡到道具
            if (!check_tool){
                check_tool = true;
                hero.raise_attack(30);
                hero.raise_defense(30);
                ui->attack1->setText(hero.get_attack());
                ui->defense1->setText(hero.get_defense());
                ui->label_192->hide();
            }
            else
                move(2);
        }
        else if (ui->character->x() == 450)        //黄钥匙
         {   MeetKey(2, 1, 11, ui->label_217);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 750)        //黄钥匙
         {    MeetKey(2, 1, 12, ui->label_228);
           ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 800)        //黄钥匙
         {   MeetKey(2, 1, 13, ui->label_204);
             ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 850)        //黄钥匙
         {   MeetKey(2, 1, 14, ui->label_198);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->x() == 600)        //下到0楼
            jump(0);
        break;

    case 11:
        break;

    default:
        break;
    }
}

void GameBoundary1::on_left_clicked()       //向左移动
{
    QPixmap left(LEFT);
    ui->character->setPixmap(left);

    switch ((ui->character->x() - 300) / 50)
    {
    case 1:
        break;

    case 2:
        if (ui->character->y() == 50)       //上到2楼
        {
            QPixmap down(DOWN);
            ui->character->setPixmap(down);
            jump(2);
            break;
        }
        else if (ui->character->y() == 150)    //红药水
        {    MeetWater(3, 1, 1, ui->label_82);
            ui->life1->setText(hero.get_life()); }
        else if (ui->character->y() == 200)     //黄钥匙
         {   MeetKey(3, 1, 3, ui->label_63);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 300)     //黄钥匙
         {   MeetKey(3, 1, 5, ui->label_139);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 350){    //蓝宝石
            if (dia[2]){
                dia[2] = false;
                ui->label_120->hide();
                hero.raise_defense(3);
                ui->defense1->setText(hero.get_defense());
            }
            else
                move(3);
        }
        else if (ui->character->y() == 450)
            move(3);
        else if (ui->character->y() == 500)     //红药水
        {    MeetWater(3, 1, 6, ui->label_177);
            ui->life1->setText(hero.get_life()); }
        else if (ui->character->y() == 550)     //红药水
        {    MeetWater(3, 1, 8, ui->label_191);
            ui->life1->setText(hero.get_life()); }
        break;

    case 3:
        if (ui->character->y() == 150 || ui->character->y() == 50 || ui->character->y() == 350 || ui->character->y() == 450 || ui->character->y() == 300)
            move(3);
        else if (ui->character->y() == 200)         //遇怪
            MeetMonster(3, mon5, ui->label_112);
        else if (ui->character->y() == 300)         //遇怪
            MeetMonster(3, mon7, ui->label_157);
        else if (ui->character->y() == 450)         //遇怪
            MeetMonster(3, mon11, ui->label_214);
        else if (ui->character->y() == 500)         //蓝药水
        {    MeetWater(3, 2, 7, ui->label_226);
             ui->life1->setText(hero.get_life()); }
        else if (ui->character->y() == 550){        //捡到道具
            if (!check_tool){
                check_tool = true;
                hero.raise_attack(30);
                hero.raise_defense(30);
                ui->attack1->setText(hero.get_attack());
                ui->defense1->setText(hero.get_defense());
                ui->label_192->hide();
            }
            else
                move(3);
        }
        break;

    case 4:
        if (ui->character->y() == 50)       //黄钥匙
        {    MeetKey(3, 1, 1, ui->label_26);
           ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 150)     //遇怪
            MeetMonster(3, mon4, ui->label_66);
        break;

    case 5:
        if (ui->character->y() == 50)       //遇怪
            MeetMonster(3, mon1, ui->label_303);
        else if (ui->character->y() == 150)     //黄门
         {   MeetDoor(3, 1, 1, ui->label_321);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if(ui->character->y()==500)
      {      MeetKey(3,3,8,ui->label_194);
             ui->redkey1->setText(hero.get_redkey());}

        break;

    case 6:
        if (ui->character->y() == 300 || ui->character->y() == 400)
            move(3);
        else if (ui->character->y() == 50)      //遇怪
            MeetMonster(3, mon2, ui->label_302);
        else if (ui->character->y() == 500)     //红钥匙
       {     MeetKey(3, 3, 8, ui->label_194);
             ui->redkey1->setText(hero.get_redkey());}
        break;

    case 7:
        if (ui->character->y() == 300 || ui->character->y() == 400 || ui->character->y() == 500)
            move(3);
        else if (ui->character->y() == 50)      //遇怪
            MeetMonster(3, mon3, ui->label_301);
        else if (ui->character->y() == 550)     //下到0楼
            jump(0);
        break;

    case 8:
        if (ui->character->y() == 50 || ui->character->y() == 300 || ui->character->y() == 400)
            move(3);
        else if (ui->character->y() == 150)     //红药水
       {     MeetWater(3, 1, 2, ui->label_99);
            ui->life1->setText(hero.get_life()); }
        else if (ui->character->y() == 200)     //红药水
        {    MeetWater(3, 1, 4, ui->label_67);
            ui->life1->setText(hero.get_life()); }
        break;

    case 9:
        if (ui->character->y() == 50 || ui->character->y() == 300 || ui->character->y() == 400)
            move(3);
        else if (ui->character->y() == 150)     //黄钥匙
         {   MeetKey(3, 1, 2, ui->label_111);
           ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 200)     //黄钥匙
         {   MeetKey(3, 1, 4, ui->label_101);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    case 10:
        if (ui->character->y() == 50 || ui->character->y() == 400)
            move(3);
        else if (ui->character->y() == 500)     //黄钥匙
         {   MeetKey(3, 1, 9, ui->label_183);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 550)     //黄钥匙
         {   MeetKey(3, 1, 12, ui->label_228);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    case 11:
        if (ui->character->y() == 50 || ui->character->y() == 400 || ui->character->y() == 500)
            move(3);
        else if (ui->character->y() == 550)     //黄钥匙
         {   MeetKey(3, 1, 13, ui->label_204);
           ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    default:
        break;
    }
}

void GameBoundary1::on_right_clicked()      //向右移动
{
    QPixmap right(RIGHT);
    ui->character->setPixmap(right);

    switch ((ui->character->x() - 300) / 50)
    {
    case 1:
        if (ui->character->y() == 150 || ui->character->y() == 350 || ui->character->y() == 450 || ui->character->y() == 300)
            move(4);
        else if (ui->character->y() == 200)     //遇怪
            MeetMonster(4, mon5, ui->label_112);
        else if (ui->character->y() == 500)     //蓝药水
       {     MeetWater(4, 2, 7, ui->label_226);
             ui->life1->setText(hero.get_life()); }
        else if (ui->character->y() == 550){        //捡到道具
            if (!check_tool){
                check_tool = true;
                hero.raise_attack(30);
                hero.raise_defense(30);
                ui->attack1->setText(hero.get_attack());
                ui->defense1->setText(hero.get_defense());
                ui->label_192->hide();
            }
            else
                move(4);
        }
        break;

    case 2:
        if (ui->character->y() == 150 || ui->character->y() == 450 || ui->character->y() == 300)
            move(4);
        else if (ui->character->y() == 50)      //黄钥匙
         {   MeetKey(4, 1, 1, ui->label_26);
           ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 200){        //红宝石
            if (dia[1]){
                dia[1] = false;
                ui->label_98->hide();
                hero.raise_attack(3);
                ui->attack1->setText(hero.get_attack());
            }
            else
                move(4);
        }
        else if (ui->character->y() == 350)     //蓝钥匙
        {    MeetKey(4, 2, 6, ui->label_155);
          ui->bluekey1->setText(hero.get_bluekey()); }
        else if (ui->character->y() == 500)     //黄钥匙
          {  MeetKey(4, 1, 7, ui->label_212);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 550)     //黄钥匙
          {  MeetKey(4, 1, 11, ui->label_217);
           ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    case 3:
        if (ui->character->y() == 150)
            move(4);
        else if (ui->character->y() == 50)      //遇怪
            MeetMonster(4, mon1, ui->label_303);
        break;

    case 5:
        if (ui->character->y() == 400 || ui->character->y() == 500)
            move(4);
        else if (ui->character->y() == 50)      //遇怪
            MeetMonster(4, mon3, ui->label_301);
        else if (ui->character->y() == 300)     //黄门
           { MeetDoor(4, 1, 3, ui->label_140);
           ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 550)     //下到0楼
            jump(0);
        break;

    case 6:
        if (ui->character->y() == 50 || ui->character->y() == 400 || ui->character->y() == 500)
            move(4);
        else if (ui->character->y() == 300)     //遇怪
            MeetMonster(4, mon8, ui->label_156);
        break;

    case 7:
        if (ui->character->y() == 50 || ui->character->y() == 400)
            move(4);
        else if (ui->character->y() == 150)     //黄钥匙
         {   MeetKey(4, 1, 2, ui->label_111);
             ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 200)     //黄钥匙
         {   MeetKey(4, 1, 4, ui->label_101);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        else if (ui->character->y() == 300)     //遇怪
            MeetMonster(4, mon9, ui->label_168);
        break;

    case 8:
        if (ui->character->y() == 50 || ui->character->y() == 400)
            move(4);
        else if (ui->character->y() == 150)     //红药水
        {    MeetKey(4, 1, 3, ui->label_68);
            ui->life1->setText(hero.get_life()); }
        else if (ui->character->y() == 200)     //红药水
        {    MeetKey(4, 1, 5, ui->label_69);
            ui->life1->setText(hero.get_life()); }
        else if (ui->character->y() == 300)     //遇怪
            MeetMonster(4, mon10, ui->label_125);
        break;

    case 9:
        if (ui->character->y() == 50 || ui->character->y() == 400 || ui->character->y() == 500)
            move(4);
        else if (ui->character->y() == 550)     //黄钥匙
         {   MeetKey(4, 1, 13, ui->label_204);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    case 10:
        if (ui->character->y() == 50 || ui->character->y() == 400)
            move(4);
        else if (ui->character->y() == 500)     //蓝钥匙
        {    MeetKey(4, 2, 10, ui->label_188);
            ui->bluekey1->setText(hero.get_bluekey()); }
        else if (ui->character->y() == 550)     //黄钥匙
         {   MeetKey(4, 1, 14, ui->label_198);
            ui->yellowkey1->setText(hero.get_yellowkey());}
        break;

    case 11:
        break;

    case 4:
        if (ui->character->y() == 150)
            move(4);
        else if (ui->character->y() == 50)      //遇怪
            MeetMonster(4, mon2, ui->label_302);
        break;

    default:
        break;
    }
}

void GameBoundary1::keyPressEvent(QKeyEvent*event)   //控制方向--键盘事件
{
    if ((event->key()==Qt::Key_A)||(event->key()==Qt::Key_Left))
        GameBoundary1::on_left_clicked();
    else if ((event->key()==Qt::Key_S)||(event->key()==Qt::Key_Down))
        GameBoundary1::on_down_clicked();
    else if ((event->key()==Qt::Key_D)||(event->key()==Qt::Key_Right))
        GameBoundary1::on_right_clicked();
    else if ((event->key()==Qt::Key_W)||(event->key()==Qt::Key_Up))
        GameBoundary1::on_up_clicked();
    else QWidget::keyPressEvent(event);
}

void GameBoundary1::showfloor1()
{
    this->show();
    ui->level1->setText(hero.get_level());         //等级
    ui->level1->setStyleSheet("color:white;");
    QFont font ( "Microsoft YaHei", 27, 75);
    ui->level1->setFont(font);
    ui->yellowkey1->setText(hero.get_yellowkey());  //黄钥匙
    ui->yellowkey1->setStyleSheet("color:white;");
    QFont font1 ( "Microsoft YaHei", 27, 75);
    ui->yellowkey1->setFont(font1);
    ui->bluekey1->setText(hero.get_bluekey());      //蓝钥匙
    ui->bluekey1->setStyleSheet("color:white;");
    QFont font2 ( "Microsoft YaHei", 27, 75);
    ui->bluekey1->setFont(font2);
    ui->redkey1->setText(hero.get_bluekey());      //红钥匙
    ui->redkey1->setStyleSheet("color:white;");
    QFont font3 ( "Microsoft YaHei", 27, 75);
    ui->redkey1->setFont(font3);
    ui->life1->setText(hero.get_life());            //生命值
    ui->life1->setStyleSheet("color:white;");
    QFont font4 ( "Microsoft YaHei", 27, 75);
    ui->life1->setFont(font4);
    ui->attack1->setText(hero.get_attack());         //攻击
    ui->attack1->setStyleSheet("color:white;");
    QFont font5 ( "Microsoft YaHei", 27, 75);
    ui->attack1->setFont(font5);
    ui->defense1->setText(hero.get_defense());         //防御
    ui->defense1->setStyleSheet("color:white;");
    QFont font6 ( "Microsoft YaHei", 27, 75);
    ui->defense1->setFont(font6);
    ui->exp1->setText(hero.get_exp());            //经验
    ui->exp1->setStyleSheet("color:white;");
    QFont font7 ( "Microsoft YaHei", 27, 75);
    ui->exp1->setFont(font7);
    ui->money1->setText(hero.get_money());            //金钱
    ui->money1->setStyleSheet("color:white;");
    QFont font8 ( "Microsoft YaHei", 27, 75);
    ui->money1->setFont(font8);

}
