#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include<QPropertyAnimation>
#include<QPoint>
#include<QPixmap>
#include<QPainter>

class MyObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint _currentPos READ getCurrentPos WRITE setCurrentPos)
        //格式要这么写
        //要手动写READ和WRITE对应的函数（getCurrentPos()和setCurrentPos(...)），分别用于读取当前位置、改写当前位置。

public:
    //explicit MyObject(QObject *parent = nullptr);
    MyObject(QPoint startPos, QPoint targetPos, QString fileName);
        //用于两点间运动，故构造函数包括：起始点坐标，终点坐标，物体图片资源路径
    void draw(QPainter * painter);
        //像Tower一样，要一个绘画函数
    void move();  //使物体在两点之间移动
    QPoint getCurrentPos();  //获取当前位置
    void setCurrentPos(QPoint pos);  //设定当前位置

    //注意：在choicewindow(其实是游戏界面)中include这个头文件，并用QList管理

private:
    QPoint _startPos;
    QPoint _targetPos;
    QPoint _currentPos; //当前位置
    QPixmap _pixmap;  //图片

signals:

public slots:
};

#endif // MYOBJECT_H
