#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include<QPropertyAnimation>
#include<QPoint>
#include<QPixmap>
#include<QPainter>
#include<QSize>

class QPainter;
class Enemy;
class ChoiceWindow;

class MyObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint _currentPos READ getCurrentPos WRITE setCurrentPos)
        //格式要这么写
        //要手动写READ和WRITE对应的函数（getCurrentPos()和setCurrentPos(...)），分别用于读取当前位置、改写当前位置。

public:

    MyObject(QPoint startPos, QPoint targetPos, int damage, Enemy *target,
           ChoiceWindow *gamewindow, const QPixmap &pixmap = QPixmap(":/bullet1.png"));

    void draw(QPainter * painter) const ;
        //像Tower一样，要一个绘画函数
    void move();  //使物体在两点之间移动
    QPoint getCurrentPos();  //获取当前位置
    void setCurrentPos(QPoint pos);  //设定当前位置
    int getBulletType();
    void changeBulletType();

private:
    QPoint _startPos;
    QPoint _targetPos;
    QPoint _currentPos; //当前位置
    QPixmap _pixmap;  //图片

    Enemy *	target;
    ChoiceWindow * gamewindow;
    int	damage;
    int type;

signals:

public slots:
    void damageEnemy();

};

#endif // MYOBJECT_H
