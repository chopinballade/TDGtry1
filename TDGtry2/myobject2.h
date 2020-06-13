#ifndef MYOBJECT2_H
#define MYOBJECT2_H

#include <QObject>
#include<QPoint>
#include<QPixmap>

class MyObject2 : public QObject    //MyObject2类和MyObject类很像。加了速度。
                     //MyObject2类 基于QVector2D的物体移动。好处是可以通过改speed的值调节（例如子弹）的速度
{
    Q_OBJECT
public:
    //explicit MyObject2(QObject *parent = nullptr);
    MyObject2(QPoint startPos, QPoint targetPos, QString filename);
    void move();   //物体的移动。按向量方向，每次移动speed个单位长度。
        //但不会停下，若要使其停下要再在函数里加限定条件，例如可以加很多flag和if，比如move方法里加入判断能不能动，是否到了拐弯的地方之类的
    void draw(QPainter * painter);

private:
    QPoint _startPos;
    QPoint _currentPos;
    QPoint _targetPos;
    QPixmap _pixmap;
    qreal speed;   //qreal类似double

signals:

public slots:
};

#endif // MYOBJECT2_H
