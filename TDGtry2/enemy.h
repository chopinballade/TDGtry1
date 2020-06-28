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
    void draw(QPainter * painter);
    QPoint getCenterPos();
    void enemyGetDamage(int damage);
    void getDeleted();
    void getAttacked(Tower *attacker);
    void haveEscaped(Tower *attacker);
    QPoint getcurrentpos() const;
//    void slowSpeed();
//    void fastSpeed();  //加到slots里面
    void changeEnemyType_1();
    void changeEnemyType_2();

    QPoint _startPos;
    QPoint _currentPos;
    QPoint _targetPos;
    QPixmap _pixmap;
    qreal speed;   //qreal类似double
    int maxHP;  //最初血量
    int currentHP;  //当前血量
    bool isAlive;  //表示敌人是否可以移动，true为可以移动
    ChoiceWindow * gamewindow;   //游戏所在的窗口，暂时命名为gamewindow
    QList<Tower *>	attackedTowersList;   //敌人的对应攻击炮塔
    //暂时当作public

private:

signals:

public slots:
    void slowSpeed();
    void fastSpeed();
    void turnAlive();

};

#endif // ENEMY_H
