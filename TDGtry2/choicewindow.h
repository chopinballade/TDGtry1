#ifndef CHOICEWINDOW_H
#define CHOICEWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QMouseEvent>
#include<QDebug>
#include"tower.h"
#include"myobject.h"
#include"myobject2.h"
#include"enemy.h"
#include"heart.h"
#include<QList> //用到QList, 与vector有点像

class Enemy;
class MyObject;

class ChoiceWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoiceWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void set_tower1();//tower.cpp中的举例，点击按钮建塔：
    void set_tower2();
    void set_tower3();
    void addMyObject();
    void showInfo(QPainter * painter);

    int HP; //玩家生命值
    int wave;

    void showEnemy();
    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy * enemy);
    void addBullet(MyObject *bullet);
    void removedBullet(MyObject *bullet);
    bool loadWave();
    void preLoadWavesInfo();
    void doGameOver();

    QList<Enemy *> fun_enemy_list() const;   //函数

protected:
//    void mousePressEvent(QMouseEvent * event);

private: 
    QList<Tower*> tower_list;      //创建对应tower的tower_list
    //QList<MyObject*> object_list;   //创建对应myobject的object_list
    QList<MyObject2*> object2_list;   //创建对应myobject2的object2_list
    QList<Enemy*> enemy_list;   //创建对应enemy的enemy_list
    QList<MyObject*> bullet_list;   //创建对应bullet的bullet_list
    QList<QVariant>	wavesInfo;    //用于PlistReader
    bool gameEnded;
    bool gameWin;

signals:
    void chooseBack();  //添加一个信号，用于返回按钮返回主界面
private slots:
    void gameStart();
    void updateScene();

public slots:
};

#endif // CHOICEWINDOW_H
