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


Tower::Tower(QPoint pos, ChoiceWindow * gamewindow, const QPixmap &pixFileName)
    : QObject(0),
      _pos(pos),pixmap(pixFileName),sizeX(80),sizeY(80),
      attackRange(220),damage(8),shootRate(1000),   //先设每    ms发射一次子弹
      targetEnemy(NULL),mygamewindow(gamewindow)
{
    shootingTimer = new QTimer(this);
    connect(shootingTimer, SIGNAL(timeout()), this, SLOT(shoot()));
      //将QTimer类的shootingTimer与shoot()函数connect起来
}

Tower::~Tower(){
    delete shootingTimer;
    shootingTimer = NULL;
}

int Tower::getAttackRange(){
    return attackRange;
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

QPixmap Tower::getPixmap(){
    return this->pixmap;
}

void Tower::checkEnemyInRange(){
    if (targetEnemy){   //如果选中的目标敌人不是NULL，则准备瞄准
        QVector2D normalized(targetEnemy->getCenterPos()- _pos);  //敌人到塔的向量
        normalized.normalize();

        if (getDistance(targetEnemy->getCenterPos() , _pos+QPoint(30,20)) > attackRange){ //敌人逃离攻击范围
            chosenEnemyEscaped();
        }
    }
    else{ // 看所有在list里面的敌人有没有在攻击范围内的
        foreach (Enemy *enemy, mygamewindow->fun_enemy_list()){
            if (getDistance(enemy->getCenterPos() +QPoint(20,0) , _pos+QPoint(30,20)) < attackRange){           //就是这里！！！！之前用的是targetEnemy的位置，而targetEnemy是NULL，所以造成了指针的问题
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::draw(QPainter * painter) const {
    painter->save();
    painter->setPen(Qt::white);
    painter->drawEllipse(_pos, attackRange, attackRange);    // 绘制攻击范围圆圈，用画椭圆的函数
    static const QPoint offsetPoint(- sizeX / 2, - sizeY / 2);    // 绘制偏转坐标,由中心+偏移=左上
      // 绘制炮塔并选择炮塔。这里将坐标原点移到_pos,绘制的适合,就要加上那个偏移点到左上角
    painter->translate(_pos);
    painter->drawPixmap(offsetPoint, pixmap);

    painter->restore();
}

void Tower::startShooting(){
    shootingTimer->start(shootRate);
}

void Tower::chooseEnemyForAttack(Enemy * enemy){
    targetEnemy = enemy;
    startShooting();
    targetEnemy->getAttacked(this);
}

void Tower::shoot(){
    MyObject *bullet = new MyObject(_pos+QPoint(-40,-30),targetEnemy->getCenterPos(),damage,targetEnemy, mygamewindow );
    bullet->move();
    mygamewindow->addBulletToList(bullet);
}

void Tower::targetDead(){
    if (targetEnemy){
        targetEnemy = NULL;
    }

    shootingTimer->stop();
}

void Tower::chosenEnemyEscaped(){
    targetEnemy->haveEscaped(this);
    if(targetEnemy){
        targetEnemy = NULL;
    }

    shootingTimer->stop();
}

void Tower::upGradeTower(){
    this->attackRange = this->attackRange*7/6;
    this->shootRate = this->shootRate *4/5;
}

void Tower::changeTowerType(){
    this->pixmap = QPixmap(":/tower3.png");
    changeTowerAttackRange();
    this->shootRate = shootRate * 2;
}

void Tower::changeTowerAttackRange(){  //用于第二种塔
    this->attackRange = this->attackRange*4/3;
}

void Tower::changeTowerDamage(int new_damage){
    this->damage = new_damage;
}



