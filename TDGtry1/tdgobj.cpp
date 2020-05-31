#include "tdgobj.h"
#include <iostream>

void TDGObj::initObj(string type)
{
    //TODO 所支持的对象类型应定义为枚举

    this->_icon = ICON::findICON(type);   //根据类型
    QImage all;

//    all.load(":/pics/TileB.png");
//    this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
}

void TDGObj::show(QPainter * pa){
    int gSize = ICON::GRID_SIZE;
    pa->drawImage(this->_pos_x*gSize,this->_pos_y*gSize,this->_pic);
}


