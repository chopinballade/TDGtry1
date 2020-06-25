#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include<QSize>
#include<QPoint>
#include<QPixmap>

class QPainter;
class Enemy;
class ChoiceWindow;
class QTimer;

class Tower : public QObject
{
    Q_OBJECT

public:
    Tower(QPoint pos, ChoiceWindow * gamewindow, const QPixmap &pixFileName = QPixmap(":/tower1.png"));  //pos位置，pixFileName文件路径
    ~Tower();
    void draw(QPainter * painter);
    double getDistance(QPoint p1,QPoint p2);
    QPoint getPos();

    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();

private:
    QPoint _pos;
    QPixmap pixmap;
    int sizeX=80;
    int sizeY=80;

    int attackRange;
    int damage;
    int fireRate;  //攻击频率，默认1000毫秒攻击一次

    bool attacking;
    Enemy * chooseEnemy;
    ChoiceWindow * mygamewindow;
    QTimer * fireRateTimer;

signals:

public slots:
    void shootWeapon();

};

#endif // TOWER_H
