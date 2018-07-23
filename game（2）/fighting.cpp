#include "fighting.h"
#include "ui_fighting.h"

fighting::fighting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fighting)
{
    ui->setupUi(this);

    QPixmap pic("D:/code/game/素材/f.png");
    ui->label->setPixmap(pic);
}

fighting::~fighting()
{
    delete ui;
}
