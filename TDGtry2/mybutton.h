#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QObject>
#include <QWidget>
#include<QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QString pix);  //传一个QString类型的来输入路径
    void zoomdown();
    void zoomup();  //按钮向下跳和向上跳

signals:

public slots:
};

#endif // MYBUTTON_H
