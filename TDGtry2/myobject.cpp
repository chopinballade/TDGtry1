#include "myobject.h"
#include "enemy.h"
#include "choicewindow.h"
#include <QPainter>
#include <QPropertyAnimation>

MyObject::MyObject(QPoint startPos, QPoint targetPos, int damage, Enemy *target,
         ChoiceWindow *gamewindow, const QPixmap &pixmap):
    _currentPos(startPos),
    _startPos(startPos),
    _targetPos(targetPos),
    damage(damage),
    target(target),
    gamewindow(gamewindow),
    _pixmap(pixmap)
{
}

void MyObject::draw(QPainter * painter){
    painter->drawPixmap(_currentPos, _pixmap);
}

void MyObject::move(){  //使物体在两点之间移动。参考并拓展mybutton的动法
    static const int duration = 100;  //子弹总共运动100ms
    QPropertyAnimation * animation = new QPropertyAnimation(this, "_currentPos");  //新建一个动画。这里的currentPos是刚刚在myobject.h里设置然后认识的
    animation->setDuration(duration);  //设置动画时长，即子弹总共运动100ms
    animation->setStartValue(_startPos);
    animation->setEndValue(_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
    animation->start(); //手动开始
}

void MyObject::hitTarget(){

    if(gamewindow->fun_enemy_list().indexOf(target) != -1){
        target->getDamage(damage);
    }
    gamewindow->removedBullet(this);

}

void MyObject::setCurrentPos(QPoint pos){  //改写当前位置
    _currentPos = pos;
}

QPoint MyObject::getCurrentPos(){  //获取当前位置
    return _currentPos;
}





