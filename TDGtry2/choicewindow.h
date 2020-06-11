#ifndef CHOICEWINDOW_H
#define CHOICEWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>
#include"tower.h"
#include<QList> //用到QList, 与vector有点像

class ChoiceWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoiceWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    //tower.cpp中的举例，点击按钮建塔：
    void set_tower();

private:
    QList<Tower*> tower_list;      //创建tower_list

signals:
    void chooseBack();  //添加一个信号，用于返回按钮返回主界面

public slots:
};

#endif // CHOICEWINDOW_H
