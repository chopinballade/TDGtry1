#include "enemy.h"
#include<QPoint>
#include<QVector2D>
#include<QPainter>

Enemy::Enemy(QPoint startPos, QPoint targetPos, QString filename)
    :QObject(0), _pixmap(filename)
{
    this->_startPos=startPos;
    this->_currentPos=startPos;
    this->_targetPos=targetPos;
    speed=0.5;  //可手动对Enemy类的物体速度赋值
}

void Enemy::move(){
    QVector2D vector(_targetPos - _startPos);   //创建向量，从起始位置指向目标位置。中间用减号。
    vector.normalize();   //对向量进行标准化，成为单位向量。
    _currentPos = _currentPos + vector.toPoint() * speed;
                //加上在单位向量方向上移动的长度。 .toPoint()函数将向量转化成Point类型，才能相加。
                //再乘速度。即：方向为vector(_targetPos - _startPos)的方向，每次移动speed（=...）个单位长度。
}

void Enemy::draw(QPainter * painter){  //绘画函数
    painter->drawPixmap(_currentPos, _pixmap);  //在当前位置，画对应图片
}

QPoint Enemy::getCurrentPos(){  //获取当前位置
    return this->_currentPos;
}


