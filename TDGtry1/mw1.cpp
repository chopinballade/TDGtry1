#include "mw1.h"
#include "ui_mainwindow.h"
#include "icon.h"
#include <QTime>
#include<QTimer>
#include <map>
#include <iostream>

using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);
    //init game world
    _game.initWorld("");//TODO 应该是输入有效的地图文件

}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *e){
    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    this->_game.show(pa);
    pa->end();
    delete pa;
}
