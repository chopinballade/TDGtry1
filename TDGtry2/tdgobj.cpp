#include "tdgobj.h"
#include <iostream>

void TDGObj::initObj(string type)
{
    this->_icon = ICON::findICON(type);   //根据类型
    QImage all;

    all.load(":/pictures/TDGmap1.png");   //素材图片。这里先用背景图片试试
    this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE,
                                _icon.getSrcY()*ICON::GRID_SIZE,
                                _icon.getWidth()*ICON::GRID_SIZE,
                                _icon.getHeight()*ICON::GRID_SIZE));
}

void TDGObj::show(QPainter * pa){
    int gSize = ICON::GRID_SIZE;
    pa->drawImage(this->_pos_x*gSize,this->_pos_y*gSize,this->_pic);
}

//int TDGObj::getNextX(int direction){
//    switch (direction){
//        case 1:
//            return this->_pos_x;
//        case 2:
//           return this->_pos_x;
//        case 3:
//           return this->_pos_x-1;
//        case 4:
//           return this->_pos_x+1;
//    }
//}

//int TDGObj::getNextY(int direction){
//    switch (direction){
//        case 1:
//            return this->_pos_y - 1;
//        case 2:
//           return this->_pos_y + 1;
//        case 3:
//           return this->_pos_y;
//        case 4:
//           return this->_pos_y;
//    }
//}



//void TDGObj::onErase(){   //比如吃掉水果时视情况放不同音乐

//    QMediaPlayer * player = new QMediaPlayer;
        //注意这里是播放音乐的办法！！！！！
//    player->setMedia(QUrl("qrc:/sounds/2953.mp3"));
//    player->setVolume(30);
//    player->play();

//}

