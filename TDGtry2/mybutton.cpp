#include "mybutton.h"
#include<QPixmap>

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
