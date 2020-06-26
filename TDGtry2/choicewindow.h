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
    void set_tower4();
    void showInfo(QPainter * painter);

    int HP; //玩家生命值
    int wave;

    void HPDamage(int damage = 1);
    void deleteEnemy(Enemy * enemy);
    void addBulletToList(MyObject *bullet);
    void deleteBullet(MyObject *bullet);
    bool loadWave();
    void gameOverScene();

    QList<Enemy *> fun_enemy_list() const;   //获取enemy_list的函数

protected:
//    void mousePressEvent(QMouseEvent * );  //备用建塔方式，鼠标点击处建塔

private: 
    QList<Tower*> tower_list;      //创建对应tower的tower_list
    QList<Enemy*> enemy_list;   //创建对应enemy的enemy_list
    QList<MyObject*> bullet_list;   //创建对应bullet的bullet_list
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
