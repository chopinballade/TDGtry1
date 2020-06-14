#ifndef CHOICEWINDOW_H
#define CHOICEWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>
#include"tower.h"
#include"myobject.h"
#include"myobject2.h"
#include"enemy.h"
#include"heart.h"
#include<QList> //用到QList, 与vector有点像

class ChoiceWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoiceWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void set_tower();//tower.cpp中的举例，点击按钮建塔：
    void addMyObject();
    void updateScene();
    void showInfo(QPainter * painter);
    int HP=5;
    int wave=1;  //只是举例。这种参数用于showInfo（实现文字框输出）
    void showEnemy();


private:
    QList<Tower*> tower_list;      //创建对应tower的tower_list
    QList<MyObject*> object_list;   //创建对应myobject的object_list
    QList<MyObject2*> object2_list;   //创建对应myobject2的object2_list
    QList<Enemy*> enemy_list;   //创建对应enemy的enemy_list



signals:
    void chooseBack();  //添加一个信号，用于返回按钮返回主界面

public slots:
};

#endif // CHOICEWINDOW_H
