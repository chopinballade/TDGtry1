#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include<QPropertyAnimation>
#include<QPoint>
#include<QPixmap>
#include<QPainter>

class Enemy : public QObject
{
    Q_OBJECT
public:
    //explicit MyObject2(QObject *parent = nullptr);
    Enemy(QPoint startPos, QPoint targetPos, QString filename);
    void move();   //物体的移动。按向量方向，每次移动speed个单位长度。
        //但不会停下，若要使其停下要再在函数里加限定条件，例如可以加很多flag和if，比如move方法里加入判断能不能动，是否到了拐弯的地方之类的
    void draw(QPainter * painter);
    QPoint getCurrentPos();

private:
    QPoint _startPos;
    QPoint _currentPos;
    QPoint _targetPos;
    QPixmap _pixmap;
    qreal speed;   //qreal类似double

signals:

public slots:
};

#endif // ENEMY_H
