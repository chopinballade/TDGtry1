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
#include<iostream>
#include<ctime>


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

    QMediaPlayer * player1 = new QMediaPlayer;
    player1->setMedia(QUrl("qrc:/bgm3_help_cute.mp3"));
    player1->setVolume(30);
    player1->play();

    QMediaPlayer * player2 = new QMediaPlayer;
    player2->setMedia(QUrl("qrc:/bgm2_game_cute.mp3"));
    player2->setVolume(30); //不急着play


    ChoiceWindow * scene = new ChoiceWindow;

    connect(btn, &QPushButton::clicked,this,[=](){
        btn->zoomdown();
        btn->zoomup();  //按钮向上向下跳的效果，为了显示出来需要下面的QTimer来暂停。
        QTimer::singleShot(400,this,[=](){
            this->hide();  //主界面的隐藏
            scene->show();  //新界面的展示！！！！！scene是上面刚new出来的
            player1->stop();
            player2->play();  //音乐切换
        });//暂停400毫秒，指定在this界面
    });
  /*上面的lambda表达式（用于场景切换）即 connect [](){}()。
    [=]的等号大概意思是可以使用当前类的所有东西。大括号里面是函数的实现。*/

    connect(scene,&ChoiceWindow::chooseBack,this,[=](){
        scene->hide();
        this->show();
    });  //主界面this和选择界面scene的连接。在ChoiceWindow中创建了back_btn按钮，点击即可emit一个chooseBack信号。

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){ //每次打开mainwindow都会调用（三次）
    QPainter painter(this);
    QPixmap pixmap(":/startscreen.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    showGameName(&painter);  //展示游戏名称
}

void MainWindow::showGameName(QPainter * painter){
    painter->save();  //先把画笔未改变状态之前的样子存起来
    painter->setPen(Qt::white);  //画笔颜色为白
    painter->setFont(QFont("Impact", 32));  //设置字体和字号.Impact/Arial Black/
    painter->drawText(QRect(30,250,1000,500) , QString("Nightmare of the Mice’s Clan"));
                      //指定绘画范围矩形框。左上角坐标（...,...），宽度...，高度...。
    painter->restore();   //画完后恢复画笔
}











