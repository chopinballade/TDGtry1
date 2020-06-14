#include "heart.h"
#include <QObject>
#include<QPropertyAnimation>
#include<QPoint>
#include<QPixmap>
#include<QPainter>
#include<QPaintEvent>

Heart::Heart(int _currentHP, QString filename): _currentHP(5), _pixmap(filename){
    this->_currentHP = 5;
}

void Heart::draw(QPainter * painter){
    painter->drawPixmap(QPoint(920,200), _pixmap);  //在当前位置，画对应图片

}
