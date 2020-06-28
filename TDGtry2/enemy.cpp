#include "enemy.h"
#include"tower.h"
#include<QPoint>
#include<QVector2D>
#include<QPainter>
#include<QColor>
#include<QDebug>
#include<QtMath>
#include"choicewindow.h"
#include<QTimer>
#include<stdio.h>


static const int Health_Bar_Width = 60;

Enemy::Enemy(QPoint startPos, QPoint targetPos, ChoiceWindow *game, const QPixmap &sprite)
    :QObject(0), _pixmap(sprite),
      maxHP(40), currentHP(40), isAlive(false),
      speed(1.0), gamewindow(game),
      _startPos(startPos),_currentPos(startPos),_targetPos(targetPos)
{

}

Enemy::~Enemy(){
    attackedTowersList.clear();
    gamewindow = NULL;
}

void Enemy::turnAlive(){
    isAlive = true;
}

void Enemy::move()
{
    if(isAlive==false){
        return;
    }
    if(_currentPos.x()>950){   //碰到heart了
        gamewindow->HPDamage();
        gamewindow->deleteEnemy(this);
        return;
    }
    qreal movementSpeed = speed;
    QVector2D normalized(_targetPos - _currentPos);
    normalized.normalize();
    _currentPos = _currentPos + normalized.toPoint() * movementSpeed;
}


void Enemy::draw(QPainter *painter){
    if (!isAlive)
        return;
    painter->save();

    QPoint healthBarPoint = _currentPos + QPoint(- Health_Bar_Width/2 +25, -70);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);//底部红色血条
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)currentHP / maxHP * Health_Bar_Width, 5));
    painter->drawRect(healthBarRect);

    static const QPoint offsetPoint(-100 / 2, -100 / 2);
    // 绘制偏转坐标,由中心+偏移=左上
    painter->translate(_currentPos);
    painter->drawPixmap(offsetPoint, _pixmap);// 绘制敌人

    painter->restore();
}

QPoint Enemy::getCenterPos(){  //获取敌人图片中心位置
    QPoint currentPos;
    currentPos.setX(_currentPos.x()+40);
    currentPos.setY(_currentPos.y()+30);
    return currentPos;
}

void Enemy::getDeleted(){
    if (attackedTowersList.empty()){
        return;   //即没有打该敌人的塔，所以不会getRemoved
    }
    foreach (Tower *attacker, attackedTowersList){
        attacker->targetDead();
    }
    gamewindow->deleteEnemy(this);   //通知game,此敌人已经阵亡
}

void Enemy::enemyGetDamage(int damage){
    currentHP -= damage;
    if (currentHP <= 0){
        getDeleted();  //死亡并移除
    }
}

void Enemy::getAttacked(Tower *attacker){
    if((attacker->getPos().y() < 300)
//         && (attacker->getDistance(this->getcurrentpos(),attacker->getPos())) < (attacker->getAttackRange()-30)
       )
    {
           //若受到上面那排塔1的攻击，则减速。为了配合子弹动画效果再加一个延时
        if(attacker->getDistance(this->getcurrentpos(),attacker->getPos()) < (attacker->getAttackRange())+30){
            QTimer::singleShot(1300, this, SLOT(slowSpeed()));
        }

//        else
//            slowSpeed();
    }

    attackedTowersList.push_back(attacker);
}

void Enemy::haveEscaped(Tower *attacker){  //敌人逃离攻击范围
    attackedTowersList.removeOne(attacker);
}

QPoint Enemy::getcurrentpos() const{
    return _currentPos;
}

void Enemy::slowSpeed(){
    this->speed= this->speed /3*2;
}
void Enemy::fastSpeed(){
    this->speed= this->speed /3*4;
}

void Enemy::changeEnemyType_1(){
    this->_pixmap=QPixmap(":/enemy1.png");
}
void Enemy::changeEnemyType_2(){
    this->_pixmap=QPixmap(":/enemy2.png");
}

