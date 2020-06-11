#include "tower.h"
#include<QPoint>
#include<QPixmap>
#include<QPainter>
#include<QPropertyAnimation>


Tower::Tower(QPoint pos, QString pixFileName)
    : QObject(0),pixmap(pixFileName)
{
    this->_pos=pos;
}

void Tower::draw(QPainter * painter){
    painter->drawPixmap(_pos, pixmap);
}
