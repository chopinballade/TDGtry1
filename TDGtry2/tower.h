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
    void draw(QPainter * painter) const;
    double getDistance(QPoint p1,QPoint p2);
    QPoint getPos();

    void checkEnemyInRange();
    void targetDead();
    void startShooting();
    void chooseEnemyForAttack(Enemy *enemy);
    void chosenEnemyEscaped();
    void upGradeTower();
    void changeTowerType();
    void changeTowerAttackRange();
    void changeTowerDamage(int new_damage);

private:
    QPoint _pos;
    QPixmap pixmap;
    int sizeX=80;
    int sizeY=80;

    int attackRange;
    int damage;
    int shootRate;

    Enemy * targetEnemy;
    ChoiceWindow * mygamewindow;
    QTimer * shootingTimer;

signals:

public slots:
    void shoot();

};

#endif // TOWER_H
