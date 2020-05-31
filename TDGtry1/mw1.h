#ifndef MW1_H
#define MW1_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include<QKeyEvent>
#include<QTimer>
#include "tdgobj.h"
#include "world.h"

namespace Ui {
class MW1;
}

class MW1 : public QMainWindow      //这个类主要用于在屏幕画东西、处理键盘鼠标的事件
{
    Q_OBJECT

public:
    explicit MW1(QWidget *parent = 0);
    ~MW1();
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *);

//protected slots:
//    void randomMove();

private:
    Ui::MW1 *ui;
    World _game;  //游戏世界
    QTimer *timer;
};

#endif // MW1_H
