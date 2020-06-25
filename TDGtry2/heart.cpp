#include "heart.h"
#include <QObject>
#include<QPropertyAnimation>
#include<QPoint>
#include<QPixmap>
#include<QPainter>
#include<QPaintEvent>

Heart::Heart(QString filename): _pixmap(filename){

}

void Heart::draw(QPainter * painter){
    painter->drawPixmap(QPoint(920,200), _pixmap);  //在当前位置，画对应图片
}




