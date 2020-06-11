#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>
#include"choicewindow.h"
#include"mybutton.h"
#include<QTimer>  //用于展示按钮弹跳效果的延时
#include<QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(800,600); //界面大小
    ui->setupUi(this);

    MyButton * btn= new MyButton(":/button1.png");
     //MyButton类的成员 * btn 作为进入关卡选择的按钮，同时关闭主界面
    btn->setParent(this);  //手动指定父类
    btn->move(42,400);   //"play"按钮位置，待调整
    btn->setIconSize(QSize(170,80));

    ChoiceWindow * scene = new ChoiceWindow;
    //connect(btn, &MyButton::clicked,this,&QMainWindow::close);
           //btn 按钮按下就关闭主界面
           //有个待解决：这里什么时候用&MyButton什么时候用&QPushButton ?
    connect(btn, &QPushButton::clicked,this,[=](){
        btn->zoomdown();
        btn->zoomup();  //按钮向上向下跳的效果，为了显示出来需要下面的QTimer来暂停。
        QTimer::singleShot(400,this,[=](){
            this->hide();  //主界面的隐藏
            scene->show();  //新界面的展示。scene是上面刚new出来的
        });//暂停400毫秒，指定在this界面
    });
  /*上面的lambda表达式（用于场景切换）即 connect [](){}()。
    [=]的等号大概意思是可以使用当前类的所有东西。大括号里面是函数的实现。*/

    connect(scene,&ChoiceWindow::chooseBack,this,[=](){
        scene->hide();
        this->show();
    });  //主界面this和选择界面scene的连接。在ChoiceWindow中创建了back_btn按钮，点击即可emit一个chooseBack信号。

/*以下为按钮举例
    QPushButton * btn = new QPushButton(this);
    btn->setFixedSize(100,50);
    btn->move(40,40); //关卡选择（、主窗口关闭）按钮的大小和位置
    connect(btn, &QPushButton::clicked,this,&QMainWindow::close);
        //btn是该物品，函数指针希望点击来发出信号,this,传到mainwindow上,希望点击后主窗口关闭。   */

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *){ //每次打开mainwindow都会调用（三次）
    QPainter painter(this);
    QPixmap pixmap(":/startscreen.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
