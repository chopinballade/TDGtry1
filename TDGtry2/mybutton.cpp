#include "mybutton.h"
#include<QPixmap>
#include<QPropertyAnimation>

MyButton::MyButton(QString pix): QPushButton(0){
    QPixmap pixmap(pix);  //这样可以使按钮比例与原图一致
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
      //该函数可根据图片外观调整自己外观
    this->setIcon(pixmap);
    //this->setIconSize(QSize(60,60));   //存在问题：是否将每个按钮都设置成这么大？
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));  //这句话可以使按钮大小与原图一致
//设置好了按钮图片格式
}

void MyButton::zoomdown(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
        //先创建一个动画类的对象。动的东西是this，动的属性是“geometry”。
    animation->setDuration(150);  //持续时间200毫秒
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
     //下面设定弹跳曲线，用到QEasingCurve::OutBounce 效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();  //手动让它开始
}
void MyButton::zoomup(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(150);  //持续时间200毫秒
    animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
     //下面设定弹跳曲线，用到QEasingCurve::OutBounce 效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();  //手动让它开始
}
