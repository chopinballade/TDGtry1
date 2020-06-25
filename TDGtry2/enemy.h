#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include<QPropertyAnimation>
#include<QPoint>
#include<QSize>
#include<QPixmap>
#include<QPainter>

class QPainter;
class ChoiceWindow;  //到达终点要减HP
class Tower;  //与对应的塔要建立联系

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(QPoint startPos, QPoint targetPos, ChoiceWindow *game, const QPixmap &sprite = QPixmap(":/enemy3.png"));
    ~Enemy();

    void move();   //物体的移动。按向量方向，每次移动speed个单位长度。
        //但不会停下，若要使其停下要再在函数里加限定条件，例如可以加很多flag和if，比如move方法里加入判断能不能动，是否到了拐弯的地方之类的
    void draw(QPainter * painter);
    QPoint getCenterPos();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    QPoint getcurrentpos() const;
    void slowSpeed();
    void fastSpeed();
    void changeEnemyType_1();
    void changeEnemyType_2();

    QPoint _startPos;
    QPoint _currentPos;
    QPoint _targetPos;
    QPixmap _pixmap;
    qreal speed;   //qreal类似double
    int maxHP;  //最初血量
    int currentHP;  //当前血量
    bool active;  //表示敌人是否可以移动，true为可以移动
    ChoiceWindow * gamewindow;   //游戏所在的窗口，暂时命名为gamewindow
    QList<Tower *>	attackedTowersList;   //敌人的对应攻击炮塔
    //暂时当作public

private:

signals:

public slots:
    void doActivate();

};

#endif // ENEMY_H
