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
#include"myobject.h"
#include"myobject2.h"

ChoiceWindow::ChoiceWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1100,700);
   //显示关卡选择界面的函数在下面单独的paintEvent
    MyButton * back_btn = new MyButton(":/button2.png"); //new一个“返回”按钮
    back_btn->setParent(this);  //指定父类
    back_btn->setIconSize(QSize(80,80));//这几步使得按钮比例按原图且可以调整大小
    back_btn->move(45,40); //设置返回按钮在屏幕的位置

    connect(back_btn, &MyButton::clicked, this, [=](){
        emit chooseBack();  //emit用于发送signal。chooseback()是添加在ChoiceWindow类里的信号函数。
    });

    //举例：按下一个“建塔”按钮就能创建一个塔
    MyButton * setTower = new MyButton(":/button3.jpg");
    setTower->setParent(this);
    setTower->move(660,70);  //“建塔”按钮的位置
    connect(setTower,&MyButton::clicked,this,&ChoiceWindow::set_tower);
      //创建与建塔函数set_tower()的connect

    //举例：按下一个“ ”按钮就能创造一个类似子弹的？可在指定两点之间运动的myobject类物体（视频14:30开始）
    MyButton * addObject = new MyButton(":/button3.jpg");
    addObject->setParent(this);
    addObject->move(730,70);  //“发射子弹”按钮（需要这个吗）的位置
    connect(addObject,&MyButton::clicked,this,&ChoiceWindow::addMyObject);
      //创建与建塔函数addMyObject()的connect


    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ChoiceWindow::updateScene);
        //timeout--时间开始，this界面，执行的是choicewindow类的updatescene函数
    timer->start(10);  //从0毫秒开始，每10毫秒触发一次QTimer::timeout，即触发一次updatescene以更新界面，达到动画效果。

}

void ChoiceWindow::paintEvent(QPaintEvent *){ //每次打开choicewindow都会调用（三次）
    QPainter painter(this);
    QPixmap pixmap(":/TDGmap1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);


    showInfo(&painter);   //输出想要的文字框。showInfo函数的实现在下面

    foreach(Tower* tower, tower_list){   //foreach类似for。类型是Tower*的tower，在tower_list中找。
        tower->draw(&painter);
    }//建塔显示
    foreach (MyObject * object, object_list) {
        object->draw(&painter);
    }//建myobject显示
    foreach (MyObject2 * object2, object2_list) {
        object2->draw(&painter);
    }//建myobject2显示

}

//tower.cpp中上面的举例，点击按钮建塔：
void ChoiceWindow::set_tower(){
    Tower * a_new_tower = new Tower(QPoint(220,150),":/tower1.png");
       //建造新塔，设置位置。
    tower_list.push_back(a_new_tower);//把这个刚创建好的塔放进QList里面，方法类似vector。
       //见上面ChoiceWindow类的private:  QList<Tower*> tower_list;
    update();  //若去掉这句函数，则需要最小化一下窗口才能显示出新建造的塔。因为重新打开窗口时自动update。不如自己写出来就不会出现这种情况。
}//以上这个函数是举例：点击“+”建塔按钮建一个固定了位置的塔

void ChoiceWindow::addMyObject(){
    MyObject2 * object2 = new MyObject2(QPoint(220,150), QPoint(600,400), ":/bullet1.png");
    object2_list.push_back(object2);
//    object2->move();  //这一步放到了下面的updateScene函数里。MyObject2::move()是自己写的两点之间运动的函数，但目前还没加上让object2停下的判断条件
    update();  //这里update一次根本无法达到持续从某点到某点的动画效果，所以在choicewindow.h中再自己写一个updateScene()函数，用于多次更新界面

    MyObject * object = new MyObject(QPoint(220,150), QPoint(640,240), ":/bullet3.png");
    object_list.push_back(object);
    object->move();  //MyObject::move()自己写的两点之间运动的函数
    update();  //这里update一次根本无法达到持续从某点到某点的动画效果，所以在choicewindow.h中再自己写一个updateScene()函数，用于多次更新界面
}

void ChoiceWindow::updateScene(){ //用于多次更新界面达到动画效果
    foreach (MyObject2 * object2, object2_list) {
        object2->move();
    }

    update();  //先暂时这么写
}

void ChoiceWindow::showInfo(QPainter *painter){
    painter->save();  //先把画笔未改变状态之前的样子存起来
    painter->setPen(Qt::white);  //画笔颜色为白
    painter->setFont(QFont("Comic Sans MS", 17 ));  //设置字体和字号
    painter->drawText(QRect(70,550,400,100) , QString("HP: %1    wave: %2").arg(HP).arg(wave));
                      //指定绘画范围矩形框。左上角坐标（...,...），宽度...，高度...。
                      //输入信息。格式：第一个参数%1，第二个参数%2，括号外.arg(num1).arg(num2)
       //注意：尚未设置HP和wave值改变后，以上数字也改变的功能
    painter->restore();   //画完后恢复画笔

}










