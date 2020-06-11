#include "choicewindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>
#include<QTimer>
#include<QMediaPlayer>
#include<QPixmap>
#include"mybutton.h"
#include"mainwindow.h"
#include"mainwindow.h"

ChoiceWindow::ChoiceWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800,600);
//显示关卡选择界面
//    QPainter painter(this);
//    QPixmap pixmap(":/choicescreen.jpg");
//    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    MyButton * back_btn = new MyButton(":/button2.png"); //new一个“返回”按钮
    back_btn->setParent(this);  //指定父类
    back_btn->setIconSize(QSize(80,80));//这几步使得按钮比例按原图且可以调整大小
    back_btn->move(35,33); //设置返回按钮在屏幕的位置

    //举例：按下一个“建塔”按钮就能创建一个塔
    MyButton * setTower = new MyButton(":/button3.jpg");
    setTower->setParent(this);
    setTower->move(660,64);  //“建塔”按钮的位置
    connect(setTower,&MyButton::clicked,this,&ChoiceWindow::set_tower);
      //创建与建塔函数set_tower()的connect

    connect(back_btn, &MyButton::clicked, this, [=](){
        emit chooseBack();  //emit用于发送signal。chooseback()是添加在ChoiceWindow类里的信号函数。
    });

}

void ChoiceWindow::paintEvent(QPaintEvent *){ //每次打开choicewindow都会调用（三次）
    QPainter painter(this);
    QPixmap pixmap(":/TDGmap1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);



    //下面是建塔显示
    foreach(Tower* tower, tower_list){   //foreach类似for。类型是Tower*的tower，在tower_list中找。
        tower->draw(&painter);
    }

}

//tower.cpp中上面的举例，点击按钮建塔：
void ChoiceWindow::set_tower(){
    Tower * a_new_tower = new Tower(QPoint(180,120),":/tower1.png");
       //建造新塔，设置位置。
    tower_list.push_back(a_new_tower);//把这个刚创建好的塔放进QList里面，方法类似vector。
       //见上面ChoiceWindow类的private:  QList<Tower*> tower_list;
    update();  //若去掉这句函数，则需要最小化一下窗口才能显示出新建造的塔。因为重新打开窗口时自动update。不如自己写出来就不会出现这种情况。
}
//以上这个函数是举例：点击“+”建塔按钮建一个固定了位置的塔


