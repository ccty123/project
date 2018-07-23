#include "gameboundary.h"
#include "ui_gameboundary.h"

GameBoundary::GameBoundary(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameBoundary)
{
    ui->setupUi(this);
    ui->label_10->hide();
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

GameBoundary::~GameBoundary()
{
    delete ui;
}

void GameBoundary::keyPressEvent(QKeyEvent*event)
{
    if ((event->key()==Qt::Key_A)||(event->key()==Qt::Key_Left))        //向左移动
    {
        QPixmap left(LEFT);
        ui->character->setPixmap(left);
        if (ui->character->x() == 650 && ui->character->y() == 450)
            ui->character->move((ui->character->x()) - 50, ui->character->y());
        if (ui->character->x() == 600 && ui->character->y() == 450)     //对话
        {
            ui->label_10->show();
            if (event->key()==Qt::Key_A || event->key()==Qt::Key_Left)
                ui->label_10->hide();
        }
    }
    else  if ((event->key()==Qt::Key_S)||(event->key()==Qt::Key_Down))      //向下移动
    {
        QPixmap down(DOWN);
        ui->character->setPixmap(down);
        if (ui->character->x() == 600 && ui->character->y() <= 500 && ui->character->y() >= 50)
            ui->character->move(ui->character->x(), (ui->character->y()) + 50);
    }
    else  if ((event->key()==Qt::Key_D)||(event->key()==Qt::Key_Right))     //向右移动
    {
        QPixmap right(RIGHT);
        ui->character->setPixmap(right);
        if (ui->character->x() == 600 && ui->character->y() == 450)
            ui->character->move((ui->character->x()) + 50, ui->character->y());
    }
    else  if ((event->key()==Qt::Key_W)||(event->key()==Qt::Key_Up))        //向上移动
    {
        QPixmap up(UP);
        ui->character->setPixmap(up);
        if (100 <= ui->character->y() && ui->character->y() <= 550 && ui->character->x() == 600)
        {
            if (ui->character->y() == 450 && door == 1)     //遇到门
            {
               hero.lose_key(1);
               ui->yellowkey->setText(hero.get_yellowkey());
               door = 0;
               QPixmap road(ROAD);
               ui->door->setPixmap(road);
               return;
            }
            else if (ui->character->y() == 100) {   //上1楼
                jump();
                QPixmap down(DOWN);
                ui->character->setPixmap(down);
                return;
            }
            ui->character->move(ui->character->x(), (ui->character->y()) - 50);
        }
    }
    else QWidget::keyPressEvent(event);
}

/*void GameBoundary::on_left_clicked()        //向左移动
{
    QPixmap left(LEFT);
    ui->character->setPixmap(left);
    if (ui->character->x() == 650 && ui->character->y() == 450)
        ui->character->move((ui->character->x()) - 50, ui->character->y());
}
void GameBoundary::on_down_clicked()        //向下移动
{
    QPixmap down(DOWN);
    ui->character->setPixmap(down);
    if (ui->character->x() == 600 && ui->character->y() <= 500 && ui->character->y() >= 50)
        ui->character->move(ui->character->x(), (ui->character->y()) + 50);
}
static int GameBoundary::flag=0;
/void GameBoundary::on_up_clicked()      //向上移动
{
    QPixmap up(UP);
    ui->character->setPixmap(up);
    if (100 <= ui->character->y() && ui->character->y() <= 550 && ui->character->x() == 600)
    {
        if (ui->character->y() == 450 && door == 1)     //遇到门
        {
           hero.lose_key(1);
           QPixmap road(ROAD);
           door = 0;
           ui->door->setPixmap(road);
           return;
        }
        else if (ui->character->y() == 100) {jump();}       //上1楼

        ui->character->move(ui->character->x(), (ui->character->y()) - 50);
    }
}

void GameBoundary::on_right_clicked()       //向右移动
{

    QPixmap right(RIGHT);
    ui->character->setPixmap(right);
    if (ui->character->x() == 600 && ui->character->y() == 450)
        ui->character->move((ui->character->x()) + 50, ui->character->y());
}*/

void  GameBoundary::jump()       //上1楼
{
    this->hide();
    emit zero_to_one();
}
void GameBoundary::showfloor0()
{
    this->show();
}


