#include "myobject.h"

MyObject::MyObject(QPoint startPos, QPoint targetPos, QString fileName)
    : QObject(0), _pixmap(fileName)
{
    this->_currentPos = startPos;
    this->_startPos = startPos;
    this->_targetPos = targetPos;

}

void MyObject::draw(QPainter * painter){
    painter->drawPixmap(_currentPos, _pixmap);
}

void MyObject::move(){  //使物体在两点之间移动。参考并拓展mybutton的动法
    QPropertyAnimation * animation = new QPropertyAnimation(this, "_currentPos");  //新建一个动画。这里的currentPos是刚刚在myobject.h里设置然后认识的
    animation->setDuration(2000);  //设置动画时长
    animation->setStartValue(_startPos);
    animation->setEndValue(_targetPos);
    animation->start(); //手动开始
}

QPoint MyObject::getCurrentPos(){  //获取当前位置
    return this->_currentPos;
}

void MyObject::setCurrentPos(QPoint pos){  //改写当前位置
    this->_currentPos = pos;
}
