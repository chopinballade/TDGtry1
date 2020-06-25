#include "tower.h"
#include<math.h>
#include<QPoint>
#include<QPixmap>
#include<QPainter>
#include<QColor>
#include<QTimer>
#include<QPropertyAnimation>
#include<QTimer>
#include"enemy.h"
#include"choicewindow.h"
#include"myobject.h"
#include"myobject2.h"
#include <QVector2D>
#include <QtMath>


Tower::Tower(QPoint pos, ChoiceWindow * gamewindow, const QPixmap &pixFileName)
    : QObject(0),mygamewindow(gamewindow), pixmap(pixFileName),
      _pos(pos),sizeX(80),sizeY(80),
      attackRange(180),damage(10),fireRate(1000),attacking(false),chooseEnemy(NULL)
{
    fireRateTimer = new QTimer(this);
    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::~Tower(){
    delete fireRateTimer;
    fireRateTimer = NULL;
}

double Tower::getDistance(QPoint p1, QPoint p2){//友元函数
    double dist;
    dist= (p1.x()-p2.x())*(p1.x()-p2.x()) + (p1.y()-p2.y())*(p1.y()-p2.y());
    dist= sqrt(dist);
    return dist;
}

QPoint Tower::getPos(){
    return this->_pos;
}

void Tower::draw(QPainter * painter){    
    painter->save();
    painter->setPen(Qt::white);    // 绘制攻击范围圆圈
    painter->drawEllipse(_pos, attackRange, attackRange);
    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(- sizeX / 2, - sizeY / 2);
    // 绘制炮塔并选择炮塔。这里将坐标原点移到_pos,绘制的适合,就要加上那个偏移点到左上角
    painter->translate(_pos);
    painter->drawPixmap(offsetPoint, pixmap);
    painter->restore();
}

void Tower::checkEnemyInRange(){
    if (chooseEnemy){
        QVector2D normalized(chooseEnemy->getcurrentpos() - _pos);  //敌人到塔的向量
        normalized.normalize();

        if (this->getDistance(chooseEnemy->getcurrentpos() , _pos) > this->attackRange){
            // 如果敌人脱离攻击范围
            lostSightOfEnemy();
        }
    }
    else{ // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = mygamewindow->fun_enemy_list();
        foreach (Enemy *enemy, enemyList){
            if (this->getDistance(chooseEnemy->_currentPos , _pos) < this->attackRange){
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::attackEnemy(){
    fireRateTimer->start(fireRate);
}

void Tower::chooseEnemyForAttack(Enemy *enemy){
    chooseEnemy = enemy;
    attackEnemy();
    chooseEnemy->getAttacked(this);
}

void Tower::shootWeapon(){
    MyObject *bullet = new MyObject(_pos,chooseEnemy->getcurrentpos(),damage,chooseEnemy, mygamewindow );
    bullet->move();
    mygamewindow->addBullet(bullet);
}

void Tower::targetKilled(){
    if (chooseEnemy){
        chooseEnemy = NULL;
    }
    fireRateTimer->stop();
}

void Tower::lostSightOfEnemy(){
    chooseEnemy->gotLostSight(this);
    if (chooseEnemy){
        chooseEnemy = NULL;
    }
    fireRateTimer->stop();
}





