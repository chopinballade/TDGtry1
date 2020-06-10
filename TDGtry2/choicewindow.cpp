#include "choicewindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>

ChoiceWindow::ChoiceWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800,600);
//显示关卡选择界面
    QPainter painter(this);
    QPixmap pixmap(":/choicescreen.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

void ChoiceWindow::paintEvent(QPaintEvent *){ //每次打开choicewindow都会调用（三次）
    QPainter painter(this);
    QPixmap pixmap(":/choicescreen.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
